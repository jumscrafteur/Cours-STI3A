from datetime import date


def is_almost(n, m, d=1):
    return n <= m + d and n >= m - d


def is_leap(y, m, d):
    return (y % 4 == 0 and y % 100 != 0) or (y % 400 == 0)


assert [is_leap(y, 0, 0) for y in [1900, 2000, 2020, 2022, 2024, 2100]] ==\
    [False, True, True, False, True, False]


def days_in_month(y, m, d):
    match m:
        case 2: return 28 + 1*is_leap(y, m, d)
        case 4 | 6 | 9 | 11: return 30
        case _: return 31


def is_valid_date(y, m, d):
    return(1 <= m <= 12) and (1 <= d <= days_in_month(y, m, d))


assert [is_valid_date(*date)
        for date in [(2015, 29, 2), (2015, 2, 29), (2022, 9, 29)]] == [False, False, True]


def days_between_approx(y, m, d, Y, M, D):
    return (Y - y) * 365.2425 + (M-m)*30.5 + D-d


def days_between(y, m, d, Y, M, D):
    (y, Y, factY) = (y, Y, 1) if Y-y > 0 else (Y, y, -1)
    (m, M, factM) = (m, M, 1) if M-m > 0 else (M, m, -1)
    (d, D, factD) = (d, D, 1) if D-d > 0 else (D, d, -1)

    return factY * sum([366 if is_leap(year, 0, 0) else 365 for year in range(y+1, Y+1)]) +\
        factM * sum([days_in_month(Y, i, 1) for i in range(m, M)]) +\
        factD * (D-d)


assert days_between(1985, 10, 21, 1985, 10, 21) == 0
assert days_between(1985, 10, 20, 1985, 10, 21) == 1
assert days_between(1985, 10, 21, 1985, 10, 20) == -1
assert days_between(1985, 10, 21, 2017, 9, 19) == 11656
assert days_between(2017, 9, 19, 1985, 10, 21) == -11656
assert days_between(1999, 12, 5, 2000, 3, 1) == 87


def weekday(y, m, d):
    return days_between(1899, 12, 31, y, m, d) % 7


assert weekday(1900, 1, 1) == 1
assert weekday(1985, 10, 21) == 1
assert weekday(2017, 9, 19) == 2
assert weekday(1899, 12, 31) == 0
assert weekday(1700, 1, 1) == 5
assert weekday(2019, 9, 14) == 6


def cal(y, m, weekday=weekday):
    print("di lu ma me je ve sa")
    offset = weekday(y, m, 1)
    days = days_in_month(y, m, 0)
    out = ""
    for i in range(-offset + 1, days + 1):
        out += "   " if i <= 0 else f"{f'{i}':>2} "
        out += "\n" if i % 7 == 1 else ""
    print(out)


def cal2(y, m, weekday=weekday):
    print("di lu ma me je ve sa\n" +
          "\n".join([
              " ".join([
                  "  " if i <= 0 else f"{f'{i}':>2}" for i in range(first, min(days_in_month(y, m, 0)+1, first + 7))
              ])
              for first in range(-weekday(y, m, 1) + 1, days_in_month(y, m, 0) + 1, 7)
          ]))


# cal(2018, 9)
# cal2(2018, 9)


def weekday_delambre(y, m, d):
    codes = [3 if is_leap(y, m, d) else 4,
             6 if is_leap(y, m, d) else 0, 0, 3, 5, 1, 3, 6, 2, 4, 0, 2]
    ypp = y // 100
    yp = y % 100
    return (d+codes[m-1]+int(21*ypp/4)+int(5*yp/4)+2) % 7


assert weekday_delambre(2022, 9, 29) == 4
assert weekday_delambre(1985, 10, 21) == 1

SKIPTEST1 = True

assert SKIPTEST1 or all([
    weekday_delambre(y, m, d) == weekday(y, m, d)
    for y in range(1900, 2101)
    for m in range(1, 13)
    for d in range(1, days_in_month(y, m, 0)+1)
])


def approxrat(*p):
    ex = days_between(*p)
    ap = days_between_approx(*p)
    return ap/ex


assert is_almost(approxrat(1985, 10, 21, 2020, 9, 19), 1, 0.0001)
assert is_almost(approxrat(1800, 1, 1, 2100, 1, 1), 1, 0.000005)
assert approxrat(1904, 2, 29, 1904, 3, 1) > 1.7


def weekday_approx(y, m, d):
    return int(days_between_approx(1899, 12, 31, y, m, d)) % 7


SKIPTEST2 = True
if not SKIPTEST2:
    assert weekday_approx(1900, 1, 1) == 1
    assert weekday_approx(1985, 10, 21) == 1
    assert weekday_approx(2017, 9, 19) == 2
    assert weekday_approx(1899, 12, 31) == 0
    assert weekday_approx(1700, 1, 1) == 5
    assert weekday_approx(2019, 9, 14) == 6


def daysgen(y, m, d, Y, M, D):
    yield (y, m, d)
    for _ in range(days_between(y, m, d, Y, M, D) - 1):
        d += 1

        if d == days_in_month(y, m, 0) + 1:
            m += 1
            d = 1

        if m == 13:
            y += 1
            m = 1

        yield (y, m, d)


assert list(daysgen(1899, 12, 31, 1900, 1, 4)) == \
    [(1899, 12, 31), (1900, 1, 1), (1900, 1, 2), (1900, 1, 3)]

assert next(daysgen(1899, 12, 31, 1900, 1, 4)) == (1899, 12, 31)

assert list(daysgen(1899, 12, 31, 1900, 1, 4)) == \
    [(1899, 12, 31), (1900, 1, 1), (1900, 1, 2), (1900, 1, 3)]

assert list(daysgen(2020, 2, 28, 2020, 3, 2)) == \
    [(2020, 2, 28), (2020, 2, 29), (2020, 3, 1)]

assert list(daysgen(2019, 2, 28, 2019, 3, 2)) == \
    [(2019, 2, 28), (2019, 3, 1)]

assert sum(1 for _ in daysgen(1985, 10, 21, 2017, 9, 19)) == 11656

# assert all((date(*t).weekday()+1) % 7 == weekday(*t)
#            for t in daysgen(1800, 1, 1, 2100, 1, 1))

for t in [
    ((date(*t).weekday()+1) % 7 == weekday(*t), t)
    for t in daysgen(1800, 1, 1, 2100, 1, 1)
]:
    if not t[0]:
        print(not t[0], is_leap(*t[1]))
