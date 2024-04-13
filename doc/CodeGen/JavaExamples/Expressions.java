// to compile/run:
//   javac Expressions.java
//   java Expressions
//
// Will create file 'Expressions.class'

import java.util.Scanner;

public class Expressions {
   
    public static void main (String [] args) {
        int x = 3, y = 2;
        System.out.print("x + y --> ");  System.out.println(x+y);
        System.out.print("x * y --> ");  System.out.println(x*y);
        System.out.print("x % y --> ");  System.out.println(x%y);
    }

}

/*
.method public static main([Ljava/lang/String;)V
    .limit stack 3
    .limit locals 3
.line 12
    //push the constant value 3 onto the stack 
    iconst_3
    //store into the first register
    istore_1
    //push the constant value 2 onto the stack 
    iconst_2
    //store 2 into the second register
    istore_2

.line 13
    //function for printing (in place of System.out.print) 
    getstatic java/lang/System/out Ljava/io/PrintStream;
    //load the string 
    ldc "x + y --> "
    //finish the print function 
    invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
    //start another print statement
    getstatic java/lang/System/out Ljava/io/PrintStream; 
    //push constant onto the stack 
    iload_1
    iload_2
    iadd
    invokevirtual java/io/PrintStream/println(I)V
.line 14
    getstatic java/lang/System/out Ljava/io/PrintStream;
    ldc "x * y --> "
    invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
    getstatic java/lang/System/out Ljava/io/PrintStream;
    iload_1
    iload_2
    imul
    invokevirtual java/io/PrintStream/println(I)V
.line 15
    getstatic java/lang/System/out Ljava/io/PrintStream;
    ldc "x % y --> "
    invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
    getstatic java/lang/System/out Ljava/io/PrintStream;
    iload_1
    iload_2
    irem
    invokevirtual java/io/PrintStream/println(I)V
.line 16
    return
.end method
*/
