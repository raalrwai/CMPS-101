//Rami ALrwais
//CS 101
//PA3
//Sparse.java
//Handles Matrix adt to perform special operations
import java.io.*;
import java.util.Scanner;
public class Sparse{
public static void main(String[] args) throws IOException{
  if(args.length != 2){
    System.err.println("Usage: FileIO infile Outfile");
    System.exit(1);

  }
  Scanner in;
  PrintWriter out;
  int lineNumber  = 0;
  String Line = null;


  in = new Scanner(new File(args[0]));
  out = new PrintWriter(new FileWriter(args[1]));
  String[] parts = null;
  
  if(in.hasNextLine()){
    parts = in.nextLine().split(" ");
  }

  Matrix a = new Matrix(Integer.parseInt(parts[0]));
  Matrix b = new Matrix(Integer.parseInt(parts[0]));
  int a_ent = Integer.parseInt(parts[1]);
  int b_ent = Integer.parseInt(parts[2]);



 in.nextLine();
 for(int i = 0; i < a_ent; i++){
 parts = in.nextLine().split(" ");
  a.changeEntry(Integer.parseInt(parts[0]), Integer.parseInt(parts[1]), Double.parseDouble(parts[2]));
}
in.nextLine();
for(int i = 0; i < b_ent; i++){
  parts = in.nextLine().split(" ");
  b.changeEntry(Integer.parseInt(parts[0]), Integer.parseInt(parts[1]), Double.parseDouble(parts[2]));
}



        out.println("A has " + a.getNNZ() + " non-zero entries:");
        out.println(a);

        out.println("B has " + b.getNNZ() + " non-zero entries:");
        out.println(b);

        out.println("(1.5)*A =");
        out.println(a.scalarMult(1.5));

        out.println("A+B =");
        out.println(a.add(b));

        out.println("A+A =");
        out.println(a.add(a));

        out.println("B-A =");
        out.println(b.sub(a));

        out.println("A-A =");
        out.println(a.sub(a));

        out.println("Transpose(A) =");
        out.println(a.transpose());

        out.println("A*B =");
        out.println(a.mult(b));

        out.println("B*B =");
        out.println(b.mult(b));

        in.close();
        out.close();
    }
}

















