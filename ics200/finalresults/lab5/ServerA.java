//package ics200.lab5;

import java.io.*;
import java.net.*;
import java.lang.*;
import java.util.*;

public class ServerA {

	public static void main(String[] args) throws IOException {

			BufferedInputStream buffin;
			
            BufferedOutputStream buffout;
			
            int port = Integer.parseInt(args[0]);

			ServerSocket socketofserv = new ServerSocket(port);

			while (true) {
					
                    Socket socketofclient = socketofserv.accept();
					
                    
                    buffin = new BufferedInputStream(socketofclient.getInputStream());
					buffout = new BufferedOutputStream(socketofclient.getOutputStream());

					String messageOfclient = new String("READY");
					buffout.write(messageOfclient.getBytes("UTF-8"));
					
                    buffout.flush();
					
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
					
					byte[] bitey = new byte[4];
					
					bitey[0] = (byte)((result & 0xff000000) >> 24);
					bitey[1] =	(byte)((result & 0x00ff0000) >> 16);
					bitey[2] = (byte)((result & 0x0000ff00) >> 8);
					bitey[3] = (byte)((result & 0x000000ff) >> 0);
					
					buffout.write(bitey);
					buffout.flush();

			}

	}

}
