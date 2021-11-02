from cs50 import get_string


def count_letters(text):
    counter = 0
    for letters in text:
        if letters.isalpha():
            counter += 1

    return counter


def count_words(text):
    counter = 0
    for letters in text:
        if letters == " ":
            counter += 1
    return counter + 1


def count_sentences(text):
    counter = 0
    for letters in text:
        if letters == "?" or letters == "!" or letters == ".":
            counter += 1

    return counter


def grade(letters, words, sentences):

    L = letters * 100.00 / words
    S = sentences * 100.00 / words
    mark = 0.0588 * L - 0.296 * S - 15.8
    if (mark > 1 and mark <= 16):
        print(f"Grade {round(mark)}")
    elif mark < 1:
        print("Before Grade 1")
    elif mark > 16:
        print("Grade 16+")


def main():

    text = get_string("Text: ")

    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    grade(letters, words, sentences)


main()
