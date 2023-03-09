#!/usr/bin/env python2

import pygame

WIDTH = 360
HEIGHT = 480
FPS = 30

# initialize pygame and create window
pygame.init()
pygame.mixer.init()  # For sound
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("<Your game>")
clock = pygame.time.Clock()  # For syncing the FPS

CUSTOM_EVENT1 = pygame.event.custom_type()
CUSTOM_EVENT2 = pygame.event.custom_type()


# Game loop
running = True
while running:

    # 1 Process input/events
    clock.tick(FPS)  # will make the loop run at the same speed all the time
    # gets all the events which have occured till now and keeps tab of them.
    for event in pygame.event.get():
        # listening for the the X button at the top
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_a:
                evt = pygame.event.Event(CUSTOM_EVENT1, {"value": 1})
                pygame.event.post(evt)
            elif event.key == pygame.K_z:
                evt = pygame.event.Event(CUSTOM_EVENT2, {"value": 2})
                pygame.event.post(evt)
        elif event.type in [CUSTOM_EVENT1, CUSTOM_EVENT2]:
            print(event.value)

    # 3 Draw/render
    screen.fill((0, 0, 0))

    ########################

    # Your code comes here

    ########################

    # Done after drawing everything to the screen
    pygame.display.flip()

pygame.quit()
