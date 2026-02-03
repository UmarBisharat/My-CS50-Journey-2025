import csv
import sys


def main():
    # ---------- Validate command-line arguments ----------
    if len(sys.argv) != 3:
        print("Usage: python dna.py database.csv sequence.txt")
        sys.exit(1)

    # ---------- Read the CSV database into memory ----------
    # Each row becomes a dict: {"name": "Alice", "AATG": "28", ...}
    database = []
    with open(sys.argv[1]) as csv_file:
        reader = csv.DictReader(csv_file)
        strs = reader.fieldnames[1:]      # column headers minus "name" → the STR sequences
        for row in reader:
            database.append(row)

    # ---------- Read the DNA sequence (single long string) ----------
    with open(sys.argv[2]) as seq_file:
        sequence = seq_file.read().strip()

    # ---------- For every STR, compute longest consecutive run in the sequence ----------
    str_counts = {}
    for str_seq in strs:
        str_counts[str_seq] = longest_run(sequence, str_seq)

    # ---------- Compare computed counts against every person in the database ----------
    for person in database:
        match = True
        for str_seq in strs:
            # Database values are strings; compare as integers
            if int(person[str_seq]) != str_counts[str_seq]:
                match = False
                break
        if match:
            print(person["name"])
            sys.exit(0)

    # No person matched
    print("No match")


def longest_run(sequence, str_seq):
    """
    Return the longest number of consecutive, non-overlapping repeats
    of str_seq found anywhere in sequence.

    Algorithm: slide through sequence one character at a time.
    Whenever str_seq is found at the current position, count how many
    times it repeats back-to-back, then jump past all of them.
    Track the maximum count seen.
    """
    max_count = 0
    str_len   = len(str_seq)
    i         = 0

    while i <= len(sequence) - str_len:
        if sequence[i:i + str_len] == str_seq:
            # Found the start of a run — count consecutive repeats
            count = 0
            while sequence[i:i + str_len] == str_seq:
                count += 1
                i     += str_len
            if count > max_count:
                max_count = count
        else:
            i += 1

    return max_count


if __name__ == "__main__":
    main()
