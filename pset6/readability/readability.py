import re
import math

while(True):
    # text = string of user input
    text = input("Text: ")

    # letters = regex matches of all single alphabetic characters.
    letters = len(re.findall("[a-zA-Z]", text))

    # words = regex matches of spaces and plus one for the firstword that was uncounted.
    words = len(re.findall(" ", text)) + 1

    # sentences = regex matches of all characters that indicate an end of a sentence (. ! ?)
    sentences = len(re.findall("[\.|!|?]", text)) - len(re.findall("Mr.|Ms.", text))

    # Re ask if no letters
    if (letters == 0):
        continue

    # Liou = output after finding the above values, must round the float.
    liou = round(0.0588 * (100 * (letters / words)) - 0.296 * (100 * (sentences / words)) - 15.8)

    # Debug:
    # print("Letter(s):", L)
    # print("Word(s):", W)
    # print("Sentence(s):", S)
    # print("Liou:", liou)

    # Conditionals for outputing grade level
    if (liou < 0):
        print("Before Grade 1")
        break

    if (liou < 16):
        print("Grade", liou)
        break

    if (16 < liou):
        print("Grade 16+")
        break