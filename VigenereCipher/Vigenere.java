import java.io.*;
import java.lang.Character;
import java.util.Scanner;
import java.util.ArrayList;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.util.List;

public class Vigenere {
    
    public static int charToInt(char l){
        return (int)l;
    }

    public static char intToChar(int i) {
        return (char)i;
    }
    public static boolean isAlpha(char c) {
        return true;
    }
  public static String encrypt(String word, String Key) {
        String encrypt_it = "";
        word = word.toUpperCase();
        for (int i = 0, k = 0; i < word.length(); i ++) {
            char c = word.charAt(i);
            if (c < 'A'|| c > 'Z') continue;
            encrypt_it += (char)((c + Key.charAt(k) - 2 * 'A') % 26 + 'A');
            k = ++k % Key.length();
        }
        return encrypt_it;
  }
    
    public static String decrypt(String word, String Key) {
        String decrypt_it = "";
        word = word.toUpperCase();
        for (int i = 0, k = 0; i < word.length(); i ++) {
            char c = word.charAt(i);
            if (c < 'A' || c > 'Z') continue;
            decrypt_it += (char)(( c - Key.charAt(k) + 26) % 26 + 'A');
            k = ++k % Key.length();
        }
        return decrypt_it;
    }
  
  public static void main(String[] args)throws IOException {
    System.out.println("\n*****WELCOME***********"); 
    System.out.println("***********************");
    System.out.println("\nPlease Choose an Option");
        System.out.println("***********************\n");
        System.out.println("1. -> Vignere Encryption");
        System.out.println("2. -> Vigenere Decryption");
        System.out.println("3. -> Vigenere cryptanalysis");
        System.out.println("4. -> Quit");
            
        String optionofchoice = "";
        String user_message = "";
        String ciphermessage = "";
        String deciphermessage = "";
        String encif = "";
        String indexofc = "";
        double ind;
        int calulatethekey;
        boolean red = true;
        
        System.out.println("\nWhat is your Option?: ");
        
        while (red) {
            
            Scanner scanner = new Scanner(System.in);
            int option = scanner.nextInt();
            
            if (option == 1) {
                System.out.print("Please input your key: ");
                optionofchoice = scanner.next();
                optionofchoice += scanner.nextLine();
                System.out.print("Please enter the name of the file to encrypt (with .txt at the end): ");
                user_message = scanner.next();
                user_message += scanner.nextLine();
                
                try {
                    InputStream instream = new FileInputStream(user_message);
                    FileWriter fwriter= new FileWriter("output.txt");
                    BufferedReader bufreed = new BufferedReader(new InputStreamReader(instream));
                    BufferedWriter bufwrite = new BufferedWriter(fwriter);
                    String thisline = bufreed.readLine(); 
                    StringBuilder sbuild = new StringBuilder();
                    while(thisline != null) {
                        sbuild.append(thisline).append("\n");
                        thisline = bufreed.readLine();
                    }
                    String string_in_file = sbuild.toString();
                    encif = encrypt(string_in_file, optionofchoice.toUpperCase());
                    bufwrite.write(encif);
                    bufwrite.close();
                    System.out.println("Your text has been encrypted.");
                }
                catch (IOException e) {
                    System.out.println(e);
                }
            }
            else if (option == 2) {
                System.out.println("Text decrypted and sent to output.txt!");
                System.out.println("Please open file named output.txt to view cryptanalysis");
            }
            else if (option == 3) {
                try{
                    System.out.print("Enter file to find key length (output.txt): ");
                    String encriptedtext = scanner.next();
                    encriptedtext += scanner.nextLine();
                    int[] indecofcoin = new int[20];
                    BufferedReader reader = new BufferedReader(new FileReader(encriptedtext));
                    String regular_text = "";
                    String enciphered_string = "";
                    boolean itworks = true;
                    while ((enciphered_string = reader.readLine()) != null) {
                        if (itworks == true) {
                            regular_text = regular_text + enciphered_string;
                            itworks = false;
                    }
                    else {
                    regular_text = regular_text + " " + enciphered_string;
                    }
                }
                    String shift = regular_text;
                    for (int cryptdex = 1; cryptdex <= indecofcoin.length; cryptdex++) {
                        int indecofcoin2 = 0;
                        shift = shift.substring(1);
                        for(int z = 0; z < shift.length(); z ++) {
                            if(regular_text.charAt(z) == shift.charAt(z)) {
                                indecofcoin2++;
                            }
                        }
                        indecofcoin[cryptdex-1] = indecofcoin2;
                    }
                    int maximum = indecofcoin[0];
                    int indexWithCoin = 0;
                    for (int i = 1; i < indecofcoin.length; i++) {
                        if (indecofcoin[i] > maximum) {
                            maximum = indecofcoin[i];
                            indexWithCoin = i;
                        }
                    }
                    System.out.println("The key length is: " + (indexWithCoin + 1));
                }
            catch (IOException e) {
                System.out.println(e);
            }
        }
            else if (option == 4) {
                System.out.println("\nThank you, Goodbye");
                System.exit(0);
            }
            else
                System.out.println("\nI'm Sorry that is an not a valid choice!");
                System.out.print("\nPlease choose a different option: ");
            }
     }
}