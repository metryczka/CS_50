from cs50 import get_int


def get_number():
    number = get_int("Height: ")
    return number


def check_value(number):
    if number > 0 and number < 9:
        print_mario(number)
    else:
        number = get_number()
        check_value(number)


def print_mario(number):
    for i in range(1, number+1):
        print(" " * (number-i), end="")
        print("#" * i)


number = get_number()
check_value(number)