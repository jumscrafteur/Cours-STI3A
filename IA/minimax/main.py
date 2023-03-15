class Tree:
    def __init__(self, nodes, links, depth) -> None:
        self.nodes = nodes
        self.links = links
        self.depth = depth

    def show(self):
        for i in range(self.depth):
            n = self.depth - i - 1
            padding = (((2**n) * 6 - 1) // 2 - 2) * " "

            nodes = [
                f"{padding}|{str(self.nodes[j-1]).center(3,' ') if self.nodes[j-1] else ' - '}|{padding}"
                for j in range(2**i, 2 ** (i + 1))
            ]

            print(" ".join(nodes))

            if i < self.depth - 1:
                branch = [
                    (((2**n) * 6 - 1) // 4) * " "
                    + (((2**n) * 6 - 1) // 4 + 1) * "_"
                    + "|"
                    + (((2**n) * 6 - 1) // 4 + 1) * "_"
                    + (((2**n) * 6 - 1) // 4) * " "
                ] * 2**i

                print(" ".join(branch))

    def getChild(self, node):
        return self.links[node] if node in self.links else {}


def minimax(tree):
    return max_value(tree, 0)


def max_value(tree: Tree, node):
    childs = tree.getChild(node)
    if childs == {}:
        return tree.nodes[node]

    v = float("-inf")
    for child in childs:
        v = max(v, min_value(tree, child))

    return v


def min_value(tree: Tree, node):
    childs = tree.getChild(node)
    if childs == {}:
        return tree.nodes[node]

    v = float("inf")
    for child in childs:
        v = min(v, max_value(tree, child))
    return v


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

print(minimax(t))

# t.show()
