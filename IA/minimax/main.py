class Tree:
    def __init__(self, nodes, links, depth) -> None:
        self.nodes = nodes
        self.links = links
        self.depth = depth

    def show(self):
        for i in range(self.depth):
            n = self.depth - i - 1
            padding = (((2**n) * 6 - 1) // 2 - 2) * " "
            nodes = [f"{padding}| {i} |{padding}"] * 2**i
            print(" ".join(nodes))
        print("==" * 10)
        print("                     | - |")
        print("           ____________|____________ ")
        print("         | - |                   | - |")
        print("     ______|______           ______|______")
        print("   | - |       | - |       | - |       | - |")
        print("  ___|___     ___|___     ___|___     ___|___")
        print("| 6 | | 8 | | 9 | | 1 | | 3 | |-2 | | 9 | |-1 |")


t = Tree(
    [None, None, None, None, None, None, None, 6, 8, 9, 1, 3, -2, 9, -1],
    {
        0: {1, 2},
        1: {3, 4},
        2: {5, 6},
        3: {7, 8},
        4: {9, 10},
        5: {11, 12},
        6: {13, 14},
    },
    4,
)

t.show()
