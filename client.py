import socket

s=socket.socket()

s.connect(('localhost', 1234))

print("Connected!")

while True:
    msg = input("You: ")
    s.send(msg.encode())

    reply = s.recv(1024).decode()
    print("Server:", reply)