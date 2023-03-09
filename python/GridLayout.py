def GenerateGrid(x, y, columnNumber, rowNumber, gapX, gapY, sizeX, sizeY):
    initialOffsetX = - (columnNumber - 1) * (gapX+sizeX) / 2
    initialOffsetY = - (rowNumber - 1) * (gapY+sizeY) / 2

    for c in range(columnNumber):
        for r in range(rowNumber):
            yield (x + initialOffsetX + c*(gapX+sizeX), y + initialOffsetY + r*(gapY+sizeY))


layout = GenerateGrid(0, 0, 1, 4, 100, 50, 200, 100)

for i in range(4):
    print(next(layout))
