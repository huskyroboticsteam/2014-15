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

axis0 = [0]*joystick.get_numaxes()
buttons0 = [0]*joystick.get_numbuttons()
axis1 = [0]*joystick.get_numaxes()
buttons1 = [0]*joystick.get_numbuttons()
axis2 = [0]*joystick.get_numaxes()
buttons2 = [0]*joystick.get_numbuttons()
axis3 = [0]*joystick.get_numaxes()
buttons3 = [0]*joystick.get_numbuttons()
    
while pygame.joystick.get_count() == 1:
    time.sleep(0.1)
    pygame.event.pump()
    
    for i in range(joystick.get_numaxes()):
        axis2[i] = joystick.get_axis(i)
    #print(axis)
    
    for i in range(joystick.get_numbuttons()):
        buttons2[i] = joystick.get_button(i)
        if joystick.get_button(i) == 1:
            #buttons.append(i)
            print("PEW")
    #print(buttons)
    """
    encode inputs into usable forms
"""
    """
    drive motors left
    (joystick0)
    """
    if(axis0[1] > .1):
        axis0[1] = 1
    elif(axis0[1] > -.1):
        axis0[1] = 0
    else:
        axis0[1] = -1
    axis0[2] = (int)((axis0[2] - 1) * -64) 
    leftDrive = ""
    if(axis0[1] == 0):
        leftDrive += "00000000"
    elif(axis0[1] == 1):
        tmp = format(axis0[2], 'b')
        leftDrive += "0"
        for i in range(7-len(tmp)):
            leftDrive += "0"
        leftDrive += tmp
    else:
        tmp = format(axis0[2], 'b')
        leftDrive += "1"
        for i in range(7-len(tmp)):
            leftDrive += "0"
        leftDrive += tmp
    #print (leftDrive)
        
    """
    drive motors right
    (joystick1)
    """
    if(axis1[1] > .1):
        axis[1] = 1
    elif(axis1[1] > -.1):
        axis1[1] = 0
    else:
        axis1[1] = -1
    axis1[2] = (int)((axis1[2] - 1) * -64) 
    rightDrive = ""
    if(axis1[1] == 0):
        rightDrive += "00000000"
    elif(axis1[1] == 1):
        tmp = format(axis1[2], 'b')
        rightDrive += "0"
        for i in range(7-len(tmp)):
            rightDrive += "0"
        rightDrive += tmp
    else:
        tmp = format(axis1[2], 'b')
        rightDrive += "1"
        for i in range(7-len(tmp)):
            rightDrive += "0"
        rightDrive += tmp
    #print (rightDrive)

    """
    sci-station stuff
    spinny: axis1[3]
    pushy: axis0[0]
"""
    sciRot = ""
    sciPush = ""
    if(axis1[3] > .1):
        sciRot = "11"
    elif(axis1[3] > -.1):
        sciRot = "00"
    else:
        sciRot = "10"
    #print("sciRot:" +sciRot)
    
    if(axis0[0] > .1):
        sciPush = "11"
    elif(axis0[0] > -.1):
        sciPush = "00"
    else:
        sciPush = "10"
    #print("sciPush:" +sciPush)
        
    """
    hand motors (joystick2)
    yaw: axis2[0]
    pitch: axis2[1]
    pinchers: axis2[2]
    roll: axis2[3]
    
    """
    yaw = ""
    pitch = ""
    roll = ""
    pinchers = ""
    #full right
    if(axis2[0] > .1):
        yaw = "11"
    #stop
    elif(axis2[0] > -.1):
        yaw = "00"
    #full left
    else:
        yaw = "10"
    #print("yaw" + yaw)

    #full up
    if(axis2[1] > .1):
        pitch = "11"
    #stop
    elif(axis2[1] > -.1):
        pitch = "00"
    #full down
    else:
        pitch = "10"
    #print("pitch" + pitch)

    #full right
    if(axis2[3] > .1):
        roll = "11"
    #stop
    elif(axis2[3] > -.1):
        roll = "00"
    #full left
    else:
        roll = "10"
    #print("roll" + roll)

    #grab
    if(axis2[2] > .1):
        pinchers = "11"
    #stop
    elif(axis2[2] > -.1):
        pinchers = "00"
    #release
    else:
        pinchers = "10"
    #print("pinchers" + pinchers)

    """
    arm movement
    joystick 3
    elbow 1: axis3[1]
    elbow 2: 
    rotation: axis3[3]
    augar: axis3[2]
    """
    armElbow1 = ""
    armElbow2 = ""
    armRot = ""
    armAugar =""
    #full down
    if(axis3[1] > .1):
        armElbow1 = "11"
    #stop
    elif(axis3[1] > -.1):
        armElbow1 = "00"
    #full up
    else:
        armElbow1 = "10"
    #print("armElbow1" + armElbow1)
    """
    This one needs a better control chosen
    """
    #full down
    if(axis3[1] > .1):
        armElbow2 = "11"
    #stop
    elif(axis3[1] > -.1):
        armElbow2 = "00"
    #full up
    else:
        armElbow2 = "10"
    #print("armElbow2" + armElbow2)

    #full right
    if(axis3[3] > .1):
        armRot = "11"
    #stop
    elif(axis3[3] > -.1):
        armRot = "00"
    #full left
    else:
        armRot = "10"
    #print("armRot" + armRot)

    #full up
    if(axis3[2] > .1):
        armAugar = "11"
    #stop
    elif(axis3[2] > -.1):
        armAugar = "00"
    #full down
    else:
        armAugar = "10"
    #print("armAugar" + armAugar)


    

         
    data = leftDrive + rightDrive + "00000000" + "00000000" + roll + pitch + yaw +pinchers +armRot+ armElbow1 + armElbow2 + armAugar + sciPush + sciRot + "0000" +"00000000"
    print (data)
    sent = sock.sendto(data, address)
