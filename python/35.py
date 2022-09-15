from math import floor, sqrt


def is_almost(n, m, d=1):
    return n <= m + d and n >= m - d


def isqrt_builtin(n):
    return floor(sqrt(n))


assert [isqrt_builtin(n) for n in range(30)] == \
    [0, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3,
        3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5], "Erreur isqrt_builtin"


def isqrt_hard(n):
    test_nb = 0
    while test_nb*test_nb <= n:
        test_nb += 1
    return test_nb - 1


def isqrt_sum(n):
    test_nb = 0
    sq = 0
    while sq <= n:
        test_nb += 1
        sq += 2 * test_nb - 1

    return test_nb - 1


def isqrt_dicho(n, a=0, b=100):
    def f(x, n):
        return x*x-n

    mid = (a + b) // 2

    while not is_almost(f(mid, n), 0, 0):
        print(f(mid, n), n)
        if f(a, n)*f(mid, n) < 0:
            b = mid
        elif f(b, n)*f(mid, n) < 0:
            a = mid
        else:
            return a if f(a, n) == 0 else b
    return mid


def final_check(fs):
    for f in fs:
        for n in range(100):
            assert f(n) == isqrt_builtin(
                n), f"Erreur {f.__name__} ({f(n)} != {isqrt_builtin(n)})"


final_check([isqrt_builtin, isqrt_hard, isqrt_sum, isqrt_dicho])
