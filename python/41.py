def upto(g, i):
    return [el for el in [next(g, None) for _ in range(i)] if el is not None]


assert list(upto((x for x in range(3)), 8)) == [0, 1, 2]
assert list(upto((n*n for n in range(100)), 7)) == \
    [0, 1, 4, 9, 16, 25, 36]


def nth(g, i):
    return [item for item in g][i]


assert all(nth(g, i) == i*i for i in range(7)
           for g in [(n*n for n in range(7))])


def powers(f, s):
    while True:
        yield s
        s = f(s)


assert list(upto((x for x in range(3)), 8)) == [0, 1, 2]
assert list(upto(powers(lambda x: 2*x, 1), 7)) == \
    [1, 2, 4, 8, 16, 32, 64]


def group(s):
    out = ''
    for i in range(len(s)):
        out += s[i]
        if i+1 >= len(s) or s[i] != s[i+1]:
            yield list(out)
            out = ''


assert list(group('')) == [], f'{list(group(""))} != []'
assert list(group('a')) == [['a']], f"{list(group('a'))} != [['a']]"
assert list(group('aaba')) == [['a', 'a'], ['b'], ['a']],\
    f"{list(group('aaba'))} != [['a', 'a'], ['b'], ['a']]"
assert list(group('aabbbcdaaaa')) == \
    [['a', 'a'], ['b', 'b', 'b'], ['c'], ['d'], ['a', 'a', 'a', 'a']],\
    f"{list(group('aabbbcdaaaa'))} != [['a', 'a'], ['b', 'b', 'b'], ['c'], ['d'], ['a', 'a', 'a', 'a']]"


def groupn(s):
    out = ''
    for i in range(len(s)):
        out += s[i]
        if i+1 >= len(s) or s[i] != s[i+1]:
            yield (len(out), out[0])
            out = ''


assert list(groupn('aabbbcdaaaa')) == \
    [(2, 'a'), (3, 'b'), (1, 'c'), (1, 'd'), (4, 'a')]


def groupl(gn):
    return [[res[1]]*res[0] for res in gn]


assert all(tuple(group(s)) == tuple(groupl(groupn(s)))
           for s in ('', 'a', 'aaba', 'aabbbcdaaaa'))


def say(s):
    return "".join([str(el[0])+el[1] for el in groupn(s)])


assert list(upto(powers(say, '1'), 7)) == \
    ['1', '11', '21', '1211', '111221', '312211', '13112221']
assert list(upto(powers(say, '22'), 7)) == \
    ['22', '22', '22', '22', '22', '22', '22']


def conway(seed='1', maxrnk=100, maxlen=30):
    gen = powers(say, seed)
    for i in range(maxrnk):
        act_ver = next(gen)
        print(
            f"{i:>3} {act_ver[:maxlen]}{f' e{len(act_ver)-maxlen}' if len(act_ver)-maxlen > 0 else ''}")

# conway()


def sayg(s):
    return (str(el) for seq in groupn(s) for el in seq)


assert list(sayg('')) == []
assert list(sayg('1')) == ['1', '1']
assert list(sayg('1211')) == ['1', '1', '1', '2', '2', '1']


def nthpowerg(f, n, s):
    if n == 0:
        return (c for c in s)
    else:
        return f("".join(nthpowerg(f, n-1, s)))


assert "".join(upto(nthpowerg(sayg, 6, "1"), 8)) == "13112221"


def conwayg(seed='1', maxrnk=100, maxlen=30):
    prev = seed
    for i in range(maxrnk):
        print(i, prev[:30])
        prev = "".join(sayg(prev))


conwayg()

# NOTE : TROP LENT ?
