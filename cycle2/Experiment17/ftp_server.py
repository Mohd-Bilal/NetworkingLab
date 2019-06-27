import socket
import threading
import os

HOST = '127.0.0.1'  
PORT = 65432    

def userCallBack(conn,addr):
    while True:
        filename = conn.recv(1024)
        print(filename)
        filename = filename.decode()
        print(filename)
        if filename == "exit":
            exit(0)
        data = ""
        try:
            if filename != "":
                file = open("./files/"+filename,'r')
                data = file.read()
                if data == "":
                    data = "File Contains no data"
        except FileNotFoundError:
            data = "File Not Found !"
        pid = os.getpid()
        conn.sendall(str(pid).encode())
        conn.sendall(data.encode())
s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.bind((HOST,PORT))
s.listen()

while True:

    conn,addr = s.accept()
    print("Connected by :",addr)
    t = threading.Thread(target=userCallBack,args=(conn,addr))
    t.start()