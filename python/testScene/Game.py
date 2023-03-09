from __future__ import annotations
from typing import Optional, TYPE_CHECKING

if TYPE_CHECKING:
    from Scene import Scene


class Game():
    def __init__(self) -> None:
        self.actualScene: Optional[int] = None
        self.running = True
        self.sceneMap = {}

    def addScene(self, scene: Scene) -> None:
        if scene.id in self.sceneMap.keys():
            raise Exception(
                f"The scene {self.sceneMap[scene.id]} already have id : {scene.id}")

        if self.actualScene == None:
            self.actualScene = scene.id

        self.sceneMap[scene.id] = scene
        pass

    def run(self):
        while self.running:
            if self.actualScene not in self.sceneMap.keys():
                raise Exception(
                    f"Invalid Scene ID ({self.actualScene}) valid : [{self.sceneMap.keys()}]")
            scene: Scene = self.sceneMap[self.actualScene]
            scene.create(self)
            while self.actualScene == scene.id:
                scene.run()
            scene.destroy()
