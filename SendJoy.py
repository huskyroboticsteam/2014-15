import pygame
import socket
import struct
#import binascii
import time
from pygame.locals import *

address = ("127.0.0.1", 1000)

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

pygame.init()
joystick_count=pygame.joystick.get_count()
if joystick_count == 0:
    # No joysticks!
    print ("Error, I didn't find any joysticks.")
else:
    # Use joystick #0 and initialize it
    print ("init")
    fir_joystick = pygame.joystick.Joystick(0)
    fir_joystick.init()
    sec_joystick = pygame.joystick.Joystick(1)
    sec_joystick.init()

done = False

def normalize(value):
    return int((-value + 1)/2 * 500 + 1250)

while done==False:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            done=True
            continue

    vertAx1 = normalize(fir_joystick.get_axis(1))
    #horAxis1 = normalize(fir_joystick.get_axis(0))
    vertAx2 = normalize(sec_joystick.get_axis(1))
    #horAxis2 = normalize(sec_joystick.get_axis(0))

    message = str(vertAx1) + ":" + str(vertAx2)
    #message = str(horAxis1) + ":" + str(vertAx1) + ":" + str(horAxis2) + ":" + str(vertAx2)

    sock.sendto(message, address) 
    #sock.sendto(binascii.hexlify(packet_data), (IP, PORT))

    print(message)

    time.sleep(1)

pygame.quit ()
        
        

        

        
    
