A = {'a', 'b', 'c', 'd'}
B = {1, 2, 3}
n = 100


def prod_c(A, B):
    return {(a, b) for a in A for b in B}


assert prod_c({1, 2}, {3, 4}) == {(1, 3), (1, 4), (2, 3), (2, 4)},\
    "Erreur prod_c"

assert prod_c("abcd", B) == prod_c({'a', 'b', 'c', 'd'}, B), \
    "Erreur prod_c"


def squares(n):
    return [i**2 for i in range(1, n) if i**2 <= n]


assert squares(100) == [1, 4, 9, 16, 25, 36, 49, 64, 81, 100], \
    "Erreur squares"


def palindrome(s):
    return s == "".join([s[i-1] for i in range(len(s), 0, -1)])


assert palindrome('abba')
assert palindrome('abcba')
assert palindrome('')
assert palindrome('a')
assert not palindrome('ab')


def inverse(s):
    return [s[i-1] for i in range(len(s), 0, -1)]


assert inverse('abc') == ['c', 'b', 'a'] and inverse('') == [], \
    "Erreur inverse"


def palinv(s):
    return s == "".join(inverse(s))


assert palinv('abba')
assert palinv('abcba')
assert palinv('')
assert palinv('a')
assert not palinv('ab')


def rmfrom(s, bad):
    return [c for c in s if c not in bad]


assert rmfrom('esope reste ici et se repose', 'aeiouy ') == \
    ['s', 'p', 'r', 's', 't', 'c', 't', 's', 'r', 'p', 's'], \
    "Erreur rmfrom"


def rmspaces(s):
    return rmfrom(s, " ")


assert rmspaces('esope reste ici et se repose') == \
    ['e', 's', 'o', 'p', 'e', 'r', 'e', 's', 't', 'e', 'i', 'c', 'i', 'e', 't', 's', 'e', 'r',
     'e', 'p', 'o', 's', 'e'], \
    "Erreur rmspaces"


def palindrome_sentence(s):
    return palinv("".join(rmspaces(s)))


assert palindrome_sentence('esope reste ici et se repose')
assert not palindrome_sentence('esope reste ici et se reposes')


def fsum(f, i, j):
    return sum([f(k) for k in range(i, j+1)])


assert fsum(lambda i: i, 0, 10) == 55
assert fsum(lambda i: i**2, 0, 10) == 385


def isprime(n):
    return len([i for i in range(1, n+1) if n/i == n//i]) == 2


assert [i for i in range(100) if isprime(i)] == \
    [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41,
        43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97],\
    "Erreur isprime"

# n = 20

# TODO : cas invalide
comp = {i for i in range(2, n+1) if any([i/j == i//j for j in range(2, i-1)])}

for nb in comp:
    assert not isprime(nb), f"Erreur comp ({nb} is prime) "

comp2 = {i for j in range(2, n+1) for i in range(2*j, n+1, j)}

assert comp == comp2, "Erreur comp2"


comp3 = {i*j for i in range(2, n+1)
         for j in range(2, int(n/i) + 1)}

assert comp == comp3, "Erreur comp3"


primes = tuple(i for i in range(2, n+1) if i not in comp)

assert primes == tuple(k for k in range(1, n+1) if isprime(k))


def crange(c1, c2):
    return [chr(n) for n in range(ord(c1), ord(c2) + 1)]


assert "".join(crange('A', 'Z')) == 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'


def charrange(*args):
    assert len(args) % 2 == 0
    return crange(args[0], args[1]) + charrange(*args[2:]) if len(args) != 0 else []


assert "".join(charrange('A', 'Z', 'a', 'z', '0', '9')) == \
    'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789' and \
    "".join(charrange()) == '', \
    "Erreur charrange"
