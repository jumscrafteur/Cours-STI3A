import numpy as np
from matplotlib import pyplot as plt

x = np.array(
    [
        [1, 0.5, 3],
        [1, 0.4, 3],
        [1, 0.4, 4],
        [1, 2.3, 5],
        [1, 2.1, 5],
        [1, 2.2, 4.5],
    ]
)

t = np.array([1, 1, 1, -1, -1, -1])


z = np.linspace(0, 3, 100)

n = len(x)

w = np.random.rand(len(x[0]))
tau = 0
eta = 0.01
normeOmega = 1

while normeOmega != 0 and tau < 10000:
    deltaW = np.zeros(3)
    normeOmega = 0
    for i in range(n):
        if t[i] * np.dot(w, x[i]) <= 0:
            normeOmega += 1
            deltaW += eta * t[i] * x[i]
    w += deltaW
    tau += 1

for xi in x:
    plt.plot(xi[1], xi[2], "ro")

plt.plot(x[0:3, 1], x[0:3, 2], "ro")
plt.plot(x[3:6, 1], x[3:6, 2], "bo")

print(w)
plt.plot(z, -w[0] / w[2] - (w[1] / w[2]) * z, "b")

plt.show(block=True)
