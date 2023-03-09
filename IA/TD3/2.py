import numpy as np
from matplotlib import pyplot as plt

x = np.array([[1, 0.1], [1, 0.2], [1, 0.3], [1, 0.3], [1, 0.5], [1, 0.4]])
y = np.array([3.5, 5.2, 4.5, 5.3, 6.5, 4.1])

z = np.linspace(0, 0.6, 100)

n = len(x)

w = np.random.rand(2)

eta = 0.01

for _ in range(10000):
    for i in range(n):
        w += eta * (y[i] - np.dot(w, x[i])) * x[i]

plt.plot([x1 for _, x1 in x], y, "ro")
plt.plot(z, w[0] + w[1] * z, "b")

plt.show(block=True)
