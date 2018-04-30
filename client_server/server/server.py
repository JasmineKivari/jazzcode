import sys, socket, os

# for -v flag
verboseflag = False

#for the port
porttoconnect = int(sys.argv[1])

#socket objects
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("", porttoconnect))
s.listen(5)

if "-v" in sys.argv: verboseflag = True


if verboseflag:
	print("Server waiting on port " + str(porttoconnect))

while True:
	client, address = s.accept()
	
	if verboseflag:
		print("Server connected to client at %s:%s" % (address[0], address[1]))	
	
	client.send("READY".encode("utf-8"))
	arrivinginfo = client.recv(1024)
	command, nameofFile = arrivinginfo.decode("utf-8").split()

	if command == "PUT":
		client.send("OK".encode("UTF-8"))
		bytes = int.from_bytes(client.recv(1024), byteorder='big', signed=False)
		client.send("OK".encode("UTF-8"))
		if verboseflag:
			print("Server receiving request: %s %s" % (command, nameofFile))
		try:
			f = open(nameofFile, 'wb')
			if verboseflag:
				print("Server recieving %s bytes" % (bytes))
			while bytes > 0:
				file = client.recv(1024)
				f.write(file)
				bytes -= len(file)
			f.close()	
			client.send("DONE".encode("UTF-8"))
		except:
			client.send(("ERROR: unable to create file " + nameofFile).encode("UTF-8"))
			
	elif command == "GET":
		if os.path.exists(nameofFile) and os.access(nameofFile, os.R_OK):
			client.send("OK".encode("utf-8"))
			readyMessage = client.recv(1024)
			if verboseflag:
				print("Server receiving request: %s %s" % (command, nameofFile))
			if readyMessage.decode("utf-8") == "READY":
				amountOfBytes = os.path.getsize(nameofFile)
				client.send(amountOfBytes.to_bytes(8, byteorder='big', signed=False))
				if verboseflag:
					print("Server sending %s bytes" % (amountOfBytes))
			ok_rcv = client.recv(1024)	
			if ok_rcv.decode("utf-8") == "OK":
				f = open(nameofFile,'rb')
				l = f.read(1024)	
				while (l):
					client.send(l)
					l = f.read(1024)
			client.send("DONE".encode("utf-8"))
		else:
			client.send(("ERROR: " + nameofFile + " does not exist").encode("utf-8"))
			
	elif command == "DEL":
		try:
		
			os.remove(nameofFile)		
			if verboseflag:
				print("Server deleting file " + nameofFile)
			client.send("DONE".encode("utf-8"))	
		except:
			client.send(("ERROR: " + nameofFile + " does not exist").encode("utf-8"))
		