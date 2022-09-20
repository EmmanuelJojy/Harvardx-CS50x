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
        # j iterates over STR s
        for j in STR.keys():
            if int(data[i][j]) != STR[j]:
                break
            else:
                continue
        else:
            print(i)
            exit(1)
            break
    print("No match")
    exit(0)


def load(loc_data, loc_seq):
    global data, STR, seq
    with open(loc_data, 'r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            s = row['name']
            del(row['name'])
            data[s] = row.copy()
        for i in row.keys():
            STR[i] = 0

    with open(loc_seq, 'r') as fh:
        seq = fh.readline()


def comp():

    for s in STR.keys():
        count = 0
        i = 0
        while i < len(seq) - len(s) + 1:

            if seq[i: i + len(s)] == s:
                count += 1
                i += len(s)
            else:
                #print(f"ELSE :: {seq[i: i + len(s)]}")
                if count > STR[s]:
                    STR[s] = count
                count = 0
                i += 1

        if count > STR[s]:
            STR[s] = count


main()