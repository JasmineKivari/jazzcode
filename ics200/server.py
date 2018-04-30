import sys, socket
import os


ip= "localhost"
port = 1111


s1 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s1.bind(("", port))
s1.listen(5)

while True: 
    client, address = s1.accept()
    print ("Connection address: ")
    print(address)
    data = client.recv(1024)
    if not data: 
        break
    print("Recieved data:")
    print(data.decode("utf-8"))
    client.send("READY".encode("utf-8"))
    # this is where Get will go
    comm_filename = client.recv(1024)
    print(comm_filename)
    command = comm_filename[:3].decode("utf-8")
    file_input = comm_filename[3:].decode("utf-8")
    print(command)
    print(file_input)
    client.send("OK".encode("utf-8"))
    clientready = client.recv(1024)
    print(clientready.decode("utf-8"))
    client.send("This is where I send the number biiites".encode("utf-8"))
    okmess = client.recv(1024)
    print(okmess.decode("utf-8"))
     with open(file_input, 'rb') as f:
        for data in f:
            client.send(f)  
    
    
    client.send("DONE".encode("utf-8"))
client.close()








