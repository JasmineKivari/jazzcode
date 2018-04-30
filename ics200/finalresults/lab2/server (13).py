import sys, socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(("", int(sys.argv[1])))

while True: 
	bite = bytearray(4)
	packet, address = s.recvfrom(7)
	opp = packet[0]
	pack = packet[1] 
	
	if opp == 1:
		result = 0
		biteinpacket = 2
		for i in range(0, pack, 2):
			part1 = (packet[biteinpacket] >>4)
			part2 = (packet[biteinpacket] & 0x0f)
			result += part1 + part2
			biteinpacket += 1
			# bit7 = 2**7
			# test_a = a & bit7
			# if test_a == bit7:
				# # negative number
				# a = a - 2**8
			# print("a is: %d" % a)
			
	if opp == 2:
		result = (packet[2] >> 4) - (packet[2] & 0x0f)
		biteinpacket = 3
		for i in range(0, pack - 2, 2):
			part1 = (packet[biteinpacket] >> 4)
			part2 = (packet[biteinpacket] & 0x0f)
			result -= part1 + part2
			biteinpacket += 1
			
	if opp == 4:
		result = 1
		biteinpacket = 2
		quantity = 0
		for i in range(0, pack, 2):
			part1 = (packet[biteinpacket] >> 4)
			part2 = (packet[biteinpacket] & 0x0f)
			result *= part1
			quantity += 1
			if quantity < pack:
				result *= part2
				quantity += 1
			biteinpacket += 1
		
	bite[0] = (result & 0xff000000) >> 24
	bite[1] = (result & 0x00ff0000) >> 16
	bite[2] = (result & 0x0000ff00) >> 8
	bite[3] = (result & 0x000000ff) >> 0
	
	s.sendto(bite, address)



