//package ics200.lab5;

import java.io.*;
import java.net.*;
import java.lang.*;
import java.util.*;

public class ClientA {

    public static void main(String[] args) throws IOException {

        int ints = (args.length - 3);
        String server = args[0];
        byte[] b = new byte[(byte)(Math.ceil(ints / 2.0) + 2)];
        int port = Integer.parseInt(args[1]);
        Socket socket;
        socket = new Socket(server, port);
        
        BufferedInputStream is = new BufferedInputStream(socket.getInputStream());
        BufferedOutputStream os = new BufferedOutputStream(socket.getOutputStream());
        byte [] b1 = new byte[1024];
        int n = is.read(b1);
				
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
				byte[] incoming = new byte[4];
				is.read(incoming);
				int result = ((incoming[0] << 24) | ((incoming[1] & 0xff) << 16) | ((incoming[2] & 0xff) << 8) | ((incoming[3] & 0xff)));

				System.out.println(result);
				
        socket.close();

    }

}