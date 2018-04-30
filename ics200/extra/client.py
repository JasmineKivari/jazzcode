import sys, socket, os

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host = sys.argv[1]
port = int(sys.argv[2])
command = sys.argv[3]
file = sys.argv[4]
done_message = "DONE"

verbose = False

if command == "PUT":
	if not os.path.exists(file):
		print("File not found")
		sys.exit()

sock.connect((host, port))
ready = sock.recv(1024)

sock.send((command + " " + file).encode("UTF-8"))

if command == "PUT":
	if os.path.exists(file) and os.access(file, os.R_OK):
		okay_rcv = sock.recv(1024)
		if okay_rcv.decode('UTF-8') == "OK":
			byte_count = os.path.getsize(file)
			sock.send(byte_count.to_bytes(8, byteorder='big', signed=False))
			okay_rcv = sock.recv(1024)	
			if okay_rcv.decode('UTF-8') == "OK":		
				print("Client sending file %s (%d bytes)" % (file, byte_count))
				f = open(file,'rb')
				l = f.read(1024)	
				while (l):
					sock.send(l)
					l = f.read(1024)
				finished = sock.recv(1024)
				if finished.decode("UTF-8") == done_message:
					print("Complete")
		else:
			if ("ERROR") in okay_rcv.decode("UTF-8"):
				i = okay_rcv.decode("UTF-8").index("ERROR")
				i += 7
				print("server error: " + okay_rcv.decode("UTF-8")[i:])
	else:
		print("File not found")
	sock.close()
  
if command == "GET":
	okay_rcv = sock.recv(1024)
	if okay_rcv.decode("UTF-8") == "OK":
		sock.send("READY".encode("UTF-8"))
		bytes = int.from_bytes(sock.recv(1024), byteorder='big', signed=False)
		print("Client recieving file " + file + " " + "(" + str(bytes) + " bytes)")
		sock.send("OK".encode("UTF-8"))
		try:
			f = open(file,'wb')
			while bytes > 0:
				new_file = sock.recv(min(1024, bytes))
				f.write(new_file)
				bytes -= len(new_file)
			f.close()
		except:
			print("client error: unable to create file " + file)
			sock.close()
		finished = sock.recv(1024)
		if finished.decode("UTF-8") == done_message:
			print("Complete")
		else:
			print(finished.decode("UTF-8"))
	else:
		if ("ERROR") in okay_rcv.decode("UTF-8"):
			i = okay_rcv.decode("UTF-8").index("ERROR")
			i += 7
			print("server error: " + okay_rcv.decode("UTF-8")[i:])
	sock.close()

if command == "DEL":
	print("Client deleting file %s" % (file))	
	finished = sock.recv(1024)
	if finished.decode("UTF-8") == done_message:
		print("Complete")
	else:
		if ("ERROR") in finished.decode("UTF-8"):
			i = finished.decode("UTF-8").index("ERROR")
			i += 7
			print("server error: " + finished.decode("UTF-8")[i:])
	sock.close()  
