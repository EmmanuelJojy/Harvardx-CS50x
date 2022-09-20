# TODO
from cs50 import SQL
from sys import argv, exit
import csv

# Connecting to database students.db
db = SQL("sqlite:///students.db")


def main():

    # Validating command line arguments
    if len(argv) != 2:
        print("Usage: python import.py filename.csv")
        exit(1)

    # Initializing database
    db.execute("DELETE FROM students")

    # Reading csv file provided
    with open(argv[1], "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            name = row['name'].split(' ')
            house = row['house']
            birth = int(row['birth'])

            # Checking if middle name present
            if len(name) != 3:
                name = [name[0], None, name[1]]

            # Inserting to database
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                       name[0], name[1], name[2], house, birth)

    # Successful termination
    exit(0)


# Driver code
main()