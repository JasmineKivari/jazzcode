import threading, sys, socket, os, collections, time

class ClientHandler(threading.Thread):

	def __init__(self, client):
		threading.Thread.__init__(self)
		self.client = client
		
	def run(self):
		client = self.client
		client.send("READY".encode("UTF-8"))
		incoming = client.recv(1024)
		command, fileName = incoming.decode("UTF-8").split()

		if command == "PUT":
			client.send("OK".encode("UTF-8"))
			bytes = int.from_bytes(client.recv(1024), byteorder='big', signed=False)
			client.send("OK".encode("UTF-8"))
			try:
				f = open(fileName, 'wb')
				while bytes > 0:
					file = client.recv(1024)
					f.write(file)
					bytes -= len(file)
				f.close()	
				client.send("DONE".encode("UTF-8"))
			except:
				client.send(("ERROR: unable to create file " + fileName).encode("UTF-8"))
				
		elif command == "GET":
			if os.path.exists(fileName) and os.access(fileName, os.R_OK):
				client.send("OK".encode("UTF-8"))
				ready = client.recv(1024)
				if ready.decode("UTF-8") == "READY":
					byte_count = os.path.getsize(fileName)
					client.send(byte_count.to_bytes(8, byteorder='big', signed=False))
				okay_rcv = client.recv(1024)	
				if okay_rcv.decode('UTF-8') == "OK":
					f = open(fileName,'rb')
					l = f.read(1024)	
					while (l):
						client.send(l)
						l = f.read(1024)
				client.send("DONE".encode("UTF-8"))
			else:
				client.send(("ERROR: " + fileName + " does not exist").encode("UTF-8"))
				
		elif command == "DEL":
			try:
				os.remove(fileName)		
				client.send("DONE".encode("UTF-8"))	
			except:
				client.send(("ERROR: " + fileName + " does not exist").encode("UTF-8"))
				
class Manager(threading.Thread):	

	def __init__(self, resources):
		threading.Thread.__init__(self)
		self.resources = resources

		self.q = collections.deque()
		self.running = set()
		
	def run(self):
		while True:
			kick = []
			# Check the running threads, and remove if neccessary
			#print("Working")
			for x in self.running:
				if not x.isAlive(): kick.append(x)
			for x in kick:
				self.running.remove(x)		
			# Check the waiting queue
			if len(self.q) == 0:
				time.sleep(1)
				continue
			else:
				if len(self.running) == resources:
					time.sleep(1)
					continue
				else:
					#print("Doing stuff!")
					t = self.q.popleft()
					t.start()
					self.running.add(t)

	def addClient(self, t):
		self.q.append(t)
				

### Socket setup
port = int(sys.argv[1])
resources = int(sys.argv[2])

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(("", port))
sock.listen(5)
###	

m = Manager(resources)
m.start()

while True:
	client, address = sock.accept()
	t = ClientHandler(client)
	m.addClient(t)
	#t.start() # hands this off to the "manager"