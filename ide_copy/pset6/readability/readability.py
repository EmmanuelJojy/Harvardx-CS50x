from cs50 import *

# String input from user
text = get_string("Text: ")

# Initializing letters l, words w, sentences s
l, w, s = 0, 1, 0

# Iterating over every character in text
for i in range(len(text)):
    # If letter
    if text[i].isalpha():
        l += 1
    # If end of a word
    elif text[i] == ' ':
        w += 1
    # If end of sentence
    elif text[i] in ['.', '?', '!']:
        s += 1
    # If unidentified character continue
    else:
        continue

# Calculating Coleman-Liau index
# Index = 0.0588 * L - 0.296 * S - 15.8
i = 0.0588 * (l / w) * 100
i -= 0.296 * (s / w) * 100
i -= 15.8

# Rounding grade to nearest whole number
i = round(i)

# Printing based on obtained result
if i < 1:
    print("Before Grade 1")
elif i >= 16:
    print("Grade 16+")
else:
    print(f"Grade {i}")