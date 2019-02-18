//Rami ALrwais
//1403536
//Pa1
//Lex.java
//This program reads in an input file and write out the correct alphabetic
import java.io.*;
import java.util.Scanner;
public class Lex{
  public static void main(String[] args) throws IOException{
    if(args.length != 2){                                 
      System.err.println("Usage: FileIO infile Outfile");//prints error message for incorrect usage
      System.exit(1);
    }
    Scanner in;
    PrintWriter out;
    int lineNumber = 0;                                  
    String[] token = null;
    token = new String[lineNumber];
     
    in = new Scanner(new File(args[0]));
    out = new PrintWriter(new FileWriter(args[1]));

    while(in.hasNextLine()){
      lineNumber++;//counts number of lines
      in.nextLine();
    }

    in.close();
    String[] input = new String[lineNumber];
    in = new Scanner(new File(args[0]));
    int i = 0;
    while(in.hasNextLine()){
     input[i] = in.nextLine();
    i++; //stores values in array
    }
   List sort = new List();
    sort.append(0);
      //sorting method
    for(int j=1; i < lineNumber; i++){
    i = j-1; 
    String tmp = input[j];
    sort.moveBack();
    while(i >= 0 && tmp.compareTo(input[sort.get()])<= 0) {
    sort.movePrev();
    i--;
    } if(sort.index() >= 0) 
      sort.insertAfter(j);
    else sort.prepend(j);
    }
      
  for(i=0; i<lineNumber; i++){
    sort.moveFront();
    out.println(token[sort.get()]);
    sort.moveNext();
  } //closes files
    in.close();
    out.close();
  }
}
