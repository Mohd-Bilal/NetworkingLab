import socket

HOST = "127.0.0.1"
PORT = 65432 

s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.connect((HOST,PORT))
while True:
    filename = input("Enter the name of the file :")
    
    s.sendall(filename.encode())
    if filename == "exit":
        exit(0) 
    server_pid = s.recv(1024)
    server_pid = server_pid.decode()
    data = s.recv(1024)
    data = data.decode()
    print("Server PID :",server_pid)
    if data != "File Not Found !":
        f = open("./downloaded/"+filename,'w')
        f.write(data)
        print("\nFile Data \n",data)
    else:
        print("\nFile Not Found")