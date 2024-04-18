// to compile/run:
//   javac Input.java
//   java Input
//
// Will create file 'Input.class'

import java.util.Scanner;

public class Input {
   
    public static void main (String [] args) {
        int num;
        Scanner s = new Scanner(System.in);
        System.out.print("enter an integer: ");
        num = s.nextInt();
        System.out.print("value entered: ");
        System.out.println(num);
    }

}

/*
.method public static main([Ljava/lang/String;)V
    .limit stack 3
    .limit locals 3
.line 13
    new java/util/Scanner
    dup
    getstatic java/lang/System/in Ljava/io/InputStream;
    invokespecial java/util/Scanner/<init>(Ljava/io/InputStream;)V
    astore_2
.line 14
    getstatic java/lang/System/out Ljava/io/PrintStream;
    ldc "enter an integer: "
    invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
.line 15
    aload_2
    invokevirtual java/util/Scanner/nextInt()I
    istore_1
.line 16
    getstatic java/lang/System/out Ljava/io/PrintStream;
    ldc "value entered: "
    invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
.line 17
    getstatic java/lang/System/out Ljava/io/PrintStream;
    iload_1
    invokevirtual java/io/PrintStream/println(I)V
.line 18
    return
.end method
*/
