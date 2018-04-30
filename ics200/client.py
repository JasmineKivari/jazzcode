import sys, socket
import os

s1= socket.socket(socket.AF_INET, socket.SOCK_STREAM)

ip = str(sys.argv[1])
port = int(sys.argv[2])
filefunction = sys.argv[3] # get,put, del command
file = sys.argv[4] #file name
MESSAGE = "\nHello JASMINE!"

filename = filefunction + file  #get/put/del + filename
s1.connect((ip, port))
if sys.argv[3] == "GET":
    s1.sendto(MESSAGE.encode("utf-8"),(ip, port))
    ready_message = s1.recv(1024) #ok
    print (ready_message.decode("utf-8"))
    s1.send(filename.encode("utf-8"))
    ok_message = s1.recv(1024)
    print(ok_message.decode("utf-8"))
    s1.send("READY".encode("utf-8"))
    numbites_rec = s1.recv(1024)
    print(numbites_rec.decode("utf-8"))
    s1.send("OK".encode("utf-8"))
    rec_bites = s1.recv(1024)
    
    totalRecv = len(rec_bites)
    
with open(file, 'wb') as filename:
    while True:
        data = rec_bites.recv(1024)
        if not data:
            break
        filename.write(data)
    filename.close()
    
    print(rec_bites.decode("utf-8"))
    
    serv_done = s1.recv(1024)
    
    print(serv_done.decode("utf-8"))
	
		
    print("This is GET")
elif sys.argv[3] == "PUT":
    print("This is PUT")
elif sys.argv[3] == "DEL":
    print("This is DELETE")

		

