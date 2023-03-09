from Game import Game
from Scene import MAIN_SCENE, SECOND_SCENE

if __name__ == '__main__':
    g = Game()

    g.addScene(MAIN_SCENE)
    g.addScene(SECOND_SCENE)

    g.run()
