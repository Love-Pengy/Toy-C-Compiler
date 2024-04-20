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
.method public static main([Ljava/lang/String;)V
    .limit stack 2
    .limit locals 3
.line 10
    sipush 1000
    istore_1
.line 11
    bipush 10
    istore_2
.line 12
    iload_1
    iload_2
    if_icmplt Label1
    iload_2
    iload_1
    if_icmpge Label2
.line 13
Label1:
    getstatic java/lang/System/out Ljava/io/PrintStream;
    ldc "if1"
    invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
.line 14
Label2:
    iload_1
    iload_2
    if_icmpge Label3
    iload_2
    iload_1
    if_icmpge Label3
.line 15
    getstatic java/lang/System/out Ljava/io/PrintStream;
    ldc "if2"
    invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
.line 16
Label3:
    iload_1
    bipush 100
    if_icmpgt Label4
.line 17
    getstatic java/lang/System/out Ljava/io/PrintStream;
    ldc "if3"
    invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
.line 18
Label4:
    iload_1
    bipush 100
    if_icmpge Label5
.line 19
    getstatic java/lang/System/out Ljava/io/PrintStream;
    ldc "if4"
    invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
.line 20
Label5:
    iload_1
    bipush 100
    if_icmple Label6
.line 21
    getstatic java/lang/System/out Ljava/io/PrintStream;
    ldc "if5"
    invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
.line 22
Label6:
    iload_1
    bipush 100
    if_icmplt Label7
.line 23
    getstatic java/lang/System/out Ljava/io/PrintStream;
    ldc "if6"
    invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
.line 24
Label7:
    iload_1
    bipush 100
    if_icmpeq Label8
.line 25
    getstatic java/lang/System/out Ljava/io/PrintStream;
    ldc "if7"
    invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
.line 26
Label8:
    iload_1
    bipush 100
    if_icmpeq Label9
.line 27
    getstatic java/lang/System/out Ljava/io/PrintStream;
    ldc "if8"
    invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
.line 28
Label9:
    return
.end method
*/
