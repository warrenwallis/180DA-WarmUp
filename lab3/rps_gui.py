import pygame
import random as rand
import time
from pygame.locals import (K_0, K_1, K_2, KEYDOWN)

'''
pygame.draw.circle(surface,color,center,radius,width)   -> rock
pygame.draw.rect(surface,color,rect, width)             -> paper
pygame.draw.polygon(surface,color,points,width)         -> scissors
'''
rock_color, paper_color, scissors_color = (255,0,0), (0,255,0), (0,0,255)
rock_radius, paper_width, scissors_width = 50, 0, 0
screen_width, screen_height = 500, 500
user_x, user_y, comp_x, comp_y = 100, 100, 700, 100

def main():
    pygame.init()
    screen = pygame.display.set_mode([screen_width, screen_height])
    font = pygame.font.Font('freesansbold.ttf', 23)
    input_text = font.render('Input 0 for Rock, 1 for Paper, 2 for Scissors:', True, (0,0,0))
    
    running = True
    while running:
        user_gesture = 3
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            if event.type == KEYDOWN:
                if event.key == K_0:
                    user_gesture = 0
                if event.key == K_1:
                    user_gesture = 1
                if event.key == K_2:
                    user_gesture = 2

        screen.fill((255,255,255))
        screen.blit(input_text, (0, 0))

        match user_gesture:
            case 0:
                pygame.draw.circle(screen,rock_color,(user_x,user_y),rock_radius)
            case 1:
                pygame.draw.rect(screen,paper_color,[user_x//2,user_y//2,user_x,user_y],paper_width)
            case 2:
                pygame.draw.polygon(screen,scissors_color,[[user_x//2,user_y//2],[user_x//2,user_y+(user_y//2)],[user_x+(user_x//2),user_y+(user_y//2)]],scissors_width)
            case _:
                pass

        pygame.display.flip()

        if user_gesture != 3:
            comp_gesture = rand.randint(0,2)
            mapping = {0 : 'Rock', 1 : 'Paper', 2 : 'Scissors'}

            match comp_gesture:
                case 0:
                    pygame.draw.circle(screen,rock_color,(comp_x//2,comp_y),rock_radius)
                case 1:
                    pygame.draw.rect(screen,paper_color,[comp_x//2,comp_y//2,user_x,user_y],paper_width)
                case 2:
                    pygame.draw.polygon(screen,scissors_color,[[comp_x//2,comp_y//2],[comp_x//2,user_y+(comp_y//2)],[user_x+(comp_x//2),user_y+(comp_y//2)]],scissors_width)
                case _:
                    pass
            
            if user_gesture == (comp_gesture-1)%3:
                output_text = font.render(f'Computer chooses {mapping[comp_gesture]}; Computer wins!',True,(0,0,0))
            elif comp_gesture == (user_gesture-1)%3:
                output_text = font.render(f'Computer chooses {mapping[comp_gesture]}; You win!',True,(0,0,0))
            else:
                output_text = font.render(f'Computer chooses {mapping[comp_gesture]}; Tie!',True,(0,0,0))

            screen.blit(output_text, (0,250))
            time.sleep(2)
            

        pygame.display.flip()
        time.sleep(1)

    pygame.quit()
        


if __name__ == '__main__':
    main()