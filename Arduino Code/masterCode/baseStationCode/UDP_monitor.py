import socket

UDP_IP = "192.168.1.121"
UDP_PORT = 8888
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))

while True:
    data, address = sock.recvfrom(1024)
    print data