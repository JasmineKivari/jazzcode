import sys, socket, os

verbose = False
port = int(sys.argv[1])

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(("", port))
sock.listen(5)

if "-v" in sys.argv: verbose = True


if verbose:
	print("Server waiting on port " + str(port))

while True:
	client, address = sock.accept()
	
	if verbose:
		print("Server connected to client at %s:%s" % (address[0], address[1]))	
	
	client.send("READY".encode("UTF-8"))
	incoming = client.recv(1024)
	command, fileName = incoming.decode("UTF-8").split()

	if command == "PUT":
		if os.path.exists(fileName):
			client.send("OK".encode("UTF-8"))
			bytes = int.from_bytes(client.recv(1024), byteorder='big', signed=False)
			client.send("OK".encode("UTF-8"))
			if verbose:
				print("Server receiving request: %s %s" % (command, fileName))
			f = open(fileName, 'wb')
			if verbose:
				print("Server recieving %s bytes" % (bytes))
			while bytes > 0:
				file = client.recv(1024)
				f.write(file)
				bytes -= len(file)
			f.close()	
			client.send("DONE".encode("UTF-8"))
		else:
			client.send(("ERROR: unable to create file " + fileName).encode("UTF-8"))
			
	elif command == "GET":
		if os.path.exists(fileName):
			client.send("OK".encode("UTF-8"))
			ready = client.recv(1024)
			if verbose:
				print("Server receiving request: %s %s" % (command, fileName))
			if ready.decode("UTF-8") == "READY":
				byte_count = os.path.getsize(fileName)
				client.send(byte_count.to_bytes(8, byteorder='big', signed=False))
				if verbose:
					print("Server sending %s bytes" % (byte_count))
			okay_rcv = client.recv(1024)	
			if okay_rcv.decode('UTF-8') == "OK":
				if verbose:
					print("Server sending file %s (%d bytes)" % (fileName, byte_count))
				f = open(fileName,'rb')
				l = f.read(1024)	
				while (l):
					client.send(l)
					l = f.read(1024)
			client.send("DONE".encode("UTF-8"))
		else:
			client.send(("ERROR: " + fileName + " does not exist").encode("UTF-8"))
			
	elif command == "DEL":
		if os.path.exists(fileName):
			os.remove(fileName)		
			if verbose:
				print("Server deleting file " + fileName)
			client.send("DONE".encode("UTF-8"))	
		else:
			client.send(("ERROR: " + fileName + " does not exist").encode("UTF-8"))
		