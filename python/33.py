from numbers import Number
from typing import Tuple, Union


def is_almost(n, m, d=1):
    return n <= m + d and n >= m - d


def fahrenheit_to_celsius(fTemp: Number) -> Number:
    """Convert fahrenheit unit to celsius unit

    Parameters
    ----------
    fTemp : Number
        temperature in fahrenheit

    Returns
    -------
    Number
        temperature in celsius
    """

    assert isinstance(fTemp, Number), "Argument invalide"

    return (fTemp - 32) * 5 / 9


def celsius_to_fahrenheit(cTemp: Number) -> Number:
    """Convert celsius unit to fahrenheit unit

    Parameters
    ----------
    cTemp : Number
        temperature in celsius

    Returns
    -------
    Number
        temperature in fahrenheit
    """

    assert isinstance(cTemp, Number), "Argument invalide"

    return (9/5) * cTemp + 32


assert is_almost(fahrenheit_to_celsius(-459.67), -273.15, 1e-13), \
    "Erreur fahrenheit_to_celsius"

assert is_almost(celsius_to_fahrenheit(-273.15), -459.67,  1e-13), \
    "Erreur celsius_to_fahrenheit"


def greatest_root(a: Number, b: Number, c: Number) -> Union[Number, None]:
    """Return the greatest root of a polynom of the format ax2+bx+c

    Parameters
    ----------
    a : Number
        2nd degree polynom coeff
    b : Number
        1st degree polynom coeff
    c : Number
        const coeff

    Returns
    -------
    Union[Number, None]
        the greatest root if exist
    """
    if (a == 0):
        return -b/c if c != 0 else 0

    delta = b * b - 4 * a * c
    if delta < 0:
        return None

    return (-b + delta ** (1/2))/(2*a)

    # return


assert (greatest_root(1, 0, -1) == 1),\
    "Erreur greatest_root"
assert (greatest_root(1, 0, 1) == None),\
    "Erreur greatest_root"


def roots(a: Number, b: Number, c: Number) -> Tuple[Union[Number, None], Union[Number, None]]:
    """return all the roots of a polynom

    Parameters
    ----------
    a : Number
        2nd degree polynom coeff
    b : Number
        1st degree polynom coeff
    c : Number
        const coeff

    Returns
    -------
    Tuple[Union[Number, None], Union[Number, None]]
        return the roots of a polynom
    """

    if (a == 0):
        return (-b/c, -b/c) if c != 0 else (0, 0)

    delta = b * b - 4 * a * c
    if delta < 0:
        return (None, None)

    return ((-b - delta ** (1/2))/(2*a), (-b + delta ** (1/2))/(2*a))


for a in range(-5, 5):
    for b in range(-5, 5):
        for c in range(-5, 5):
            assert (greatest_root(a, b, c) == roots(a, b, c)[1]),\
                "Erreur roots"
