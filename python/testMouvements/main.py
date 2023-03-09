import random
import time

pathGrid = [[1, 1, 1, 0, 1, 0, 1],
            [1, 0, 1, 0, 1, 0, 1],
            [1, 1, 1, 0, 1, 0, 1],
            [0, 0, 0, 0, 1, 0, 1],
            [0, 0, 1, 1, 1, 0, 1],
            [0, 0, 0, 0, 1, 0, 1]]


def showGrid(grid, pos):
    gridText = ""
    for y in range(len(grid)):
        for x in range(len(grid[y])):
            if (x, y) == pos:
                gridText += '█'
            elif grid[y][x] == 1:
                gridText += '▓'
            else:
                gridText += '░'

        gridText += '\n'

    print(gridText)


class Guy():
    def __init__(self, pos):
        self.pos = pos
        self.dir = (0, 0)

    def mouv(self, grid, tryCount=0):
        self.dir = self.getRandomValideDir(grid)

        self.pos = (self.pos[0] + self.dir[0],
                    self.pos[1] + self.dir[1])

    def getRandomValideDir(self, grid):
        dirs = [dir for dir in [(0, -1), (1, 0), (0, 1), (-1, 0)]
                if self.isNextPosValide(dir, grid)]
        return random.choice(dirs if (len(dirs) > 0) else [(self.dir[0]*-1, self.dir[1]*-1)])

    def isNextPosValide(self, dir, grid):
        nextPos = (self.pos[0] + dir[0],
                   self.pos[1] + dir[1])

        isNextPosInRange = len(grid[0]) > nextPos[0] >= 0 and\
            len(grid) > nextPos[1] >= 0

        isNextPosAPath = False
        if isNextPosInRange:
            isNextPosAPath = grid[nextPos[1]][nextPos[0]] == 1

        isNextPosBackward = dir == (self.dir[0]*-1, self.dir[1]*-1)

        return isNextPosInRange and isNextPosAPath and not isNextPosBackward


myGuy = Guy((6, 0))

while True:
    showGrid(pathGrid, myGuy.pos)
    print(myGuy.pos)
    myGuy.mouv(pathGrid)
    time.sleep(1)
