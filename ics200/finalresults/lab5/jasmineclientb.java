package ics200.lab5;

import java.io.*;
import java.net.*;
import java.lang.*;
import java.util.*;

public class jasmineclientb {

    public static void main(String[] args) throws IOException {

        int interGer = (args.length - 3);
        String server = args[0];
        
        byte[] bitey = new byte[(byte)(Math.ceil(interGer / 2.0) + 2)];
        int port = Integer.parseInt(args[1]);
        
        Socket socket;
        socket = new Socket(server, port);
        
        BufferedInputStream inn = new BufferedInputStream(socket.getInputStream());
        BufferedOutputStream outs = new BufferedOutputStream(socket.getOutputStream());
        
                DataOutputStream dataout = new DataOutputStream(new BufferedOutputStream(socket.getOutputStream()));
                DataInputStream datain = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
        
                BufferedReader reeder = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                PrintWriter riter = new PrintWriter(socket.getOutputStream());
        
        
        
        String n = reeder.readLine();
				
				if (args[2].equals("+")) {
					bitey[0] = 1;
				}
				if (args[2].equals("-")) {
					bitey[0] = 2;
				}
				if (args[2].equals("*")) {
					bitey[0] = 4;
				}

				bitey[1] = (byte)interGer;
				
				int j = 2;
				
				for (int i = 0; i < interGer; i += 2) {
					int y = 0;
					if ((i + 4) < args.length) {	
						y = Integer.parseInt(args[i + 4]);
					}
					int x = Integer.parseInt(args[i + 3]);
					bitey[j] = (byte)((x << 4) | y);
					j += 1;
				}

				outs.write(bitey);
				outs.flush();
				
                
                int outcome = datain.readInt();
				
                
				System.out.println(outcome);
				
        socket.close();

    }

}