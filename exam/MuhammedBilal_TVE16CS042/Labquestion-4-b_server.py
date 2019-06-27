import socket
import threading


matrix = []
#int_mat = []

def spiral_creator(mat,N):
	N = int(N)
	left=top=0
	bottom=right=N
	spiral=[]
	print(mat)
	if N%2 == 1:
		N = int(N/2)+1
	else:
		N = int(N/2)
	for i in range(N):
		for j in range(left,right):
			spiral.append(mat[top][j])
		top+=1
#		print(spiral)
		for j in range(top,bottom):
			spiral.append(mat[j][right-1])
		right-=1
#		print(spiral)

		for j in range(right-1,left,-1):
			spiral.append(mat[bottom-1][j])
		bottom-=1
#		print(spiral)

		for j in range(bottom,top-1,-1):
			spiral.append(mat[j][left])
		left+=1
#		print(spiral)

	return spiral
def clientCallBack(conn,addr):
	matrix = conn.recv(1024)
	matrix = matrix.decode()	
	invalid_chars = ['[',']',' ',',','"']
	N = 0
	int_mat = []
	N = 0
	l = 0
	k = []
#	for i in matrix:
#		if i not in invalid_chars:
#			N+=1
#	N = int(N**0.5)
#	for i in matrix:
#		if i not in invalid_chars:
#			l+=1
#			k.append(int(i))
#			if l == N:
#				int_mat.append(k)
#				k = []
#				l = 0


	print(matrix)
	#int_mat= [[1,2,3,4],[12,13,14,5],[11,16,15,6],[10,9,8,7]]
	print(int_mat)
	int_mat = spiral_creator(int_mat,N)
	print(int_mat)
	conn.send(str(int_mat).encode())
s = socket.socket(socket.AF_INET,socket.SOCK_STREAM,socket.IPPROTO_TCP)
port = 8000
address = ("",port)
s.bind(address)
s.listen()
while(True):
	connection,addr = s.accept()
	t = threading.Thread(target=clientCallBack,args=(connection,addr))
	t.start()
	t.join()
	break
