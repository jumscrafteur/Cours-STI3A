from math import sqrt
from numbers import Number
from pyclbr import Function


def is_almost(n, m, d=1):
    return n <= m + d and n >= m - d


def di(f: Function, a: Number, b: Number, d: Number = 1e-16) -> Number:
    """Found the root of a lineare expression between [a;b]

    Parameters
    ----------
    f : Function
        linear func
    a : Number
        1st borne
    b : Number
        2nd borne
    d : Number, optional
        marge

    Returns
    -------
    Number
        root
    """
    mid = (a+b)/2
    while not is_almost(f(mid), 0, d):
        if f(a)*f(mid) < 0:
            b = mid
        elif f(b)*f(mid) < 0:
            a = mid
        else:
            return a if f(a) == 0 else b

        mid = (a + b) / 2
    return mid


assert is_almost(di(lambda x: x + 2, -100, 100), -2), "Erreur di"


def di2(f: Function, a: Number, b: Number, d: Number = 1e-16) -> Number:
    """Found the root of a lineare expression between [a;b]

    Parameters
    ----------
    f : Function
        linear func
    a : Number
        1st borne
    b : Number
        2nd borne
    d : Number, optional
        marge

    Returns
    -------
    Number
        root
    """
    mid = (a+b)/2

    if is_almost(f(mid), 0, d):
        return mid

    if f(a)*f(mid) < 0:
        return di2(f, a, mid, d)
    elif f(b)*f(mid) < 0:
        return di2(f, mid, b, d)
    else:
        return a if f(a) == 0 else b


assert is_almost(di2(lambda x: x + 2, -100, 100), -2, 1e-16), "Erreur di2"


def f(x): return 2*x
def g(x): return x**2 - 2


def deriv(f: Function, x: Number, h: Number = .01) -> Number:
    """Return the value of the derivative at a certain point

    Parameters
    ----------
    f : Function
        function to derive
    x : Number
        point where to calculate the derivative 
    h : Number, optional
        precision

    Returns
    -------
    Number
        value of f'(x)
    """

    # 34.1
    # return (f(x+h)-f(x))/h

    # 34.2
    return (f(x+h)-f(x-h))/(2*h)  # WOW


for x in range(-20, 20):
    assert is_almost(deriv(lambda x: x**2 + 2, x/10),
                     .2 * x, .1), f"Erreur derive ({deriv(lambda x: x**2 + 2,x/10)} != {.2 * x})"


def fderiv(f: Function, h: Number = .01) -> Function:
    """Return the derivated function

    Parameters
    ----------
    f : Function
        function you want to derive
    h : Number, optional
        precision, by default .01

    Returns
    -------
    Function
        derivated function
    """
    return lambda x: deriv(f, x, h)


for x in range(-20, 20):
    assert is_almost(
        fderiv(lambda x: x**2 + 2)(x/10),
        .2 * x,
        .1), f"Erreur fderive ({fderiv(lambda x: x**2 + 2)(x/10)} != {.2 * x})"

G = fderiv(g)


def test_deriv():
    print(f"{'x':<5} {'f(x)':<5} {'G(x)':<5} {'f(x)-G(x)':<21}")
    for x in range(-20, 21):
        print(
            f"{f'{x/10:.2f}':>5} {f'{f(x/10):.2f}':>5} {f'{G(x/10):.2f}':>5} {f'{(f(x/10)-G(x/10)):.19f}':>22}")

# test_deriv()


def newton(f: Function, x: Number, eps: Number = 1e-15, debug: bool = False) -> Number:
    """compute a zero of a function if possible

    Parameters
    ----------
    f : Function
        function to search
    x : Number
        start guess
    eps : Number, optional
        precision, by default 1e-15
    debug : bool, optional
        print the value f the guess at every step, by default False

    Returns
    -------
    Number
        value of x where f(x)=0
    """
    debug and print(f"-> {x}")
    if abs(f(x)) < eps:
        return x
    return newton(f, x - f(x)/fderiv(f)(x), debug=debug)


assert is_almost(newton(g, 1), sqrt(2), .01), "Erreur newton"
