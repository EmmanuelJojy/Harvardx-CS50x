# sys.argv for command line arguments
# sys.exit() for immediate termination
from sys import argv, exit

# For use of csv module
import csv

# data stores csv content as dict
data = {}

# str stores STR repetitions longest
STR = {}

# seq loads contents from text file
seq = ''


def main():

    # Check for correct set of arguments
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(0)

    # Sending file locations to load
    load(argv[1], argv[2])

    # Computing STR sequences
    comp()

    # i iterates over each name
    for i in data.keys():
        # j iterates over STR sequences
        for j in STR.keys():
            # Comparing sequences
            if int(data[i][j]) != STR[j]:
                break
        # else executed on successful completion
        # of for loop
        else:
            # Printing name if match found
            print(i)
            exit(1)
    # In case no match was found
    print("No match")
    exit(0)

# load() sets values for data dict and seq str
# initializes STR dict


def load(loc_data, loc_seq):

    # Using global values
    global data, STR, seq

    # with facilitates temporary opening
    # Refer csv module docs
    with open(loc_data, 'r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            s = row['name']
            del(row['name'])
            data[s] = row.copy()

        for i in row.keys():
            STR[i] = 0

    # Refer file handling
    with open(loc_seq, 'r') as fh:
        seq = fh.readline()

# Computes STR sequences
# Mutates STR.values() only


def comp():

    # s indicates an STR sequence eg: AGTA
    for s in STR.keys():
        count = 0
        i = 0

        # Iterating with respect to len of s
        while i < len(seq) - len(s) + 1:

            # Check if sequence match
            if seq[i: i + len(s)] == s:
                count += 1
                # Locating next sequence
                i += len(s)
            else:
                # If next sequence match fails
                # check if that was longest continuous
                # sequence. If yes update STR
                if count > STR[s]:
                    STR[s] = count
                # Reset value
                count = 0
                i += 1

        # Leak out check
        if count > STR[s]:
            STR[s] = count


main()