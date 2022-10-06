from math import floor, sqrt
from timeit import timeit


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
    mid = (a + b) // 2

    while mid*mid > n or (mid+1)*(mid+1) <= n:
        if mid*mid > n:
            b = mid
        elif (mid+1)*(mid+1) <= n:
            a = mid
        else:
            return mid
        mid = (a + b) // 2

    return mid


def isqrt_dicho_rec(n, a=0, b=100):
    mid = (a + b) // 2

    if(mid*mid <= n and (mid+1)*(mid+1) > n):
        return mid
    elif mid*mid > n:
        return isqrt_dicho_rec(n, a, mid)
    else:
        return isqrt_dicho_rec(n, mid, b)


def final_check(fs):
    for f in fs:
        for n in range(100):
            assert f(n) == isqrt_builtin(
                n), f"Erreur {f.__name__} ({f(n)} != {isqrt_builtin(n)})"


def time_all(fs, N):
    for f in fs:
        print(f"{f.__name__} : {timeit(lambda: f(1000000), number=N) / N}s")


fs = [isqrt_builtin, isqrt_hard, isqrt_sum,
      isqrt_dicho, isqrt_dicho_rec]


final_check(fs)
time_all(fs, 10000)
