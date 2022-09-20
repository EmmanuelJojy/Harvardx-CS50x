from cs50 import * 

# Input loop
while True:
    # Using cs50.get_int to handle integral
    # and non integral inputs
    n = get_int("Height: ")
    if n > 0 and n < 9:
        break

# Printing pattern
for i in range(n):
    
    # Printing prefixed spaces
    for j in range(n - i - 1):
        print(" ", end="")
        
    # Printing #
    for j in range(i + 1):
        print("#", end="")
        
    # Adding new line at the end
    print()
