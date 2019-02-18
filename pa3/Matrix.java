//Rami Alrwais
//CS 101
//ID #1403536
//PA3
//Matrix.java

public class Matrix{
  List rows[] = null;
  int matrixSize = 0;
  int nnz;
  private class Entry{

    double value;
    int column;

    Entry(int column, double value){
      this.value = value;
      this.column = column;
    }
    public String toString(){
      StringBuffer theBuffer = new StringBuffer();
      theBuffer.append("(" + column +","+value+")");
      return theBuffer.toString();
    }
    public boolean equals(Object x){
      boolean eq = false;
      Entry thiss;
      if(x instanceof Entry){
        thiss = (Entry)x;
        eq = (this.value == thiss.value);

      }
      return eq;
    }

  }


  public Matrix(int n){
    if( n < 1 ) throw new RuntimeException("error");
    else{
      rows = new List[n];
      for(int i = 0; i < n; i++)
        rows[i] = new List();
      matrixSize = n;
    }
  }
  //Access functions
  // Returns n, the number of rows and columns of this Matrix
  int getSize(){
    return this.matrixSize;
  }
  // Returns the number of non-zero entries in this Matrix
  int getNNZ(){
    return this.nnz;
  }

  //overrides Object's equals() method
  public boolean equals(Object x){
    if (!(x instanceof Matrix)) return false;
    Matrix m = (Matrix) x;
    if(m.nnz != this.nnz){
      return false;
    }
    if(m.matrixSize != this.matrixSize){
      return false;
    }
    for(int i = 0; i<matrixSize; i++){
      if(!(m.rows[i].equals(rows[i]))){
        return false;
      }
    }
    return true;
  }
  //Manipulation procedures
  //sets this Matrix to Zero state.
  void makeZero(){
    nnz = 0;
    for(int i=0; i<this.matrixSize; i++){
      this.rows[i] = new List();
    }
  }
  //returns a new Matrix having the same entries as this Matrix
  Matrix copy() {
    Matrix newMatrix = new Matrix(matrixSize);
    for (int i = 0; i < matrixSize; i++) {
      if (!rows[i].isEmpty()) {
        rows[i].moveFront();
        while (rows[i].index() != -1) {
          Entry entry = (Entry)rows[i].get();
          newMatrix.changeEntry(i + 1, entry.column, entry.value);
          rows[i].moveNext();
        }
      }
    }
    return newMatrix;
  } 
  //// changes ith row, jth column of this Matrix to x
  // pre: 1<=i<=getSize(), 1<=j<=getSize()
  void changeEntry(int i, int j, double value){
    if(i < 1 || i > getSize() || j < 1 || j > getSize())
      throw new RuntimeException("Matrix error: changeEntry() =  invalid arguments(i,j)=(" + i + "," + j + ")");
    List L = rows[i-1];
    if (L.isEmpty()) {
      if (value != 0) {
        //  System.out.println("Case1");
        Entry W = new Entry(j, value);
        L.append(W);
        nnz++;
      }
    } else {
      L.moveFront();
      Entry E = (Entry) L.get();
      int k = E.column;
      while(L.index() != -1){
        E = (Entry) L.get();
        k = E.column;
        if (j <= k) break;
        L.moveNext();
      }
      if (L.index() == -1) {
        //System.out.println("Case2");
        if (value != 0) {
          L.append(new Entry(j, value));
          nnz++;
        }
      }
      else if (j < k && value != 0)
      {
        //System.out.println("Case3");
        L.insertBefore(new Entry(j, value));
        nnz++;
      }
      //        Entry temp = (Entry)rows[i - 1].get();
      else {
        if (value == 0) {
          //System.out.println("ChangeEntry is deleting a node");
          L.delete();
          nnz--;
        } else {
          //System.out.println("Case4");
          E.value = value;
        }
      }
    }
  }
  //returns a new Matrix that is the scalar product of this Matrix
  Matrix scalarMult(double x){
    int newMatrixSize = this.getSize();
    Matrix newM = new Matrix(newMatrixSize);
    for(int i = 1; i <= newMatrixSize; i++){
      List itRow = rows[i - 1];
      itRow.moveFront();
      while(itRow.index() != -1){
        Entry c = (Entry)itRow.get();
        newM.changeEntry(i, c.column, (x*c.value));
        itRow.moveNext();
      }
    }

    return newM;
  }

  // returns a new Matrix that is the sum of this Matrix with M
  // pre: getSize()==M.getSize()
  Matrix add(Matrix M) {
    if(getSize() != M.getSize()) {
      throw new RuntimeException("Matrix Error: Matrices not same size");
    }
    if (M.equals(this)) return M.scalarMult(2);
    int c = 0, e2 = 0;
    double v1 = 0, v2 = 0;
    List temp1, temp2;
    Matrix addM = new Matrix(getSize());
    for(int i = 1; i <= rows.length; i++) {
      temp1 = M.rows[i-1];
      temp2 = this.rows[i-1];
      if(temp1.isEmpty() && !temp2.isEmpty()) {
        temp2.moveFront();
        while(temp2.index() != -1) {
          addM.changeEntry(i, ((Entry)temp2.get()).column, ((Entry)temp2.get()).value);
          temp2.moveNext();
        }
      }else if(!temp1.isEmpty() && temp2.isEmpty()) {
        temp1.moveFront();
        while(temp1.index() != -1) {
          addM.changeEntry(i, ((Entry)temp1.get()).column, ((Entry)temp1.get()).value);
          temp1.moveNext();
        }
      }else if(!temp1.isEmpty() && !temp2.isEmpty()) {
        temp2.moveFront();
        temp1.moveFront();
        while(temp1.index() != -1 && temp2.index() != -1) {
          if(((Entry)temp1.get()).column == ((Entry)temp2.get()).column) {
            v1 = ((Entry)temp1.get()).value;
            v2 = ((Entry)temp2.get()).value;
            c = ((Entry)temp2.get()).column;
            addM.changeEntry(i, c, (v1+v2));
            temp1.moveNext();
            if(!this.equals(M))
              temp2.moveNext();
            ///if temp1 < temp2
            //this < M
          }else if(((Entry)temp1.get()).column < ((Entry)temp2.get()).column) {
            v1 = ((Entry)temp1.get()).value;
            c = ((Entry)temp1.get()).column;
            addM.changeEntry(i, c, v1);
            temp1.moveNext();
            //if temp1>temp2
          }else if(((Entry)temp1.get()).column > ((Entry)temp2.get()).column) {
            v2 = ((Entry)temp2.get()).value;
            c = ((Entry)temp2.get()).column;
            addM.changeEntry(i, c, v2);
            temp2.moveNext();
          }
        }
        while(temp1.index() != -1) {
          addM.changeEntry( i, ((Entry)temp1.get()).column, ((Entry)temp1.get()).value);
          temp1.moveNext();
        }
        while(temp2.index() != -1) {
          addM.changeEntry(i, ((Entry)temp2.get()).column, ((Entry)temp2.get()).value);
          temp2.moveNext();
        }
      }
    }
    return addM;
  }

  //returns a new Matrix that is the difference of the Matrix with M
  //pre: getSize() ==M.getSize()
  Matrix sub(Matrix M){
    if(getSize() != M.getSize()) {
      throw new RuntimeException("Matrix Error: Matrices must be the same size");
    }
    //add the negative
    Matrix Y = new Matrix(getSize());
    M = (M.scalarMult(-1));
    Y = (this.add(M));
    return Y;
  }
  //returns a new Matrix that is the transpose of this Matrix
  Matrix transpose(){
    int newMatrixSize = this.getSize();
    Matrix newM = new Matrix(newMatrixSize);
    for(int i = 1; i <= newMatrixSize; i++){
      List itRow = rows[i - 1];
      // if(!itRow[i].isEmpty()){
      itRow.moveFront();
      //  itRow[i].moveFront();
      while(itRow.index() != -1){
        Entry c = (Entry)itRow.get();
        newM.changeEntry(c.column, i, c.value);
        itRow.moveNext();
      }
    }
    return newM;
  }
  //returns a new Matrix that is the product of this Matrix with M
  Matrix mult(Matrix M){
    if(this.getSize() != M.getSize()){
      throw new RuntimeException("Matrix");

    } 
    int newMatrixSize = this.getSize();
    Matrix newM = M.transpose();
    Matrix resultMatrix = new Matrix(newMatrixSize);
    double resultMatrix_Entry = 0;
    for(int i = 1; i <= newMatrixSize; i++){
      for(int j = 1; j<= newMatrixSize; j++){
        List itRow_A = this.rows[i - 1];
        List itRow_B = newM.rows[j-1];
        itRow_A.moveFront();
        itRow_B.moveFront();
        while((itRow_A.index() != -1) && (itRow_B.index() != -1)){
          Entry c_A = (Entry)itRow_A.get();
          Entry c_B = (Entry) itRow_B.get();
          if(c_A.column == c_B.column){
            resultMatrix_Entry += (c_A.value)*(c_B.value);
            itRow_A.moveNext();
            itRow_B.moveNext();

          } else if(c_A.column > c_B.column){
            itRow_B.moveNext();

          }else{
            itRow_A.moveNext();
          }

        }
        resultMatrix.changeEntry(i, j, resultMatrix_Entry);
        resultMatrix_Entry = 0;
      }
    }
    return resultMatrix;

  }
  //overrides Object's toString() method
  public String toString(){
    StringBuffer returnString = new StringBuffer();
    for(int i = 0; i < this.matrixSize; i++){
      if(rows[i].length() != 0){
        returnString.append((i+1) + ":" + rows[i]+ "\n");
      }
    }
    return returnString.toString();
  }
}

