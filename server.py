import socket

s=socket.socket()
s.bind(('localhost', 1234))
s.listen(1)

print("server is listening on port 1234...")

c,addr=s.accept()
print("connection established with", addr)

while True:
    msg=c.recv(1024).decode()
    print("client:", msg)

    reply=input("you: ")
    c.send(reply.encode())

