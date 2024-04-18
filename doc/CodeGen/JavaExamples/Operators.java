// to compile/run:
//   javac IfElse.java
//   java IfElse
//
// Will create file 'IfElse.class'

public class Operators {
   
    public static void main (String [] args) {
        int i = 1000; 
        int j = 10;
        if((i < j) || (j < i))
            System.out.println("if1");
        if((i < j) && (j < i))
            System.out.println("if2");
        if(i <= 100)
            System.out.println("if3");
        if(i < 100)
            System.out.println("if4");
        if(i > 100)
            System.out.println("if5");
        if(i >= 100)
            System.out.println("if6");
        if(i != 100)
            System.out.println("if7");
        if(!(i==100))
            System.out.println("if8");
    }

}

/*
.method public <init>()V
    .limit stack 1
    .limit locals 1
.line 7
    aload_0
    invokespecial java/lang/Object/<init>()V
    return
.end method

; >> METHOD 2 <<
.method public static main([Ljava/lang/String;)V
    .limit stack 2
    .limit locals 2
.line 10
    sipush 1000
    istore_1
.line 11
    iload_1
    bipush 100
    if_icmple Label1
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
.end method
*/
