class A():
    pass


class B(A):
    pass


a = A()

b = B()

print(str(b.__class__) == "<class '__main__.B'>")
