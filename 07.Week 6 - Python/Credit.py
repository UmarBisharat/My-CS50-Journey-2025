import sys


def main():
    # Prompt the user for a credit card number (accept as string to preserve leading zeros)
    while True:
        try:
            number = int(input("Number: "))
            if number > 0:
                break
        except ValueError:
            pass

    # Convert to string for easy digit manipulation
    digits = str(number)
    length = len(digits)

    # ---------- Luhn's Algorithm ----------
    # Starting from the second-to-last digit, double every other digit
    total = 0
    for i, ch in enumerate(reversed(digits)):
        d = int(ch)
        if i % 2 == 1:          # every second digit from the right (0-indexed)
            d *= 2
            if d > 9:
                d -= 9          # equivalent to summing the two resulting digits
        total += d

    # If the total does not end in 0, the number is invalid
    if total % 10 != 0:
        print("INVALID")
        return

    # ---------- Identify the card brand ----------
    # AMEX:        starts with 34 or 37, length 15
    # MASTERCARD:  starts with 51-55,    length 16
    # VISA:        starts with 4,        length 13 or 16

    if length == 15 and digits[:2] in ("34", "37"):
        print("AMEX")
    elif length == 16 and 51 <= int(digits[:2]) <= 55:
        print("MASTERCARD")
    elif digits[0] == "4" and length in (13, 16):
        print("VISA")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()
