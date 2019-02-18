//Rami Alrwis
//Cs 101
//pa3
//List.java
//student id#1403536
//List client for Matrix.java
class List{

  private class Node{
    // Fields
    Object entry;
    // Node nexti;
    Node prev, next;

    // Constructor
    Node(Object entry) { this.entry = entry;
      prev = next = null; }

    //toString();  overrides Object's toString() method
    public String toString(){
      return entry.toString();
    }
    public boolean equals(Object x){
      boolean equal = false;
      Node node;
      if(x instanceof Node){
        node = (Node)x;
        equal = (this.entry.equals(node.entry));
      }
      return equal;
    }
  }

  // Fields
  private Node front;
  private Node back;
  private int length;
  private Node current;
  private int index; 
  // Constructor
  List(){ 
    front = back = current = null; 
    length = 0;
    index = -1;
  }

  // Access Funtions -----------------------------------------------------
  // getLength()
  // Returns length of this Queue.
  int length() { 
    return length; 
  } //Boolean which returns length to 0
  boolean isEmpty(){
    return (length==0);
  }
  //If cursor is defined, returns the index of the cursor element, otherwise
  //returns -1
  int index(){
    return index;
  }

  // getFront() 
  // Returns front element.
  // Pre: !this.islEmpty()
  Object front(){
    if(length() !=0){
      return front.entry;
    }else{
      throw new RuntimeException("Error: getFront() called on emptly List");
    }
  }
  //int getBack()
  //returns back element.
  // Pre: length != 0 
  Object back(){
    if(length() !=0){
      return back.entry;
    } else{
      throw new RuntimeException("Error: getBack() called on empty List");
    }
  } 
  //int get()
  //returns current element
  //pre: lenght != 0
  Object get(){
    if(length()<=0)
      throw new RuntimeException("Error: get() called on an empty list.");
    if(current==null)
      throw new RuntimeException("Error: get() icalled on undefined cursor");
    return current.entry;
  }


  public boolean equals (Object x){
    boolean eq = false;
    List L;
    Node N, M;

    if(x instanceof List){
      L = (List)x;
      eq = (this.length == L.length);
      N = this.front;
      M = L.front;

      while(eq && N!=null)
      {
        eq = (N.equals(M));
        N = N.next;
        M = M.next;
      }
    }

    return eq;
  }
  // Manipulation Procedures -------------------------------------------------
  //clears List
  void clear(){
    front = back = current = null;
    length = 0;
    index = -1;
  }
  //  void moveFront(){
  void moveFront(){
    if(length()>0){
      current = front;
      index = 0;  
    }
  }
  //void moveBack()
  // pre: list must not be empty
  // moves current to  back
  void moveBack(){
    if(length()==0){
      throw new RuntimeException("Error: moveBack() called on an empty list");
    } else{
      current = back;
      index = length-1;
    }
  }
  //void movePrev()
  //pre: list must not be empty
  //moves current one element back
  void movePrev(){
    if(this.isEmpty()){
      throw new RuntimeException("Error: movePrev() called on an empty list.");
    }else{
      index--;
      current = current.prev;
    }
  } 
  //void moveNext()i
  //pre: list must not be empty
  //moves current one element next

  void moveNext(){
    if(this.isEmpty()){
      throw new RuntimeException("Error: moveNexxt() called on an empty list");
    }else if(index()== length()-1){
      index = -1;
      current = null;
    }else{
      current = current.next;
      index++;
    }
  }
  //void prepend()
  //pre: list must not be empty
  //insert new element into front of list
  void prepend(Object entry){
    Node tmp = new Node(entry);
    if(length()==0){
      front = back = tmp;
    }else{
      tmp.next = front;
      front.prev = tmp;
      front = tmp;
      if(current != null) index +=1;
    }
    length++;
  } 
  //void append()
  //pre: list must not be empty
  //insert new element at back of list
  void append(Object entry){
    Node tmp = new Node(entry);
    if(length()==0){
      front = back = tmp;
    }else{
      tmp.prev = back;
      back.next = tmp;
      back = tmp;
    }
    length++;
  }
  //void insertBefore()
  //pre: index must be defined, list must not be empty
  //inserts new element before current one
  void insertBefore(Object entry){
    if(this.isEmpty()){
      throw new RuntimeException("Error: insertBefore() called on an empty list");
    }
    if(index()<0){
      throw new RuntimeException("Error: insertBefore() cursor not defined");
    }
    if(index()==0){
      prepend(entry);
    }else{
      Node tmp = new Node(entry);

      current.prev.next = tmp;;
      tmp.prev = current.prev;
      current.prev = tmp;
      tmp.next = current;
      index += 1;
      length += 1;
    }
  }
  //void insertAfter
  //pre: list must not be empty, index must be defined
  //inserts new element after current elent
  void insertAfter(Object entry){
    if(this.isEmpty()){
      throw new RuntimeException("Error: insertAfter() called on an empty list.");
    } if(index()<0){
      throw new RuntimeException("Error: insertAfter() called on undefined cursor.");
    }if(index()==length()-1){
      append(entry);
    }else{
      Node tmp = new Node(entry); 
      tmp.next = current.next;
      current.next.prev = tmp;
      tmp.prev = current;
      current.next = tmp;
      length+=1;
    }
  }
  //void deleteBack()
  //list must not be empty
  //deleted back element
  void deleteBack(){
    if(length == 0) {
      throw new RuntimeException("Error: deleteBack() called on an empty list");
    }
    if( length ==1){
      clear();
      return;
    }else{
      if(index == length-1){
        index = -1;
        current = null;
      }
      Node N = back;
      back = back.prev;
      back.next = null;
      N.prev = null;
    }
    length-=1;
  }
  //void deleteFront()
  //pre: list must be not empty
  //deletes element in front of current
  void deleteFront(){
    if(this.isEmpty()){
      throw new RuntimeException("Error: deleteFront() called on an empty list");
    }
    if(length==1){
      clear();
      return;
    }else{
      if(index==0){
        current = null;
        index = -1;
      }
      Node N = front;
      front = front.next;
      front.prev = null;
      N.next = null;
    }

    length -=1;
    if(index > 0) index--;
  }
  //void delete()
  //deleted current element
  //pre: index must be defined, list must not be empty
  void delete(){ 
    if(index<0){
      throw new RuntimeException("Error: deleteCurrent() called on undefined cursor");
    } if(length < 1){ 
      throw new RuntimeException("Error: deleteCurrent() called on empty list");
    }
    if(index == 0)
      deleteFront();
    else if(index == length-1){
      deleteBack();
    }
    else
    {
      current.next.prev = current.prev;
      current.prev.next = current.next;
      current.next = null;  
      current.prev = null;
      current = null;
      index = -1;
      length--;
    }
  } 


  // Other Functions ---------------------------------------------------------

  // toString()
  // Overides Object's toString() method.
  public String toString(){
    StringBuffer sb = new StringBuffer();
    Node N = front;
    while(N!=null){
      sb.append(" ");
      sb.append(N.toString());
      N = N.next;
    }
    return sb.toString();
  }



  // copy()
  // Returns a new Queue identical to this Queue.
  List copy(){
    List Q = new List();
    Node N = this.front;

    while( N!=null ){

      Q.append(N.entry);
      N = N.next;
    }
    return Q;
  }

}
