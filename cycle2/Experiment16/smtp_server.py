#!/usr/bin/env python3

import socket
import threading

HOST = '127.0.0.1'  # Standard loopback interface address (localhost)
PORT = 65432        # Port to listen on (non-privileged ports are > 1023)

user_emails = {}
global_mail_box = {}

  
def client_callback(conn,addr):
    while True:
        option = conn.recv(1024)
        if(option!=""):
            option = int(option.decode())
            if option == 1:
                to = conn.recv(1024)
                to = to.decode()
                body = conn.recv(1024)
                body = body.decode()
                email = "From: "+user_emails[addr]+"\nTo :"+to+"\nBody :"+body
                for key,value in user_emails.items():
                    if value == to:
                        if key in global_mail_box.keys():
                            global_mail_box[key].append(email)
            elif option == 2:
                #Send back mailbox
                conn.sendall(str(global_mail_box[addr]).encode())
            else:
                #Exit
                exit(0)
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
s.bind((HOST, PORT))
s.listen()
while True:

    conn, addr = s.accept()
    print('Connected by', addr)
    email = conn.recv(1024)
    user_emails[addr] = email.decode()
    global_mail_box[addr] = []
    t = threading.Thread(target=client_callback,args=(conn,addr))
    t.start()
