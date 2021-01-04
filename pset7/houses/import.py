# https://cs50.harvard.edu/x/2020/psets/7/houses/#specification
import sys
import csv
from cs50 import SQL

# @main()
# Executes function calls that make up entire task as whole this file
# This file's task is to import data from a csv file into a table located in a sql database file.


def main():

    # This will take commandline argument to filename and open that csv file then pass it as argument to
    # the insert method that will do the final job of importation.
    return insertStudents(selectSpreadSheet())

# @selectSpreadSheet()
# Returns a dictionary of the csv file containing the students.


def selectSpreadSheet():
    # Get input arguments array from command line
    inputArgs = sys.argv

    # If invalid arguments then exit program
    if (2 < len(inputArgs)):
        print("Invalid argument(s): ", inputArgs[2:])
        return sys.exit()

    # Return dictionary of filename given.
    try:
        return csv.DictReader(open(inputArgs[1], newline="", encoding="UTF-8"), delimiter=",")
    except FileNotFoundError:
        print("No such file:", inputArgs[1])
        sys.exit()
# @connectDatabase(path)
# Connect database with path to database file


def connectDatabase(path):
    try:
        # Returns the connection where you can then execute querys
        return SQL(path)
    except:
        # Display error if no connection can be made with given path.
        print("Cannot find path to database:", path)
        return sys.exit()

# @insertStudents(spreadSheet)
# Responsible for inserting the contents of the csv spread sheet into the students table
# in database


def insertStudents(spreadSheet):
    # Assign connection object to variable for further insertions
    connection = connectDatabase("sqlite:///students.db")

    # Variable that contains ID of student
    idOf = connection.execute("SELECT MAX(ID) AS ID_START FROM STUDENTS")[0]["ID_START"]

    if not idOf:
        idOf = 1
    else:
        idOf = idOf + 1

    # Return array
    result = []
    # For each row in csv file
    for row in spreadSheet:

        # Temp dict that contains data of student
        student = {}

        # For each key [NAME, HOUSE, BIRTH]
        for key in [*row.keys()]:

            # If name Parse into three values to be added to student dictionary
            if(key == "name"):
                name = parseName(row[key])
                student["first"] = name[0]
                student["middle"] = name[1]
                student["last"] = name[2]
            # Else if it is not name then keys and values are as wanted
            else:
                student[key] = row[key]

        # Add id to student
        student["id"] = idOf
        # SQL query that inserts the values from student dictionary by each key and value
        query = (f"""
        INSERT INTO STUDENTS(
            ID, FIRST, MIDDLE,
            LAST, BIRTH, HOUSE
        )
        VALUES(
            '{student['id']}', '{student['first']}', { "'" + student['middle'] + "'" if student['middle'] != None else "NULL"},
            '{student['last']}', {student['birth']}, '{student['house']}'
        )
        """)

        # Execute the above query
        connection.execute(query)

        # Increment new unique id
        idOf += 1

        result.append(student)

    return result

# parseName()
# Responsible for returning an array with 3 indexes representing first middle and last names
# if no last name is provided then middle name will be NULL


def parseName(name):
    strArr = name.split(" ")

    # If string only has two words, can assume first and last. Add NULL as middle name
    if (len(strArr) == 2):
        strArr.insert(1, None)

    # If middle name is included then return result is ready to go.
    return strArr



main()