import threading, sys, socket, os, collections, time

class ClientHandler(threading.Thread):

	def __init__(self, client):
		threading.Thread.__init__(self)
		self.client = client
		
	def run(self):
		client = self.client
		client.send("READY".encode("utf-8"))
		arrivinginfo = client.recv(1024)
		command, nameofFile = arrivinginfo.decode("utf-8").split()

		if command == "PUT":
			client.send("OK".encode("utf-8"))
			bytes = int.from_bytes(client.recv(1024), byteorder='big', signed=False)
			client.send("OK".encode("utf-8"))
			try:
				f = open(nameofFile, 'wb')
				while bytes > 0:
					file = client.recv(1024)
					f.write(file)
					bytes -= len(file)
				f.close()	
				client.send("DONE".encode("utf-8"))
			except:
				client.send(("ERROR: unable to create file " + nameofFile).encode("utf-8"))
				
		elif command == "GET":
			if os.path.exists(nameofFile) and os.access(nameofFile, os.R_OK):
				client.send("OK".encode("utf-8"))
				readyMessage = client.recv(1024)
				if readyMessage.decode("utf-8") == "READY":
					amountOfBytes = os.path.getsize(nameofFile)
					client.send(amountOfBytes.to_bytes(8, byteorder='big', signed=False))
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
				client.send("DONE".encode("utf-8"))	
			except:
				client.send(("ERROR: " + nameofFile + " does not exist").encode("utf-8"))
				
class Manager(threading.Thread):	

	def __init__(self, resources):
		threading.Thread.__init__(self)
		self.resources = resources

		self.q = collections.deque()
		self.running = set()
		
	def run(self):
		while True:
			kick = []
			for r in self.running:
				if not r.isAlive(): kick.append(r)
			for r in kick:
				self.running.remove(r)		
			if len(self.q) == 0:
				time.sleep(1)
				continue
			else:
				if len(self.running) == resources:
					time.sleep(1)
					continue
				else:
					t = self.q.popleft()
					t.start()
					self.running.add(t)

	def addClient(self, t):
		self.q.append(t)
				


porttoconnect = int(sys.argv[1])
resources = int(sys.argv[2])

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("", porttoconnect))
s.listen(5)


m = Manager(resources)
m.start()

while True:
	client, address = sock.accept()
	t = ClientHandler(client)
	m.addClient(t)
	