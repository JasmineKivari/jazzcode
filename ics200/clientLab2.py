import sys, socket
import math

with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s1:

	integer = int(len(sys.argv) - 4) 	
	bOp = bytearray(math.ceil(integer / 2.0) + 2)
	address= sys.argv[1]
	
	if sys.argv[3] == "+":
		bOp[0] = 1
		print("This is Addition")
	elif sys.argv[3] == "-":
		bOp[0] = 2
		print("This is Subtraction")
	elif sys.argv[3] == "*":
		bOp[0] = 4
		print("This is Multiplication")

	bOp[1] = integer
	
	biteinpacket = 2
	for i in range(0, integer, 2):
		part2 = 0
		if (i + 5) < len(sys.argv):
			part2 = int(sys.argv[i + 5])
		part1 = int(sys.argv[i + 4])
		bOp[biteinpacket] = (part1 << 4) | part2
		biteinpacket += 1

	s1.sendto(bOp, (address, int(sys.argv[2])))
	packet = s1.recv(4)
	result = ((packet[0] << 24 | (packet[1] << 16) | packet[2] << 8) | (packet[3]))
	if result >= 2**31:
		result -= 2**32
	print ("\nThis is the result: ")
	print(result)
	
	s1.close()

