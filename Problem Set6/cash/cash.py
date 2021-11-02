from cs50 import get_float


def get_input():
    change = get_float("Change owed: ")
    return change


def checking_input(change):
    if change > 0:
        change = round(change * 100)
        counts = counting(change)
        return counts
    else:
        get_input()


def counting(change):
    counts = 0
    while change > 0:
        if change >= 25:
            change -= 25
            counts += 1
        elif change < 25 and change >= 10:
            change -= 10
            counts += 1
        elif change < 10 and change >= 5:
            change -= 5
            counts += 1
        elif change < 5 and change >= 1:
            change -= 1
            counts += 1
    return counts


def main():

    change = get_input()
    counts = checking_input(change)
    print(counts)


main()
