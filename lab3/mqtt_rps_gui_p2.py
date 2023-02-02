import paho.mqtt.client as mqtt
import numpy as np
import time
import pygame
import random as rand
from pygame.locals import (K_0, K_1, K_2, KEYDOWN)

global client
comp_gesture = 3

def mqtt_publisher():
    # 0. define callbacks - functions that run when events happen.
    # The callback for when the client receives a CONNACK response from the server.

    def on_connect(client, userdata, flags, rc):
        print("Connection returned result: " + str(rc))
        # Subscribing in on_connect() means that if we lose the connection and
        # reconnect then subscriptions will be renewed.
        client.subscribe("ece180d/player1")
        # The callback of the client when it disconnects.

    def on_disconnect(client, userdata, rc):
        if rc != 0:
            print('Unexpected Disconnect')
        else:
            print('Expected Disconnect')
        # The default message callback.
        # (won't be used if only publishing, but can still exist)

    def on_message(client, userdata, message):
        global comp_gesture
        comp_gesture = int(str(message.payload)[2:-1])
        print(comp_gesture)

                
    # 1. create a client instance.
    global client
    client = mqtt.Client()
    # add additional client options (security, certifications, etc.)
    # many default options should be good to start off.
    # add callbacks to client.
    client.on_connect = on_connect
    client.on_disconnect = on_disconnect
    client.on_message = on_message

    # 2. connect to a broker using one of the connect*() functions.
    # client.connect_async("test.mosquitto.org")
    client.connect_async('mqtt.eclipseprojects.io')

    # 3. call one of the loop*() functions to maintain network traffic flow with the broker.
    client.loop_start()
    # 4. use subscribe() to subscribe to a topic and receive messages.
    # 5. use publish() to publish messages to the broker.
    # payload must be a string, bytearray, int, float or None.


    # 6. use disconnect() to disconnect from the broker.
    # client.loop_stop()
    # client.disconnect()

def main():
    mqtt_publisher()

    rock_color, paper_color, scissors_color = (255,0,0), (0,255,0), (0,0,255)
    rock_radius, paper_width, scissors_width = 50, 0, 0
    screen_width, screen_height = 500, 500
    user_x, user_y, comp_x, comp_y = 100, 100, 700, 100

    pygame.init()
    screen = pygame.display.set_mode([screen_width, screen_height])
    font = pygame.font.Font('freesansbold.ttf', 23)
    input_text = font.render('Input 0 for Rock, 1 for Paper, 2 for Scissors:', True, (0,0,0))
    running = True
    running = True

    global comp_gesture
    while running:
        screen.fill((255,255,255))
        pygame.display.flip()

        while comp_gesture == 3:
            pass
        screen.blit(input_text, (0, 0))
        pygame.display.flip()
        user_gesture = 3
        print('hereererere')
        time.sleep(5)
        while user_gesture == 3:
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
        print('matching user_gesture')
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
            client.publish('ece180d/player2', user_gesture, qos=1)
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
        comp_gesture = 3

    pygame.quit()

if __name__ == '__main__':
    main()