// to compile/run:
//   javac WhileLoop.java
//   java WhileLoop
//
// Will create file 'WhileLoop.class'

public class WhileLoop {
   
    public static void main (String [] args) {
	int i = 1;
	while(i <= 5) {
	    System.out.println(i);
	    i = i + 1;
	}
    }
   
}

/*
.method public static main([Ljava/lang/String;)V
    .limit stack 2
    .limit locals 2
.line 10
    iconst_1
    istore_1
.line 11
Label1:
    iload_1
    iconst_5
    if_icmpgt Label2
.line 12
    getstatic java/lang/System/out Ljava/io/PrintStream;
    iload_1
    invokevirtual java/io/PrintStream/println(I)V
.line 13
    iload_1
    iconst_1
    iadd
    istore_1
    goto Label1
.line 15
Label2:
    return
.end method
*/
