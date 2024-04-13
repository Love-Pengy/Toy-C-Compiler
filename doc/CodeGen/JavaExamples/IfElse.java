// to compile/run:
//   javac IfElse.java
//   java IfElse
//
// Will create file 'IfElse.class'

public class IfElse {
   
    public static void main (String [] args) {
	int i = 10;
	if(i > 0)
	    System.out.println("greater than 0");
	else
	    System.out.println("less than or equal to 0");
    }
   
}

/*
; >> METHOD 2 <<
.method public static main([Ljava/lang/String;)V
    .limit stack 2
    .limit locals 2
.line 10
    bipush 10
    istore_1
.line 11
    iload_1
    ifle Label1
.line 12
    getstatic java/lang/System/out Ljava/io/PrintStream;
    ldc "greater than 0"
    invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
    goto Label2
.line 14
Label1:
    getstatic java/lang/System/out Ljava/io/PrintStream;
    ldc "less than or equal to 0"
    invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
.line 15
Label2:
    return 
*/
