# https://cs50.harvard.edu/x/2020/psets/6/dna/
import sys
import csv
import re

# @main()
# - Runs the test and check if the result is None then returns "No match" otherwise returns the name of person


def main():
    return ifNoMatch(runTest())


# @runTest()
# - Returns a name of person who matches or None
def runTest():
    # @inputArgs
    # Take in input arguments as an array of string and or int, from the commandline. (i.e. "python dna.py file-a file-b")
    inputArgs = sys.argv

    # @dnaDatabase
    # - inputArgs[1]: .csv file
    # Uses the file name as command line argument 2 which equals args[1] because this python file would be args[0].
    # Then it opens the file by the name given and will be passed to csv.reader() which will in return will be a dictionary.
    dnaDatabase = csv.DictReader(open(inputArgs[1], newline='', encoding="UTF-8"), delimiter=',')

    # @dnaSample
    # - inputArgs[2]: .txt file
    dnaSample = open(inputArgs[2], newline='', encoding="UTF-8").read()

    # Loop through each column in csv file
    for column in dnaDatabase:
        # @typeCount
        # - Records the number of DNA types have been iterated through, will help me know if all of them have been tested meaning a match.
        typeCount = 0

        # DEBUG: Name of person that is currently being processed
        # print(column["name"], "\n\n")

        # DEBUG: Show array of DNA types
        # print([*column.keys()][1:])
        for dnaType in [*column.keys()][1:]:
            typeCount += 1

            # DEBUG: See what DNA type is currently gettign searched for
            # print("\tOn DNA type:", dnaType, "\n")

            # @regex
            # - Pattern that looks for repeated dnaType string repeated exactly n times, n being the value of repeated the person is supposed to have.
            # - Example: (AGATC){18}
            regex = "(" + dnaType + ")" + "{" + column[dnaType] + "}"

            # @match
            # - Search dna sample for a match with the regex above and assign either None or a MatchObject
            match = re.search(regex, dnaSample)

            # If there is no match which re.search() would return None. Break the loop and on to the next
            # Breaking the loop becuase there is no way this person matches the sample and further iteration would be unneccessary runtime
            if match == None:
                break

            # Else that means we have a possible match, becuase there could be trailing repeats of the sequence.
            else:
                # @span
                # - Make use of MatchObject.span() to find the indexes in the DNA sample where the pattern starts and ends
                span = match.span()

                # If there is a trailing repeat then break for no match
                if (dnaSample[span[1]: span[1] + len(dnaType)] == dnaType):
                    break

                # If no break from above and typeCount equals the length of DNA types meaning we ran all the results with no breaks thus meaning it is a match!
                # return the name which stops any further testing becuase I can assume there is no one else with the same DNA.
                if typeCount == len([*column.keys()][1:]):
                    return column["name"]

# @ifNoMatch(result)
# - Checks if the result from the @runTest() method expected as argunment is equal to None so "No match" can be returned else returns the result given.


def ifNoMatch(result):
    if (result == None):
        return "No match"
    else:
        return result


print(main())