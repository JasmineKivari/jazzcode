import socket
import sys

s1= socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s2= socket.socket(socket.AF_INET, socket.SOCK_STREAM)

url= sys.argv[1].split("/")
resource = "/" + url[3] + "/" + url[4]
host= url[2]
request= "GET %s HTTP/1.1\r\nhost: %s\r\n\r\n" %(resource, host)

s1.connect( (host, 80) )
s1.send(request.encode("utf-8"))
#html= s1.recv(1024).decode("utf-8")
html2textHost = "rtvm.cs.camosun.bc.ca"
#print (html)


# navigate HTTP protocol until the resource is about to be transferred

s2.connect( (html2textHost, 10010) )
#s2.send(request.encode("utf-8"))
status= s2.recv(1024).decode("utf-8")
#print (status)
	

# navigate the html2text protocol until the server is expecting bytes of
# HTML code.

# now start reading and writing.
state = 1
#html2 = " "
oldBlock= ""
newBlock= ""
while state != 4:
	if state == 1:
		newBlock= s1.recv(1024).decode("utf-8")
		beginning= (oldBlock + newBlock).upper().find("<HTML>")
		#ending = html.upper().find("</HTML>") + 7
		#print("\nthis is the html \n" + html + "\nthis is html from beginning to end\n" + html[beginning:ending])
		if beginning >=0:
			state = 2
		else:
			#html2 = html[beginning:]
			oldBlock = newBlock
			#state = 2
		
	
	
	if state == 2:
		if "</HTML>" in (oldBlock + newBlock):
			ending = (oldBlock + newBlock).upper().find("</HTML>")
		#output for test 2
			s2.send(newBlock[beginning:ending + 7 - len(oldBlock)].encode("utf-8"))
			oldBlock= ""
			state = 3
		#print("\nI'm in state two \n" + str(ending))
		else:
			s2.send(newBlock[beginning:].encode("utf-8"))
			
			oldBlock = newBlock
			
			newBlock = s1.recv(1024).decode("utf-8")
			beginning = 0
		#state = 3
			
	
	if state == 3:
		newBlock = s2.recv(1024).decode("utf-8")
		end = (oldBlock + newBlock).find('ICS 200 HTML CONVERT COMPLETE')
		if end == -1:
			print(oldBlock, end='')
			oldBlock=newBlock

		else:
			print((oldBlock+newBlock)[:end], end='')
			state = 4
			
s1.close()
s2.close()

		
		
		


