from sys import _clear_type_cache
from timeit import timeit

import ngram_score as ns


def print_grille(alph):
    print(f"    {' '.join(alph)}")
    print(f"---{'-'*len(alph)*2}")
    for i in range(len(alph)):
        print(f"{alph[i]} | {' '.join(alph[i:] + alph[:i])}")


# print_grille(["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N",
#               "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"])


def crypt(msg, key, decript=False):
    out = ""
    key = key * (len(msg)//len(key) + 1)
    for i in range(len(msg)):
        offset = (ord(msg[i]) + (-1 if decript else 1) * ord(key[i])) % 26
        out += chr(65 + offset)
    return out


def crypt2(msg, key, decript=False):
    return "".join([chr(65 + (ord(msg[i]) + (-1 if decript else 1) * ord((key * (len(msg)//len(key) + 1))[i])) % 26) for i in range(len(msg))])


LOREM = "LOREMIPSUMDOLORSITAMETCONSECTETURADIPISCINGELITDONECATLACUSNEQUECLASSAPTENTTACITISOCIOSQUADLITORATORQUENTPERCONUBIANOSTRAPERINCEPTOSHIMENAEOSNAMVELBLANDITPURUSNUNCUTELITEUFELISAUCTORMOLESTIEATSEDLACUSPELLENTESQUEHABITANTMORBITRISTIQUESENECTUSETNETUSETMALESUADAFAMESACTURPISEGESTAS"

assert crypt(crypt(LOREM, "IAMTHEKEY"), "IAMTHEKEY", True)\
    == LOREM

assert crypt2(crypt2(LOREM, "IAMTHEKEY"), "IAMTHEKEY", True)\
    == LOREM

fitness = ns.ngram_score()

assert fitness.score('THISISACOHERENTSENTENCE')\
    > fitness.score('LKFJLSDFJIOJZOJMIOFJNZA')


def check(c, k):
    return fitness.score(crypt(c, k, True))


def checkLenNRec(c, n, prefix=''):
    if n == 0:
        return prefix
    starts = [prefix + chr(65+i)*n for i in range(26)]

    best_comb = starts[0]
    best_score = check(c, starts[0])

    for start in starts:
        for i in range(26):
            key = start[:len(prefix)] + chr(65 + i) + start[len(prefix) + 1:]
            score = check(c, key)
            if score > best_score:
                best_score = score
                best_comb = key

    return checkLenNRec(c, n-1, best_comb[:len(prefix)+1])


def checkLenNIte(c, n):
    prefix = ''
    best_score = -1 * float("inf")
    best_comp = ""

    for pivot in range(n):
        for fill in [chr(65+i)*(n-len(prefix) - 1) for i in range(26)]:
            for char in [chr(65+i) for i in range(26)]:
                comb = prefix + char + fill
                score = check(c, comb)
                if score > best_score:
                    best_score = score
                    best_comp = comb
        prefix = best_comp[:pivot + 1]

    return prefix


def checkLenNForce(c, n):
    best_score = -1 * float("inf")
    best_comb = ""

    for i in range(26 ** n):
        comb_offsets = [(i // (26 ** j)) % 26 for j in range(n)]
        comb = "".join([chr(65 + offset) for offset in comb_offsets])
        score = check(c, comb)
        if score > best_score:
            best_score = score
            best_comb = comb

    return best_comb


def autobreak(c, n):
    for i in range(1, n):
        key = checkLenNRec(c, i)
        # key = checkLenNIte(c, i)
        # key = checkLenNForce(c, i)

        decode = crypt(c, key, True)
        print(f"{key:>{n}} {decode} {fitness.score(decode)}")


msg1 = "THESTUDENTSARENICEANDHARDWORKING"
key1 = "ORARETHEY"
cyp1 = crypt(msg1, key1)


autobreak(cyp1, 10)


# TODO : en parler au prof pour trouver l'astuce
