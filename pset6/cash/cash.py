# Import get_float
from cs50 import get_float

# Infinite loop that checks input for negatives unless breaks itself
while (True):
    # Convert to whole number representation of float
    change_owed = round(get_float("Change owed: ") * 100)
    if not change_owed < 0:
        break
# Will use this array to represent each coin.
coins = [25, 10, 5, 1]

# Initlize minimum coin variable
minimum_coins = 0

# Loop through each coin in the coins array.
for i in range(len(coins)):
    # While there is a quotient value greater than equal to one
    # meaning the change owed cannot be divided no more by the coin's value
    while (1 <= change_owed / coins[i]):
        # Scince change_owed can be divided by the coin value,
        # subtract the value from change_owed
        change_owed -= coins[i]

        # Scince change_owed was subtracted a coin value,
        # that means there is an additon of one coin used
        minimum_coins += 1


# Print the mimimum number of coins
print(minimum_coins)