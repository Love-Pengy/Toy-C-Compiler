# All relavent commands for code generation

+ bipush
    + pushes a value onto the stack 
+ istore_<register value>
    + loads the value at the top of the stack into memory 
    + I believe this also pops the value from the stack 
+ return    
    + signals the end of a function
+ .end method
    + signals the end of the class
+ getstatic java/lang/System/out Ljava/io/PrintStream 
    + the header with the new line would be the same
    + this is the start of the print function
+ invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
    + end of the print function
    + the end for a new line print would be invokebirtual java/io/PrintStream/println(I)V
+ ldc "<value>"
    + loads the value to the top of the stack 
+ iload_<register value> 
    + loads value from memory to the stack 
+ iadd  
    + adds the top two values on the stack 
+ imul  
    + multiplies the top two values on the stack 
+ irem 
    + computes the module of the top two values on the stack 

