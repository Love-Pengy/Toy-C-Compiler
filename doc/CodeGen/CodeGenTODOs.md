# Portions of the AST that must be considered
+ ToyCProgram
    + at the moment this does literally nothing in terms of the code gen 
+ Definition 
+ FunctionDefinition 
    + handled by functionHeader and the functionBody
+ FunctionHeader
    + function definition (main): ```.method public static main([Ljava/lang/String;)V```
        + for this the stack and locals also need to be determined
+ FunctionBody 
    + handled by helper functions

+ FormalParamList
    + function header cannot exist without functions (ask about this maybe?)
+ Statement
    + handled in helper functions

+ IfStatement
```
    check condition with command (example ifle) 
    go to respective label if condition is hit or other one if else statement exists
```
+ NullStatement

+ ReturnStatement
+ WhileStatement
+ ReadStatement
+ WriteStatement
+ newLineStatement
+ Expression
+ RelopExpression
+ SimpleExpression
+ Term
+ Primary
+ FunctionCall
+ ActualParameters

# Java Notes
+ main function must have the argument ```String [] args``` and only that argument



    
