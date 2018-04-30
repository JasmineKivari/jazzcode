import java.lang.Character;
import java.util.Scanner;
import java.io.*;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.util.ArrayList;
import java.util.List;


public class finalcipher {

	public static int charToInt(char l) {
		return (int)l;
	}

	public static char intToChar(int i) {
		return (char)i;
	}

	public static boolean isAlpha(char c) {
		return true;
	}

  public static String encrypt(String text, String key) {
        String res = "";
        text = text.toUpperCase();
        for (int i = 0, j = 0; i < text.length(); i++) {
            char c = text.charAt(i);
            if (c < 'A' || c > 'Z') continue;
            res += (char)((c + key.charAt(j) - 2 * 'A') % 26 + 'A');
            j = ++j % key.length();
        }
        return res;
    }
	
	public static String decrypt(String text, String key) {	
			String res = "";
			text = text.toUpperCase();
			for (int i = 0, j = 0; i < text.length(); i++) {
					char c = text.charAt(i);
					if (c < 'A' || c > 'Z') continue;
					res += (char)((c - key.charAt(j) + 26) % 26 + 'A');
					j = ++j % key.length();
			}
			return res;
	}
		

  public static void main(String[] args)throws IOException {

    System.out.println("\nChoose from these choices");
		System.out.println("-------------------------\n");
		System.out.println("1 - Vigenere encryption");
		System.out.println("2 - Vigenere decryption");
		System.out.println("3 - Vigenere cryptanalysis");
		System.out.println("4 - Quit\n");
		
		String key_choice = "";
		String message_choice = "";
		String ciphertext = "";
		String deciphertext = "";
		String enc = "";
		String ioc = "";
		double index;
		int calcKey;
		boolean blue = true;
		
		System.out.print("\nChoice: ");
		
		while (blue) {
		
			Scanner scanner = new Scanner(System.in);
			int choice = scanner.nextInt();
			
			if (choice == 1){
				// Perform "Enter key/encrypt" case.
				System.out.print("Key to be used: ");
				key_choice = scanner.next();
				key_choice += scanner.nextLine();	
				System.out.print("Enter file to encrypt: ");
				message_choice = scanner.next();
				message_choice += scanner.nextLine();

				try {
					InputStream in = new FileInputStream(message_choice);
					FileWriter fw = new FileWriter("output.txt");
					BufferedReader buf = new BufferedReader(new InputStreamReader(in));
					BufferedWriter bw = new BufferedWriter(fw);
					String line = buf.readLine();
					StringBuilder sb = new StringBuilder();
					while(line != null){ 
						sb.append(line).append("\n");
						line = buf.readLine();		
					}
					String file_string = sb.toString();
					enc = encrypt(file_string, key_choice.toUpperCase());
					bw.write(enc);
					bw.close();
					System.out.println("Text encrypted!");
				}
				catch (IOException e) {
					System.out.println(e);
				}
			}
			
			else if (choice == 2){
				// Perform "decrypt" case.
				System.out.print("Decrypted: copy of file sent to file output.txt. (Enter output.txt as file for cryptanalysis)");

			}
			else if (choice == 3){
				// Perform "Cryptanalysis" case.
				try {
					System.out.print("Enter file to find key length (output.txt): ");
					String cryptedText = scanner.next();
					cryptedText += scanner.nextLine(); 
					int[] coincidences = new int[20];
					BufferedReader br = new BufferedReader(new FileReader(cryptedText));
					String original_text = "";
					String cipherString = "";
					boolean happy = true;
					while ((cipherString = br.readLine()) != null){
						if (happy == true){
							original_text = original_text + cipherString;
							happy = false;
						}
						else {
						original_text = original_text + " " + cipherString;
						}
					}
					String shifted_string = original_text;
					for (int crypt_index = 1; crypt_index <= coincidences.length; crypt_index++){
						int coincidence = 0;
						shifted_string = shifted_string.substring(1);
						for(int i = 0; i < shifted_string.length(); i++ ){
							if (original_text.charAt(i) == shifted_string.charAt(i) ){
								coincidence++;
							}
						}
						coincidences[crypt_index-1] = coincidence;
					}
					int max = coincidences[0];
					int coincidence_index = 0;
					for (int i = 1; i < coincidences.length; i++){
						if (coincidences[i] > max){
							max = coincidences[i];
							coincidence_index = i;
						}
					}
					System.out.println("Estimated key length: " + (coincidence_index + 1));							
				}		
			catch (IOException e) {
				System.out.println(e);
			}
		}
			
			else if (choice == 4){
				System.out.println("\nGoodbye!");
				System.exit(0);
			}
			else
			System.out.println("\nINVALID CHOICE!");
			System.out.print("\nChoice: ");
			}
	}	    
}