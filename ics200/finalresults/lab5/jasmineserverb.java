package ics200.lab5;

import java.io.*;
import java.net.*;
import java.lang.*;
import java.util.*;

public class jasmineserverb {

	public static void main(String[] args) throws IOException {

			BufferedInputStream buffin;
			BufferedOutputStream buffout;
			int port = Integer.parseInt(args[0]);

			ServerSocket serverSocket = new ServerSocket(port);

			while (true) {
					Socket socketofclient = serverSocket.accept();
					buffin = new BufferedInputStream(socketofclient.getInputStream());
					buffout = new BufferedOutputStream(socketofclient.getOutputStream());
					
			    DataOutputStream outd = new DataOutputStream(new BufferedOutputStream(socketofclient.getOutputStream()));
				  DataInputStream innd = new DataInputStream(new BufferedInputStream(socketofclient.getInputStream()));
					
					BufferedReader reeder = new BufferedReader(new InputStreamReader(socketofclient.getInputStream()));
				
			   	PrintWriter riter = new PrintWriter(socketofclient.getOutputStream());

					String messageOfclient = "READY";	
          riter.println(messageOfclient);
          riter.flush();					

					
					byte[] packet = new byte[1024];
					buffin.read(packet);
					
					int opp = packet[0];
					int P = packet[1]; 
					int result = 0;
					int i;
					int maskofA = 0x0f;
					int maskofB = 0xf0;
					

					if (opp == 1) {
						int j = 2;
						for (i = 0; i < P; i += 2) {
							int x = ((maskofB & packet[j]) >>> 4);
							int y = (packet[j] & 0x0f);
							result += x + y;
							j += 1;
						}
					}
					
					
					if (opp == 2) {					
						result = ((packet[2] >>> 4) & maskofA) - (packet[2] & 0x0f);
						int j = 3;
						for (i = 0; i < P - 2; i += 2) {
							int x = ((maskofB & packet[j]) >>> 4);
							int y = (packet[j] & 0x0f);
							result -= x + y;
							j += 1;
						}
					}
					
					if (opp == 4) {
						result = 1;
						int j = 2;
						int operation = 0;
						for (i = 0; i < P; i += 2) {
							int x = ((maskofB & packet[j]) >>> 4);
							int y = (packet[j] & 0x0f);
							result *= x; 
							operation += 1;
							if (operation < P) {
								result *= y;
								operation += 1;
							}
							j += 1;
						}
					}

					outd.writeInt(result);
					outd.flush();


			}

	}

}
