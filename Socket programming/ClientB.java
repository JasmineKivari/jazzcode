//package ics200.lab5;

import java.io.*;
import java.net.*;
import java.lang.*;
import java.util.*;

public class ClientB {

    public static void main(String[] args) throws IOException {

        int ints = (args.length - 3);
        String server = args[0];
        byte[] b = new byte[(byte)(Math.ceil(ints / 2.0) + 2)];
        int port = Integer.parseInt(args[1]);
        Socket socket;
        socket = new Socket(server, port);
        
        BufferedInputStream is = new BufferedInputStream(socket.getInputStream());
        BufferedOutputStream os = new BufferedOutputStream(socket.getOutputStream());
				
				DataOutputStream dout = new DataOutputStream(new BufferedOutputStream(socket.getOutputStream()));
				DataInputStream din = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
				
				BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));

				
				PrintWriter pw = new PrintWriter(socket.getOutputStream());
				

        String n = br.readLine();
				//System.out.println(n); <--- READY message
				
				if (args[2].equals("+")) {
					b[0] = 1;
				}
				if (args[2].equals("-")) {
					b[0] = 2;
				}
				if (args[2].equals("*")) {
					b[0] = 4;
				}

				b[1] = (byte)ints;
				
				int j = 2;
				
				for (int i = 0; i < ints; i += 2) {
					int y = 0;
					if ((i + 4) < args.length) {	
						y = Integer.parseInt(args[i + 4]);
					}
					int x = Integer.parseInt(args[i + 3]);
					b[j] = (byte)((x << 4) | y);
					j += 1;
				}

				os.write(b);
				os.flush();

				int answer = din.readInt();

				System.out.println(answer);
				
        socket.close();

    }

}