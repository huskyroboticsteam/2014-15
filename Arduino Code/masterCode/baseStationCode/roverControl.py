#!/usr/bin/env python
# -*- coding: utf-8 -*-
# vi:ts=4 sw=4 et

from __future__ import division
from __future__ import print_function

import struct
import socket

# Joystick import
import pygame

# Joystick Constants
C_RIGHT = 1
C_LEFT = 0
A_RIGHT = 3
A_LEFT = 2

# UDP Constants
TARGET_IP = "192.168.1.177"
UDP_PORT = 8888
MAX_BUFFER_SIZE = 24

# UDP Defaults message
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
message = "I'm too old for this."


def getResponse():
    try:
        sock.sendto(message, (TARGET_IP, UDP_PORT))
        data, addr = sock.recvfrom(MAX_BUFFER_SIZE)
        gpsTup = struct.unpack("%f%f", data)
        print("Response: ", gpsTup[0:1])
    except Exception as error:
        print("")


def joy2value(value, halfcontrol=False):
    if halfcontrol:
        value /= 2.0
    if abs(value - 0) < 0.05:
        value = 0
    return value


def float256(value, low, high):
    value = 256 * (value - low) / (high - low)
    value = max([value, 0])
    value = min([value, 255])
    return int(value)


def float012(value):
    if (value < 0.5) and (value > -0.5):
        return 1
    if value < -0.5:
        return 0
    return 2


def bool012(forward, reverse):
    if forward:
        return 2
    if reverse:
        return 0
    return 1

# Main                
if __name__ == '__main__':
    try:
        # Joystick
        pygame.joystick.init()
        pygame.display.init()
        joystick = []
        joynum = pygame.joystick.get_count()
        print(str(joynum) + " joysticks connected.")
        
        for i in range(joynum):
            pygame.joystick.Joystick(i).init()
            
        while len(joystick) < joynum:
            pygame.event.pump()
            for i in range(joynum):
                if pygame.joystick.Joystick(i).get_button(0):
                    joystick.append(pygame.joystick.Joystick(i))
                    pygame.time.wait(500)

        for i in range(joynum):
            print("Joystick " + str(i) + " is: " + joystick[i].get_name() + " with " + str(joystick[i].get_numaxes()) + " axes.")
        
        # Initialize
        arm = []
        for i in range(4):
            arm.append(1)

        hand = []
        for i in range(3):
            hand.append(1)

        misc = []
        for i in range(4):
            misc.append(1)
        
        # UDP
        print("UDP Port: ", UDP_PORT)
        print("Test Message: ", message)
        print("Max Buffer Size: ", MAX_BUFFER_SIZE)

        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

        sock.bind(('0.0.0.0', UDP_PORT))
        sock.settimeout(0.01)
        
        # Main Loop
        while True:
            # Get and convert joystick value, print
            pygame.event.pump()
            if joynum > 1:
                left = joy2value(joystick[C_LEFT].get_axis(1), (not joystick[C_RIGHT].get_button(0)))
                right = joy2value(joystick[C_RIGHT].get_axis(1), (not joystick[C_RIGHT].get_button(0)))
                misc[0] = joystick[C_RIGHT].get_button(2)
            else:
                left = (
                    joy2value(joystick[0].get_axis(1), (not joystick[0].get_button(0))) +
                    joy2value(joystick[0].get_axis(0), (not joystick[0].get_button(0))))
                right = (
                    joy2value(joystick[0].get_axis(1), (not joystick[0].get_button(0))) -
                    joy2value(joystick[0].get_axis(0), (not joystick[0].get_button(0))))

            if joynum == 4:
                print("TEst...")
                arm[0] = float012(joystick[A_RIGHT].get_axis(3))
                arm[1] = float012(joystick[A_RIGHT].get_axis(1) * -1)
                arm[2] = bool012(joystick[A_RIGHT].get_button(4), joystick[A_RIGHT].get_button(2))
                arm[3] = bool012(joystick[A_RIGHT].get_button(5), joystick[A_RIGHT].get_button(3))
                
                hand[0] = float012(joystick[A_LEFT].get_axis(3))
                hand[1] = float012(joystick[A_LEFT].get_axis(0))
                hand[2] = bool012(joystick[A_LEFT].get_button(0), joystick[A_LEFT].get_button(1))
                
                misc[1] = bool012(joystick[A_RIGHT].get_button(6), joystick[A_RIGHT].get_button(7))
                misc[2] = bool012(joystick[A_LEFT].get_button(0), joystick[A_LEFT].get_button(1))
            
            left = float256(left, -1, 1)
            right = float256(right, -1, 1)

            print("LEFT: " + str(ord(chr(left))))
            print("RIGHT: " + str(ord(chr(right))))
            # print(hand[2])
            print(arm[0])
            print(arm[1])
            print(arm[2])
            print(arm[3])
            
            armByte = chr(arm[0] | (arm[1] << 2) | (arm[2] << 4) | (arm[3] << 6))
            handByte = chr(hand[0] | (hand[1] << 2) | (hand[2] << 4))
            miscByte = chr(misc[0] | (misc[1] << 2) | (misc[2] << 4) | (misc[3] << 6))
            
            message = ''.join([chr(left), chr(right), armByte, handByte, miscByte])

            # Send data over UDP, print recv
            getResponse()
            
            '''p = Process(target=getResponse)
            p.start()
            p.join(100)
            if(p.is_alive()):
                print("Disconnect... Attempting to fix.")
                p.terminate()
                p.join()'''
                
            pygame.time.wait(100)
            
    except KeyboardInterrupt:
        pygame.quit()
