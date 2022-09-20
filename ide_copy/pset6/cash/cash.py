from cs50 import *

# Input loop
while True:
    # Using cs50.get_int to handle float
    # and non float inputs
    dollars = get_float("Change owed: ")
    if dollars >= 0.0:
        break
    
# Taking only two places of digits 
# after decimal point to account
cents = round(dollars * 100)

# Initializing coins to 0
coin = 0

# Checking remaining cents after giving coins
if (cents // 25 >= 1):
    n = cents // 25
    coin += n
    cents -= (n * 25)
if (cents // 10 >= 1):
    n = cents // 10
    coin += n
    cents -= (n * 10)
if (cents // 5 >= 1.0):
    n = cents // 5
    coin += n
    cents -= (n * 5)

# Accomodating rest with 1 cent coin
coin += cents

# Printing
print(f"{coin}")