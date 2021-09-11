import pygame,sys
from pygame.locals import *

pygame.init()
clock = pygame.time.Clock()
messy_ghost = pygame.image.load('ghost.png')

window = pygame.display.set_mode((1280, 720))
running = True

x = 0
y = 0
sx = 200
sy = 150

while running:
    for event in pygame.event.get():
        if event.type == QUIT:
            running = False
            
    delta = clock.tick(30) / 1000
    x = x + sx * delta
    y = y + sy * delta
    
    if y + 160 > window.get_height() or y < 0:
        sy = sy * -1
    
    if x + 140 > window.get_width() or x < 0:
        sx = sx * -1
            
    window.fill((0,0,0))
    window.blit(messy_ghost, (x,y))
    pygame.display.update()
    
    
    
pygame.quit()