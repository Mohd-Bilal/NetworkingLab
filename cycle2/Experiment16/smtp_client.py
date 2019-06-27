import socket
import ast

HOST = '127.0.0.1'  # The server's hostname or IP address
PORT = 65432        # The port used by the server

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
email = input("Enter preferred email :")
s.sendall(email.encode())
while True:
    print("\n_______________________EMAIL_______________________\n")
    print("\n1.Compose Mail\n2.View mailbox\n3.Exit\n")
    option = int(input("Enter choice :"))
    s.sendall(str(option).encode())
    if option == 1:
        to = input("To :")
        body = input("Body :")
        s.sendall(to.encode())
        s.sendall(body.encode())
    elif option == 2:
        mailbox = s.recv(1024)
        mailbox = ast.literal_eval(mailbox.decode())
        for index,mail in enumerate(mailbox):
            print("\n_______________________MAIL : ",index+1,"____________________\n")
            print(mail)
            print("\n_____________________________________________________________\n")
    else :
        exit(0)