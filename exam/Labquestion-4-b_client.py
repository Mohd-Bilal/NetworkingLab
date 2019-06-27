'''
	CLIENT FOR TCP/UDP SPIRAL
	AUTHOR : MUHAMMED BILAL A

'''

import socket

s = socket.socket(socket.AF_INET,socket.SOCK_STREAM,socket.IPPROTO_TCP)
port = 8000
address =("127.0.0.1",port)
s.connect(address)
N = int(input("Enter the size of the matrix :"))
matrix = []

for i in range(N):
	k =[]
	for j in range(N):
		k.append(int(input()))
	matrix.append(k)
s.send(str(matrix).encode())
spiral = s.recv(1024)
print(spiral.decode())
