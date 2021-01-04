# Mario (Less Comfortable)
from cs50 import get_int

# Get height until desired input
while (True):
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break

# Loop through height with range(INPUT)
for i in range(height):

    # Calculate number of spaces and hashes
    spaces = height - 1 - i
    hashes = i + 1

    # Use mutliply trick and set end to an empty string to prevent new line
    print(" " * spaces, end="")
    print("#" * hashes, end="")
    print("")
