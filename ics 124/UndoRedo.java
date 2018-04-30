import java.util.Scanner;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Stack;

/**
 * Application to demonstrate the use of a stack by simulating an editor's un/redo operations.
 *
 * @author lynda
 */
public class UndoRedo {
    
    public static Scanner openFile(String fileName) throws IOException{
        Scanner fileStream;
        FileInputStream fileByteStream = new FileInputStream(fileName);
        return(new Scanner(fileByteStream));
    }
    
    public static void performOperation(String operation) {
          System.out.println("Operation: " + operation + " completed.");
    }
    
    public static void main(String[] args) throws Exception {
        String fileName;
        Scanner inputFileStream;
        
        Stack<String> doneStack = new Stack<String>();
        Stack<String> undoneStack = new Stack<String>();
        String operation;
        
        Scanner keyboard = new Scanner(System.in);
        System.out.print("Enter file name: ");
        inputFileStream = openFile(keyboard.nextLine());
        
        while (inputFileStream.hasNextLine()) {
            operation = inputFileStream.nextLine();
            System.out.println("Operation read from file is: " + operation);
            switch (operation) {
                case "typing" :
                case "auto format" :
                case "bold" :
                case "italic" :
                case "copy text" :
                    doneStack.push(operation);
                    performOperation(operation);
                    break;
                
                case "UNDO" :
                    if (doneStack.isEmpty())
                        System.out.println("x Cannot undo. Nothing to undo.");
                    else {
                        operation = (String) doneStack.pop();
                        performOperation(operation + " undone");
                        undoneStack.push(operation);
                    }
                    break;
                    
                case "REDO" :
                    if (undoneStack.isEmpty())
                        System.out.println("x Cannot redo. Nothing to redo.");
                    else {
                        operation = (String) undoneStack.pop();
                        performOperation(operation + " redone");
                        doneStack.push(operation);
                    }
                    break;
            }
            System.out.println();
        }
        
   inputFileStream.close();
   }
}
