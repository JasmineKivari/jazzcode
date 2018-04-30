import sys, socket, os

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host = sys.argv[1]
porttoconnect = int(sys.argv[2])
command = sys.argv[3]
file = sys.argv[4]
finishedMessage = "DONE"

verboseflag = False

if command == "PUT":
	if not os.path.exists(file):
		print("File cannot be found!")
		sys.exit()

s.connect((host, porttoconnect))
readyMessage = s.recv(1024)
s.send((command + " " + file).encode("utf-8"))

if command == "PUT":
	if os.path.exists(file) and os.access(file, os.R_OK):
		ok_rcv = s.recv(1024)
		if ok_rcv.decode("utf-8") == "OK":
			amountOfBytes = os.path.getsize(file)
			s.send(amountOfBytes.to_bytes(8, byteorder='big', signed=False))
			ok_rcv = s.recv(1024)	
			if ok_rcv.decode("utf-8") == "OK":		
				print("Client sending file %s (%d bytes)" % (file, amountOfBytes))
				f = open(file,'rb')
				l = f.read(1024)	
				while (l):
					s.send(l)
					l = f.read(1024)
				complete = s.recv(1024)
				if complete.decode("utf-8") == finishedMessage:
					print("Complete")
		else:
			if ("ERROR") in ok_rcv.decode("utf-8"):
				i = ok_rcv.decode("utf-8").index("ERROR")
				i += 7
				print("server error: " + ok_rcv.decode("utf-8")[i:])
	else:
		print("File cannot be found!")
	s.close()
  
if command == "GET":
	ok_rcv = s.recv(1024)
	if ok_rcv.decode("utf-8") == "OK":
		s.send("READY".encode("utf-8"))
		bytes = int.from_bytes(s.recv(1024), byteorder='big', signed=False)
		print("Client recieving file " + file + " " + "(" + str(bytes) + " bytes)")
		s.send("OK".encode("utf-8"))
		try:
			f = open(file,'wb')
			while bytes > 0:
				Newerfile = s.recv(min(1024, bytes))
				f.write(Newerfile)
				bytes -= len(Newerfile)
			f.close()
		except:
			print("client error: unable to create file " + file)
			s.close()
		complete = s.recv(1024)
		if complete.decode("UTF-8") == finishedMessage:
			print("Complete")
		else:
			print(complete.decode("utf-8"))
	else:
		if ("ERROR") in ok_rcv.decode("utf-8"):
			i = ok_rcv.decode("utf-8").index("ERROR")
			i += 7
			print("server error: " + ok_rcv.decode("utf-8")[i:])
	s.close()

if command == "DEL":
	print("Client deleting file %s" % (file))	
	complete = s.recv(1024)
	if complete.decode("utf-8") == finishedMessage:
		print("Complete")
	else:
		if ("ERROR") in complete.decode("utf-8"):
			i = complete.decode("utf-8").index("ERROR")
			i += 7
			print("server error: " + complete.decode("utf-8")[i:])
	s.close()  
