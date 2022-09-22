from numbers import Number
import matplotlib.pyplot as plt

from dataclasses import dataclass
import math
from typing import Union


@dataclass
class BinExpr:
    a: object
    b: object


Expr = Union[BinExpr, int, float, str]


class Call(BinExpr):
    a: str
    funcMap = {"ln": math.log}

    def sem(self, a: str, b: Number) -> Number:
        try:
            if a in dir(math):
                return getattr(math, a)(b)
            elif a in self.funcMap.keys():
                return self.funcMap[a](b)
            else:
                raise ValueError(a)
        except ValueError:
            return math.nan
    pass


class BinOp (BinExpr):
    pass


class Add(BinOp):
    sym = "+"
    def sem(self, a: Number, b: Number) -> Number: return a+b


class Sub(BinOp):
    sym = "-"
    def sem(self, a: Number, b: Number) -> Number: return a-b


class Mul(BinOp):
    sym = "*"
    def sem(self, a: Number, b: Number) -> Number: return a*b


class Div(BinOp):
    sym = "/"

    def sem(self, a: Number, b: Number) -> Number:
        return float('inf') if b == 0 else a/b


class Pow(BinOp):
    sym = "^"
    def sem(self, a: Number, b: Number) -> Number: return a**b


@dataclass
class UnOp:
    a: object


def is_expr(el):
    return type(el) in [Call, Add, Sub, Mul, Div, Pow]


def estr(expr: Expr):
    match expr:
        case str() | Number(): return expr
        case BinOp(a, b): return f"({estr(expr.a)}{expr.sym}{estr(expr.b)})"
        case Call(a, b): return f"{expr.a}({estr(expr.b)})"
        case _: raise ValueError(expr)


assert estr(Call("ln", "x")) == "ln(x)"
assert estr(Add("x", "y")) == "(x+y)"
assert estr(Sub("x", "y")) == "(x-y)"
assert estr(Mul("x", "y")) == "(x*y)"
assert estr(Div("x", "y")) == "(x/y)"
assert estr(Pow("x", "y")) == "(x^y)"


def eval(expr: Expr, var: str = "x", val: Number = 0):
    match expr:
        case Number(): return expr
        case Call(a, b): return expr.sem(a, eval(b, var, val))
        case BinExpr(a, b): return expr.sem(eval(a, var, val), eval(b, var, val))
        case str():
            if expr == var:
                return val
            else:
                raise ValueError(expr)
        case _: raise ValueError(expr)


assert eval(Call("ln", "x"), "x", 1) == 0
assert eval(Add("x", 0), "x", 1) == 1
assert eval(Sub("x", 0), "x", 1) == 1
assert eval(Sub("x", 1), "x", 0) == -1
assert eval(Mul("x", 0), "x", 1) == 0
assert eval(Div("x", 0), "x", 1) == float('inf')
assert eval(Div("x", 2), "x", 1) == .5
assert eval(Pow("x", 2), "x", 3) == 9


def Rep(expr1, var, expr2):

    match expr1:
        case str(): return expr2 if expr1 == var else expr1
        case Number(): return expr1
        case BinExpr(a, b):
            expr1.a = Rep(a, var, expr2)
            expr1.b = Rep(b, var, expr2)
            return expr1


def D(expr: Expr, var: str = "x"):
    match expr:
        case Number(): return 0
        case str(): return 1 if expr == var else 0
        case Sub(a, b): return Sub(D(a), D(b))
        case Add(a, b): return Add(D(a), D(b))
        case Mul(a, b): return Add(Mul(D(a), b), Mul(a, D(b)))
        case Div(a, b): return Div(Sub(Mul(D(a), b), Mul(a, D(b))), Pow(b, 2))
        case Pow(a, b): return Mul(b, Mul(D(a), Pow(a, b-1)))
        case Call(a, b):
            match a:
                case 'ln': return Div(D(b), b)


# Check Const
assert eval(D(6)) == 0

# Check
assert eval(D("x")) == 1

# Check f+g
assert eval(D(Add("x", 2))) == 1

# Check f-g
assert eval(D(Sub("x", 2))) == 1

# Check f*g
assert eval(D(Mul("x", Sub("x", 3)))) == -3

# Check f*g
assert eval(D(Div("x", Sub("x", 3)))) == -1/3

# Check x^n et u^n
assert eval(D(Pow("x", 2)), val=3) == 6
assert eval(D(Pow(Sub("x", Pow("x", 2)), 2)), val=1) == 0

# Check ln(x) et ln(u)
assert eval(D(Call("ln", "x")), val=2) == .5
assert eval(D(Call("ln", Pow("x", 2))), val=2) == 1


def fixpoint(f, e):
    if f(e) == e:
        return e
    else:
        return fixpoint(f, f(e))


def simp(e: Expr) -> Expr:
    def z(e):
        match e:
            case Add(0, e) | Add(e, 0): return e
            case Add(a, b):
                if type(a) == int and type(b) == int:
                    return eval(e)
                if type(a) == Mul and type(b) == Mul:
                    if a.a == b.a:
                        return Mul(simp(Add(a.b, b.b)), a.a)
                    elif a.b == b.b:
                        return Mul(simp(Add(a.a, b.a)), a.b)
                    elif a.a == b.b:
                        return Mul(simp(Add(a.b, b.a)), a.a)
                    elif a.b == b.a:
                        return Mul(simp(Add(a.a, b.b)), a.b)
                    return Add(simp(a), simp(b))
                elif a == b:
                    return Mul(2, simp(a))
                else:
                    return Add(simp(a), simp(b))
            case Sub(a, b): return Add(a, Mul(-1, b))
            case Mul(0, e) | Mul(e, 0): return 0
            case Mul(1, e) | Mul(e, 1): return e
            case Mul(a, b):
                if type(a) == int and type(b) == Add:
                    return Add(simp(Mul(a, b.a)), simp(Mul(a, b.b)))
                elif type(b) == int and type(a) == Add:
                    return Add(simp(Mul(b, a.a)), simp(Mul(b, a.b)))

                elif type(a) == int and type(b) == Mul and type(b.a) == int:
                    return Mul(simp(Mul(a, b.a)), simp(b.b))
                elif type(b) == int and type(a) == Mul and type(a.a) == int:
                    return Mul(simp(Mul(b, a.a)), simp(a.b))
                elif type(a) == int and type(b) == Mul and type(b.b) == int:
                    return Mul(simp(Mul(a, b.a)), simp(b.b))
                elif type(b) == int and type(a) == Mul and type(a.b) == int:
                    return Mul(simp(Mul(b, a.a)), simp(a.b))

                elif a == b:
                    return Pow(simp(a), 2)
                elif type(a) == int and type(b) == int:
                    return eval(Mul(a, b))
                else:
                    return Mul(simp(a), simp(b))
            # case Div(a, b): return Mul(a, Pow(b, -1))
            case Pow(e, 1): return e
            case Pow(0, n): return 1
            case _: return e

    return fixpoint(z, e)


# e + 0 == 0
assert estr(simp(Add("x", 0))) == "x"

# e+e = 2e
assert estr(simp(Add("x", "x"))) == "(2*x)"

# 0*e = 0
assert estr(simp(Mul("x", 0))) == 0

# 1*e = e
assert estr(simp(Mul("x", 1))) == "x"

# factorisation
assert estr(simp(Add(Mul(3, "x"), Mul(4, "x")))) == "(7*x)"

# devellopement
assert estr(simp(Mul(3, Add(4, "x")))) == "(12+(3*x))"
assert estr(simp(Mul(3, Mul(4, "x")))) == "(12*x)"
assert estr(simp(Mul(3, Mul("x", 4)))) == "(12*x)"
assert estr(simp(Mul(Mul("x", 4), 3))) == "(12*x)"

assert estr(simp(D(Mul(Call("ln", "x"), Add(Mul(3, Pow("x", 2)), 1))))) ==\
    "(((1/x)*((3*(x^2))+1))+(ln(x)*(6*x)))"


print(estr(Call("ln", "x")))
print(estr(Rep(Call("ln", "x"), "x", Pow("x", 2))))

PLOT = False

if PLOT == True:
    x = "x"
    # f1 = Add(1, Mul(2, Call("ln", Sub(Pow(x, 2), 1))))
    f2 = Mul(Call("ln", x), Add(Mul(3, Pow(x, 2)), 1))

    # df1 = simp(D(f1))
    df2 = simp(D(f2))

    plt.figure(figsize=(12, 8))
    plt.rcParams.update({'font.size': 18})

    X = [-2 + i/100 for i in range(500)]

    # Yf1 = [eval(f1, x, X) for X in X]
    Yf2 = [eval(f2, x, X) for X in X]

    # Ydf1 = [eval(df1, x, X) for X in X]
    Ydf2 = [eval(df2, x, X) for X in X]

    plt.ylim([-5, 10])  # limit the y axis

    # plt.plot(X, Yf1, 'b', label=estr(f1), linewidth=2)
    plt.plot(X, Yf2, 'r', label=estr(f2), linewidth=2)

    # plt.plot(X, Yfd1, 'p', label=estr(f1), linewidth=2)
    plt.plot(X, Ydf2, 'y', label=estr(df2), linewidth=2)

    plt.legend(loc='best')
    plt.axvline(0)

    ##plt.savefig('../excasf1f2.pdf', transparent=True)
    plt.show()
