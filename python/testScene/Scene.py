from __future__ import annotations
from time import sleep
from typing import Callable, Optional, TYPE_CHECKING

if TYPE_CHECKING:
    from Game import Game


class Scene():
    def __init__(self, id: int, name: str,
                 createFunc: Callable[['Scene'], None] = lambda scene: None,
                 runFunc: Callable[['Scene'], None] = lambda scene: None,
                 destroyFunc: Callable[['Scene'], None] = lambda scene: None
                 ) -> None:
        self.name = name
        self.id = id
        self.game: Optional[Game] = None
        self.createFunc = createFunc
        self.runFunc = runFunc
        self.destroyFunc = destroyFunc

    def create(self, game: Game) -> None:
        self.game = game
        self.createFunc(self)
        return

    def run(self) -> None:
        self.runFunc(self)

    def destroy(self) -> None:
        self.destroyFunc(self)


def mainSceneRun(self: Scene):
    cmd = input("-> : ")
    for i in range(5):
        print(f"salut {i}")
        sleep(.25)

    if self.game and cmd == "switch":
        self.game.actualScene = 1


MAIN_SCENE = Scene(0, 'mainScene', runFunc=mainSceneRun)


def secondSceneRun(self: Scene) -> None:
    print("I am scene 2")
    sleep(1)

    if self.game:
        self.game.actualScene = 0


SECOND_SCENE = Scene(1, 'secondScene', runFunc=secondSceneRun)
