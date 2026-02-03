import math
import re


def main():
    text = input("Text: ")

    letters   = count_letters(text)
    words     = count_words(text)
    sentences = count_sentences(text)

    # Coleman-Liau index
    # L = average letters per 100 words
    # S = average sentences per 100 words
    L = (letters / words) * 100
    S = (sentences / words) * 100

    index = 0.0588 * L - 0.296 * S - 15.8

    # Round to the nearest integer
    grade = round(index)

    # Clamp and print
    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


def count_letters(text):
    """Count only alphabetic characters (a-z, A-Z)."""
    return sum(1 for ch in text if ch.isalpha())


def count_words(text):
    """A word is any sequence of characters separated by spaces."""
    return len(text.split())


def count_sentences(text):
    """A sentence ends with '.', '!' or '?'."""
    return sum(1 for ch in text if ch in ".!?")


if __name__ == "__main__":
    main()
