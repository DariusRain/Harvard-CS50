
# [Pluto](https://github.com/DariusRain/Pluto)
_[MERN](https://www.geeksforgeeks.org/mern-stack/) Social Media Project_
[Source Code](https://github.com/DariusRain/Pluto/tree/master)
[See the app in action](http://pluto-285916.appspot.com)
[See README on github](https://github.com/DariusRain/Pluto/tree/master)

## About:
This project I will be using [Expressjs](https://expressjs.com/) with [Nodejs](https://nodejs.org/en/) for the backend, and [Reactjs](https://reactjs.org/) with [Reduxjs](https://redux.js.org/) for the front-end, [MongoDB](https://www.mongodb.com/try/download/community) for a database, and Google Cloud for deployment. This application will be a social media platform for developers where they can link their github to the application and see other developers as well.

## Requirements:
Nodejs
NPM (Node Package Manager)

## Brief guide on how I got started:
&nbsp;
&nbsp;
- Setting up mongoose database connection & server.
 - Creating a config folder and index file.
```javascript
// Location: ./config/index.js
module.exports = {
  // This is needed for connecting a database for when mongosse.connect() needs to use it & apply a connection.
  mongoUri:"mongodb+srv://<USERNAME>:<PASSWORD>@<CLUSTER-NAME>-xhcxn.mongodb.net/<APP-NAME>?retryWrites=true",
  // This is needed in order to Sign & Verify JSON web tokens sort of like a password but more like a private key.
  jwtSec: "<ANY-STRING>",
  // These are used for retreval of a users github information, this is obtained by going to your Github and creating
  // a OAuth application.
  githubClientId: "<GET-FROM-GITHUB-OAUTH-DEV-SETTINGS>",
  githubClientSecret: "<GET-FROM-GITHUB-OAUTH-DEV-SETTINGS>",
};
```
&nbsp;
&nbsp;
- DB connection file.

```javascript
// Location: ./config/db/index.js
const { mongoUri } = require("../index");
module.exports = async () => {
  try {
    await mongoose.connect(mongoUri, {
      useNewUrlParser: true,
      useUnifiedTopology: true,
      useCreateIndex: true,
      useFindAndModify: false,
    });
    console.log("Connected to database.");
  } catch (err) {
    console.error(err);
    process.exit(1);
  }
};
```
&nbsp;
&nbsp;
- Initialization of the server.js file & importing the above.

```javascript
// SERVER MAIN

// Server
const express = require("express");
const server = express();
const PORT = process.env.PORT || 5000;

// Database
const connectDB = require("./config/db");

// Connections
connectDB();
server.listen(PORT, () => {
  console.log(`Listening on ${PORT}`);
});
```
&nbsp;
&nbsp;

- Creating the API.
  - Models
    - [./models/User.js](https://github.com/DariusRain/Pluto/blob/master/models/User.js) ( User model )
    - [./models/Post.js](https://github.com/DariusRain/Pluto/blob/master/models/Post.js) ( Post model )
    - [./models/Profile.js](https://github.com/DariusRain/Pluto/blob/master/models/Profile.js) ( Profile model )
  - Routes
    - [./routes/api/users.js](https://github.com/DariusRain/Pluto/blob/master/routes/api/users.js) ( Users route )
    - [./routes/api/posts.js](https://github.com/DariusRain/Pluto/blob/master/routes/api/posts.js) ( Posts route for users )
    - [./routes/api/profiles.js](https://github.com/DariusRain/Pluto/blob/master/routes/api/profiles.js) ( Profiles routes for users )
    - [./routes/api/auth.js](https://github.com/DariusRain/Pluto/blob/master/routes/api/auth.js) ( Authenticated routes )
  - JsonWebToken
    - Create a payload you want to sign and send a response <br />
      with the signed token.

```javascript
// CREATING A JSON WEBTOKEN

const jwt = require("jsonwebtoken");
const { jwtSec } = require("../../config");

// This below operation would be performed inside the try & catch block
// of your route handler.  Usually after a document has been found from the
// database you would then use the ID of the document as a payload, though you can store more
// in a JSON web token.

// Creating a payload that you want to sign.
// You would perorm a .find(<KEY:UNIQUE-VALUE>) on a model in order to get 'userDocId'.
// Note: You can add more properties to a payload if you wanted to.
const payload = {
  user: userDocId,
};

// Sign the token, set experation, and a callback that returns either an error or the token.
jwt.sign(
  // PAYLOAD: Could be anything.
  payload,
  // JWT-SECRET: Secret string imported from ./config/index.js
  jwtSec,
  // EXPIRATION: Set an expiration date on the token.
  { expiresIn: 360000 },
  // CB-FUNC: Callback recieves two values passed,
  //    err: Either false or truthy val
  //    token: If the above 'err' is false then this argument has
  //            a value of a token.
  (err, token) => {
    if (err) throw err;
    return res.status(200).json(token);
  }
);
```
&nbsp;
&nbsp;
- Token verification middleware for tokens sent by the client.

```javascript
// EXAMPLE: VERIFYING A JSON WEBTOKEN
// Location: ./middleware/auth.js
const { verify } = require("jsonwebtoken");
const { jwtSec } = require("../config");
module.exports = (req, res, next) => {

  // Get token from header
  // When building the front-end, this property in the header will be set using axios.
  const token = req.header("x-auth-token");


  // If no token
  if (!token) {
    return res.status(401).json({ msg: "No token, authorization denied." });
  }

  // Verify token
  try {
    // Scince there is a token after the above logic, it now needs verified.
    // The verify method takes in the token and the jwt secret string as arguemnts.
    // and the secret string used to sign the token will now be used
    // to decode the token.
    const decoded = verify(token, jwtSec);

    // The decoded token should be the payload it once was whenever you signed the token
    // in whatever route handles that operation. (See the last example.)

    // req.user = { id: "MongooseDocumentId", iat: "IssuedAtTimeSetInMiliseconds." }
    req.user = decoded;

    // Proceed to the next callback function in the chain.
    next();

  } catch (err) {
    // If any falsey values were thrown above then that means the token was not valid.
    res.status(401).json({ msg: "Token is not valid." });
  }
};
```
&nbsp;
&nbsp;
- Password hashing & authentication with bcryptjs:
    - Like the above example this will be implemented in a route file.
    - See:
        - Registering users: Route -> POST '/api/users' @ [./routes/api/users.js](https://github.com/DariusRain/Pluto/blob/master/routes/api/users.js)
        - Logging in users: Route -> POST '/api/auth' @ [./routes/api/auth.js](https://github.com/DariusRain/Pluto/blob/master/routes/api/auth.js)

```javascript
    // EXAMPLE: Password hashing with bcryptjs

    // NEEDED IN BOTH FILES
    const bcrypt = require("bcryptjs");

    // FILE: ./routes/api/users.js (ROUTE FILE)

    // Generate random string to add to hash for security reasons.
    const salt = await bcrypt.genSalt(10);

    // Hash the password and assign it to the user object.
    user.password = await bcrypt.hash(password, salt);

    // -----------------------------------------------------

    // FILE: ./routes/api/auth.js (ROUTE FILE)
    // See if hashed password is correct with bcrypt.compare(pass, hashedPass)

    // - 'password': would come from the body of the request.

    // - 'user.password': would come from a variable that has a user document as the value after
    // searching the Users collection for a matching email which value is from body of the request along with the password
    // used in the first argument.
    const isMatch = await bcrypt.compare(password, user.password);

    // If there is no match bewtween passwords.
    if (!isMatch) {
      return res.status(400).json({ errors: [{ msg: "Invalid Credentials" }] });
    }

    // Continue the process
```
&nbsp;
&nbsp;
