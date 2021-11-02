import sys
import csv


def main():
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    with open(sys.argv[2], 'r') as f:
        dna = f.read()

    data = sys.argv[1]
    base = database(data)

    first = base[0]
    STR = getting_STR(first)

    recognize = {}

    for s in STR:
        counts = {s: 0}
        recognize.update(checking_STR(dna, s, counts))

    for r in recognize:
        recognize[r] = str(recognize[r])

    checking(base, recognize)


def checking(base, recognize):
    i = 0
    while i < len(base):
        counts = 0
        for key in recognize:
            if recognize[key] == base[i][key]:
                counts += 1
        if counts == len(recognize):
            print(base[i]['name'])
            i = len(base)
        elif counts != len(recognize) and i == len(base) - 1:
            print("No match")
            i += 1
        else:
            i += 1


def database(data):

    dna = []
    with open(data) as file:
        reader = csv.DictReader(file)
        for row in reader:

            dna.append(row)

    return dna


def getting_STR(data):
    key = list(dict.keys(data))
    STR = []
    for i in range(1, len(key)):
        STR.append(key[i])

    return STR


def checking_STR(a, b, counts):
    i = 0
    count = 0
    while i <= (len(a)-len(b)):
        if a[i:i+len(b)] == b:
            count += 1
            i = i+len(b)

            if count > counts[b]:
                counts[b] = count
        else:
            count = 0
            i += 1

    return counts

main()

