import pygame
import time
import socket
import sys

pygame.joystick.init()
pygame.display.init()

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
address = ("127.0.0.1", 1000)
#sock.bind(server_address)


if pygame.joystick.get_init():
    print("That worked.")

for i in range(pygame.joystick.get_count()):
    joystick = pygame.joystick.Joystick(i)
    joystick.init()
    
print(joystick.get_id())

while pygame.joystick.get_count() == 1:
    time.sleep(0.1)
    pygame.event.pump()
    buttons = []
    print(joystick.get_axis(0))
    print(joystick.get_axis(1))
    for i in range(joystick.get_numbuttons()):
        if joystick.get_button(i) == 1:
            buttons.append(i)
            print("PEW")
    data = "" + str(joystick.get_axis(0)) + str(joystick.get_axis(1)) + str(buttons)
    sent = sock.sendto(data, address)
            
