# TODO
from cs50 import SQL
from sys import argv, exit

# Connecting to database students.db
db = SQL("sqlite:///students.db")


def main():

    # Validating command line arguments
    if len(argv) != 2:
        print("Usage: python roster.py house")
        exit(1)

    # Extracting data from database
    l = db.execute("SELECT first, middle, last, birth FROM students WHERE house == ? \
        ORDER BY last ASC, first ASC", argv[1])

    # Iterating over extracted data
    for i in range(len(l)):
        stu = l[i]
        # Checking if middle name present
        if stu['middle'] == None:
            print(f"{stu['first']} {stu['last']}, born {stu['birth']}")
            continue
        print(f"{stu['first']} {stu['middle']} {stu['last']}, born {stu['birth']}")

    # Successful termination
    exit(0)


main()