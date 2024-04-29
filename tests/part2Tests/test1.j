.class  public test1
.super  java/lang/Object
.method public static main([Ljava/lang/String;)V
.limit stack 1000
.limit locals 3
bipush 5
istore_1
getstatic java/lang/System/out Ljava/io/PrintStream;
ldc "x<9ãR = "
invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
getstatic java/lang/System/out Ljava/io/PrintStream;
iload_1
invokevirtual java/io/PrintStream/print(I)V
getstatic java/lang/System/out Ljava/io/PrintStream;
ldc "
"
invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
return
.end method