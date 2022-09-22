# {'t','o'}
print(set('totto'))
# ...
# ====
# {'totto'}
print({'totto'})
# ...
# ====
# {{'toto'}, {'tata'}}
# print({{'toto'}, {'tata'}})
# unhashable type: 'set'
# ====
# e
print('abcde'[-1])
# ...
# ====
# b
# print({'abcde'}[0][1])
# TypeError: 'set' object is not subscriptable
# ====
# cde
print('abcdefg'[2:5])
# ...
# ====
# ['c','d','e']
print((list('abcdefg')*3)[2:5])
# ...
# ====
# ['f','g']
print((list('abcdefg')*3)[19:22])
# ...
# ====
# cde
print('abcdefg'[-5:-2])
# ...
# ====
# []
print(list(range(12))[13:5:-2])
# [11, 9, 7]
# ====
# {0: 1, None: 2, False: 5}
print({0: 1, None: 2, False: 5})
# {0: 5, None: 2}
# ====
# 1
# 2
# 1
# 2
# 1
# 2
# {None}
# {(1,None),(2,None)}
# {(1,1,None),(2,2,None)}
s = {print(i) for i in range(1, 3)}
ss = {(i, print(i)) for i in range(1, 3)}
sss = {(i, i, print(i)) for i in range(1, 3)}
print(s, ss, sss, sep='\n')
#  ...
