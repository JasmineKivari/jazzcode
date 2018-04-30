//package ics200.lab5;

import java.io.*;
import java.net.*;
import java.lang.*;
import java.util.*;

public class ServerA {

	public static void main(String[] args) throws IOException {

			BufferedInputStream bin;
			BufferedOutputStream bout;
			int port = Integer.parseInt(args[0]);

			ServerSocket serverSocket = new ServerSocket(port);

			while (true) {
					Socket clientSocket = serverSocket.accept();
					bin = new BufferedInputStream(clientSocket.getInputStream());
					bout = new BufferedOutputStream(clientSocket.getOutputStream());

					String clientMessage = new String("READY");
					bout.write(clientMessage.getBytes("UTF-8"));
					bout.flush();
					
					byte[] packet = new byte[1024];
					bin.read(packet);
					
					int operator = packet[0];
					int N = packet[1]; 
					int result = 0;
					int i;
					int maskA = 0x0f;
					int maskB = 0xf0;
					

					if (operator == 1) {
						int j = 2;
						for (i = 0; i < N; i += 2) {
							int x = ((maskB & packet[j]) >>> 4);
							int y = (packet[j] & 0x0f);
							result += x + y;
							j += 1;
						}
					}
					
					// Subtraction case
					if (operator == 2) {					
						result = ((packet[2] >>> 4) & maskA) - (packet[2] & 0x0f);
						int j = 3;
						for (i = 0; i < N - 2; i += 2) {
							int x = ((maskB & packet[j]) >>> 4);
							int y = (packet[j] & 0x0f);
							result -= x + y;
							j += 1;
						}
					}
					// Multiplication case		
					if (operator == 4) {
						result = 1;
						int j = 2;
						int operands = 0;
						for (i = 0; i < N; i += 2) {
							int x = ((maskB & packet[j]) >>> 4);
							int y = (packet[j] & 0x0f);
							result *= x; 
							operands += 1;
							if (operands < N) {
								result *= y;
								operands += 1;
							}
							j += 1;
						}
					}
					
					byte[] b1 = new byte[4];
					
					b1[0] = (byte)((result & 0xff000000) >> 24);
					b1[1] =	(byte)((result & 0x00ff0000) >> 16);
					b1[2] = (byte)((result & 0x0000ff00) >> 8);
					b1[3] = (byte)((result & 0x000000ff) >> 0);
					
					bout.write(b1);
					bout.flush();

			}

	}

}
