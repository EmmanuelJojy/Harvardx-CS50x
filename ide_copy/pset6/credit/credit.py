from cs50 import *

# Translation from pset1
# Card no. input
while True:
    n = get_int("Number: ")
    if n > 0:
        break

# Initializing all temporary values    
copy, copy1, l, flag = 0, n, 0, 0

# Reversing
while n != 0:
    copy = (copy * 10) + (n % 10)
    n = n // 10
    # Computing length as l
    l += 1

# Preliminary test
if copy % 100 in [43, 73] and l == 15:
    name = "AMEX"
elif copy % 100 in [15, 25, 35, 45, 55] and l == 16:
    name = "MASTERCARD"
elif copy % 10 == 4 and (l == 13 or l == 16):
    name = "VISA"
else:
    # Incase all test cases fail
    flag = 1

# Initializing s to 0
s = 0

# Luhn algorithm implementation
while (copy1 != 0):

    # Adding non doubled elements to s
    s += (copy1 % 10)
    copy1 //= 10

    # Doubling every other digit
    i = (copy1 % 10) * 2
    while (i != 0):
        # Splitting doubled elements
        s += (i % 10)
        i //= 10
    copy1 //= 10

# Final check for compatibility
if (s % 10 == 0 and flag != 1):
    print(f"{name}")
else:
    print("INVALID")
