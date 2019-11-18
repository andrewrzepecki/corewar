import sys
import filecmp
import difflib
import subprocess

champ1 = "champs/ldi.cor"
champ2 = "champs/ldi.cor"

def get_diff():

    file1 = open("tests/zaz.txt", 'r')
    file2 = open("tests/nous.txt", 'r')

    if filecmp.cmp("tests/zaz.txt", "tests/nous.txt") == False:
        text1 = file1.readlines()
        text2 = file2.readlines()
        for line in difflib.unified_diff(text1, text2):
            print(line)
        file1.close()
        file2.close()
        return 1

    file1.close()
    file2.close()
    return 0

if __name__ == "__main__":

    if len(sys.argv[1:]) != 2:
        print("Usage : python check.py [start] [end]\nstart et end sont des entiers correspondant aux cycles a tester")
        exit(0)

    start = int(sys.argv[1]) 
    end = int(sys.argv[2])
    for i in range(start, end + 1):
        with open("tests/zaz.txt", 'w') as fzaz: # Pour output la version de zaz
            subprocess.call([".././corewar", "-d", str(i), champ1, champ2], stdout=fzaz)
        with open('tests/zaz.txt', 'r') as fin: # Pour retirer les lignes de declaration des champions
            data = fin.read().splitlines(True)
        with open('tests/zaz.txt', 'w') as fout: # Pour retirer les lignes de declaration des champions
            fout.writelines(data[3:])

        with open("tests/nous.txt", 'w') as fnous: # Pour output notre version
            subprocess.call(["./corewar", "-dump", str(i), champ1, champ2], stdout=fnous)

        if get_diff():
            print("\033[93m-----LA DIFFERENCE SE TROUVE AU CYCLE {}-----".format(i))
            exit(0)