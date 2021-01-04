import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Get symbol and shares from ledger where the sum of shares is not negative or zero
    data = db.execute("SELECT symbol, shares FROM (SELECT DISTINCT symbol, SUM(SHARES) as shares, PRICE FROM LEDGER where user_id = :uid GROUP BY SYMBOL ORDER BY date DESC) WHERE 0 < SHARES", uid=session["user_id"])

    # Get the amount of cash a user has
    cash = db.execute("SELECT CASH FROM USERS where id=:uid", uid=session["user_id"])[0]["cash"]

    # Assign an initial value for the grand total
    total = 0;

    # Iterate data and add new fields to dict from lookup
    for row in data:
        # Get current data for symbol
        currentData = lookup(row["symbol"])
        # New field stock name
        row["stock_name"] = currentData["name"]

        # Re-assign price to current price
        row["price"] = currentData["price"]

        # Calculate cost
        cost = currentData["price"] * row["shares"]

        # New field total
        row["total"] = usd(cost)

        # Increment total of all totals
        total += cost

    # Now include cash to five final grand total
    total += cash

    # Return template with data from above
    return render_template("index.html", portfolio=data, userCash=usd(cash), grandTotal=usd(total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # Are inputs valid?
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Stock lookup
        stock = lookup(request.form.get("symbol"))

        # Was there even a symbol by this name?
        if not stock:
            return apology(f"No such stock symbol: '{symbol}' ")


        # What is the total of price * number of shares?
        total = stock["price"] * float(shares)

        # How much cash does a user have?
        cash = db.execute("SELECT cash FROM users where id= :uid", uid=session["user_id"])[0]["cash"]

        # Is the price affordable?
        if cash < total:
            return apology(f"Cannot afford purchase of {usd(total)} with {usd(cash)}")

        # Create id for transaction
        transactionId = db.execute("SELECT MAX(ID) as MAX_ID FROM LEDGER")[0]["MAX_ID"]

        # If there is no max value meaning table is empty then assign 1 for first transaction
        if not transactionId:
            transactionId = 1

        # Else assign id always ranging from 2 to N meaning table is not empty
        else:
            transactionId += 1

        # Submit transaction to the ledger
        transaction = db.execute(f"""
        INSERT INTO LEDGER (id, user_id, is_buyer, symbol, shares, price)
        VALUES (
        {transactionId},
        {session["user_id"]},
        1,
        '{stock["symbol"]}',
        {int(shares)},
        {stock["price"]}
        )
        """)

        # Deduct cash from purchase
        deduction = db.execute(f"""
        UPDATE USERS
        SET cash = cash - {total}
        WHERE id = {session["user_id"]}
        """)
        flash("Purchased successfuly!")
        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Select history data
    history_data = db.execute("SELECT symbol, shares, price, date FROM ledger where user_id=:uid ORDER BY date DESC", uid=session["user_id"])
    # Return template with data
    return render_template("history.html", history=history_data)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        res = lookup(request.form.get("symbol"))
        if not res:
            return apology(f"No symbol found: {request.form.get('symbol')}")
        print("Objects found:", res)
        return render_template("quoted.html", stocks=res)

    return render_template("quote.html")

    # return apology("TODO")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        name = request.form.get("username").strip()

        # Require that a user inputs a username that is not blank
        if len(name) == 0 or len(name.split(" ")) != 1:
            return apology("Username cannot be blank or have spaces in between chars", 400)

        # Require both passwords to match
        if not request.form.get("password1") == request.form.get("password2"):
            return apology("Passwords do not match", 400)

        # If username is allready taken
        if len(db.execute("SELECT * FROM users WHERE username = :username", username=name)) > 0:
            return apology("User name unavailable")

        # Hash password
        password = generate_password_hash(request.form.get("password1"), "sha256", salt_length=8)

        # Finds highest ID value
        userId = db.execute("SELECT MAX(ID) as MAX_ID FROM users")[0]["MAX_ID"]

        # If there is no max value meaning table is empty then assign 1 for first user
        if not userId:
            userId = 1

        # Else assign user id always ranging from 2 to N meaning table is not empty
        else:
            userId+=1

        user = db.execute("INSERT INTO users (id, username, hash, cash) VALUES (:uid, :username, :pwd_hash, :cash)", uid=userId, username=name, pwd_hash=password, cash=10000.00)
        flash("Registered successfuly!")
        return redirect("/login")

    return render_template("register.html")





@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():


    """Sell shares of stock"""
    if request.method == "POST":
            # How many shares does the user have?
            symbol = request.form.get("symbol")
            shares = int(request.form.get("shares"))
            maxShares = db.execute(
                "SELECT SUM(SHARES) AS MAX_SHARES FROM LEDGER WHERE USER_ID=:uid and SYMBOL=:fSymbol",
                uid=session["user_id"],
                fSymbol=symbol)[0]["MAX_SHARES"]

            # Can user sell this many shares?
            if not shares <= maxShares:
                return apology(f"Not enough shares, you only have {shares}...")

            # Look up stock data
            stock = lookup(symbol)

            # Create id for transaction
            transactionId = db.execute("SELECT MAX(ID) as MAX_ID FROM LEDGER")[0]["MAX_ID"]

            # If there is no max value meaning table is empty then assign 1 for first transaction
            if not transactionId:
                transactionId = 1

            # Else assign id always ranging from 2 to N meaning table is not empty
            else:
                transactionId += 1
            # Insert transaction to ledger
            transaction = db.execute(f"""
                INSERT INTO LEDGER (id, user_id, is_buyer, symbol, shares, price)
                VALUES (
                    {transactionId},
                    {session["user_id"]},
                    0,
                    '{stock["symbol"]}',
                    {0 - int(shares)},
                    {stock["price"]}
                )
                """)

            # What is the total of price * number of shares?
            total = stock["price"] * float(shares)

            # Add to users cash
            addCash = db.execute(f"""
                UPDATE USERS
                SET cash = cash + {total}
                WHERE id = {session["user_id"]}
            """)
            flash("Sold successfuly!")
            return redirect("/")

    symbolData = db.execute("SELECT SYMBOL FROM LEDGER WHERE USER_ID=:uid group by symbol", uid=session["user_id"])
    userSymbols = []
    for dict_item in symbolData:
        userSymbols.append(list(dict_item.values()))
    return render_template("sell.html", symbols=userSymbols)


# Personal touch -->
@app.route("/deposit", methods=["POST"])
@login_required
def deposit():
    if request.method == "POST":
        # Check if input is not negative
        amount = request.form.get("cash")

        # Run query to add cash
        addCash = db.execute(f"""
                UPDATE USERS
                SET cash = cash + {amount}
                WHERE id = {session["user_id"]}
            """)

        #  Redirect user back to index
        flash("Added cash successfuly!")
        return redirect("/")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
