package ics200.lab5;

import java.io.*;
import java.net.*;
import java.lang.*;
import java.util.*;

public class ClientA {

    public static void main(String[] args) throws IOException {

        int interGer = (args.length - 3);
        String serv = args[0];
        byte[] bitey = new byte[(byte)(Math.ceil(interGer / 2.0) + 2)];
        int port = Integer.parseInt(args[1]);
        Socket socketto;
        socketto = new Socket(serv, port);
        
        BufferedInputStream inn = new BufferedInputStream(socketto.getInputStream());
        BufferedOutputStream outs = new BufferedOutputStream(socketto.getOutputStream());
        byte [] bitey2 = new byte[1024];
        int n = inn.read(bitey2);
				
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
				byte[] delivery = new byte[4];
				inn.read(delivery);
				int result = ((delivery[0] << 24) | ((delivery[1] & 0xff) << 16) | ((delivery[2] & 0xff) << 8) | ((delivery[3] & 0xff)));

				System.out.println(result);
				
        socketto.close();

    }

}