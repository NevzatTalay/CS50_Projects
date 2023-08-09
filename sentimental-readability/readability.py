from cs50 import get_string


def main():
    s = get_string("Text: ")
    # I do not need to assign them to certain variables but it looks more elegant in that way
    numberofletters = count_letters(s)
    numberofwords = count_words(s)
    numberofsentences = count_sentences(s)
    L = 100 * (numberofletters / numberofwords)
    S = 100 * (numberofsentences / numberofwords)
    # Calculate the Coleman-Liau index
    index = 0.0588 * L - 0.296 * S - 15.8
    if round(index) <= 1:
        print("Before Grade 1")
    elif round(index) >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(index)}")


def count_letters(n):
    # Code: ((text[i] <= 90 && 65 <= text[i]) || (text[i] <= 122 && 97 <= text[i])) is the C version
    counter = 0
    for i in range(0, len(n), 1):
        if ((ord(n[i]) <= 90 and 65 <= ord(n[i])) or (ord(n[i]) <= 122 and 97 <= ord(n[i]))):
            counter = counter + 1
    return counter


def count_words(n):
    # I used a predefined function here. Split uses specific character to cut string into piece. Then All I need was to count the number of pieces.
    t = n.split()
    return len(t)


def count_sentences(n):
    # Code: if ((text[i] == '.') || (text[i] == '?') || (text[i] == '!'))    is the C version.
    counter = 0
    for i in range(0, len(n), 1):
        if (n[i] == '.' or n[i] == '?' or n[i] == '!'):
            counter = counter + 1
    return counter


main()
