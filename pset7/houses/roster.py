# https://cs50.harvard.edu/x/2020/psets/7/houses/#specification
import sys
from cs50 import SQL

# @main()
# Program task is to query the students table in the database for all students in a sertain house of class.
# For this program it is harry potter themed where houses are (Gryffindor, Slytherin etc) so this program would
# list all students by name and birth in order by last name.


def main():
    return selectByHouse(selectHouse())


# @selectHouse()
# Responsible for selecting the house name from an argument in the command line
# Validate and return house name.  If invalid then exit program with error message.


def selectHouse():
    inputArgs = sys.argv
    lengthOf = len(inputArgs)
    if (lengthOf != 2):
        print("Invalid argument(s):", "Requires one argument" if lengthOf == 0 or lengthOf == 1 else inputArgs[2:])
        sys.exit()
    return inputArgs[1]

# @selectByHouse(houseName)
# Responsible for querying the database for a houseName passed as argument.
# Then display result from selection query which is a dictionary.


def selectByHouse(houseName):
    connection = SQL("sqlite:///students.db")
    query = f'SELECT DISTINCT FIRST, MIDDLE, LAST, BIRTH FROM STUDENTS WHERE HOUSE LIKE "{houseName}" ORDER BY LAST'
    students = []
    for student in connection.execute(query):
        students.append(displayStudent(student))
    return students
# @parseName
# Returns student's name as a whole either first last or first middle last


def parseName(student):
    return student['first'] + " " + (student['middle'] + " " if student['middle'] else "") + student['last']

# @displayStudent
# Displays the required contents of each student dictionary by name and birth and in order by last name


def displayStudent(student):
    print(parseName(student) + ", born", student['birth'])
    if student['middle'] == 'NULL':
        student['middle'] = None
    return student


main()