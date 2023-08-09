import csv
import sys


def main():
    n = len(sys.argv)
    k = 1
    final_recursion = 0
    if n != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        return 0

    seq = open(sys.argv[2], 'r')
    readed_seq = seq.read()

    with open(sys.argv[1], newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        num_seqs = len(reader.fieldnames)
        for row in reader:
            k = 1
            for x in range(2, num_seqs+1):
                turn = longest_match(readed_seq, reader.fieldnames[x-1])
                if turn == int(row[reader.fieldnames[x-1]]):
                    k = k+1
                #print(f"{row['name']} has of {turn}. The real value should be {row[reader.fieldnames[x-1]]} also k is {k}")
            if k == len(reader.fieldnames):
                print(row['name'])
                final_recursion = final_recursion + 1
    if final_recursion == 0:
        print("No Match\n")
    return

# Harry,46,49,48,29,15,5,28,40


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
