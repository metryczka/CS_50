from cs50 import get_string


def get_input():
    card = get_string("Number: ")
    if len(card) == 15 or len(card) == 16 or len(card) == 13:
        number = int(card)
        length = len(card)

        return number, length, card
    else:
        print("INVALID")


def checking(number, length):
    digits = []
    second = []
    suma = 0
    for i in range(length):
        digits.append(int(number % 10))
        number = number / 10

    for a in range(1, length, 2):
        second.append(digits[a]*2)

    for c in range(len(second)):
        if second[c] > 9:
            suma += int(second[c] % 10)
            suma += int(second[c]/10)

        else:
            suma += second[c]

    for b in range(0, length, 2):
        suma += (digits[b])

    if (suma % 10) == 0:
        return True
    else:
        return False


def kind_checking(card, length):
    if length == 15 and card[0] == "3" and (card[1] == "4" or card[1] == "7"):
        print("AMEX")
    elif length == 16 and card[0] == "5" and (card[1] == "1" or card[1] == "2" or card[1] == "3" or card[1] == "4" or card[1] == "5"):
        print("MASTERCARD")
    elif (length == 13 or length == 16) and card[0] == "4":
        print("VISA")
    else:
        print("INVALID")


number, length, card = get_input()

if checking(number, length):
    kind_checking(card, length)
else:
    print("INVALID")