// to compile/run:
//   javac Output.java
//   java Output
//
// Will create file 'Output.class'

import java.util.Scanner;

public class Output {
   
    public static void main (String [] args) {
	char ch = 'A';	
	String str = "hi mom";
	int x = 1000;
	System.out.print("ch --> ");  System.out.println(ch);
	System.out.print("str --> "); System.out.println(str);
	System.out.print("x --> ");   System.out.println(x);
    }

}


/*
.method public static main([Ljava/lang/String;)V
    .limit stack 2
    .limit locals 4
.line 12
    bipush 65
    istore_1
.line 13
    ldc "hi mom"
    astore_2
.line 14
    sipush 1000
    istore_3
.line 15
    getstatic java/lang/System/out Ljava/io/PrintStream;
    ldc "ch --> "
    invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
    getstatic java/lang/System/out Ljava/io/PrintStream;
    iload_1
    invokevirtual java/io/PrintStream/println(C)V
.line 16
    getstatic java/lang/System/out Ljava/io/PrintStream;
    ldc "str --> "
    invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
    getstatic java/lang/System/out Ljava/io/PrintStream;
    aload_2
    invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
.line 17
    getstatic java/lang/System/out Ljava/io/PrintStream;
    ldc "x --> "
    invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
    getstatic java/lang/System/out Ljava/io/PrintStream;
    iload_3
    invokevirtual java/io/PrintStream/println(I)V
.line 18
    return
.end method
*/
