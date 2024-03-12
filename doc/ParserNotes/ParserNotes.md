

+ when making the recurrsive descent parser when making the modules for all of the state's trees you ignore the terminals. Those are handles inside of the actual parsing main itself


# Functions that need to be created with their own trees

+ ToyCProgram 
+ Definition 
+ Type
+ FunctionDefinition 
+ FunctionHeader
+ FunctionBody 
+ FormalParamList
+ Statement
+ ExpressionStatement
+ BreakStatement
+ CompoundStatement
+ IfStatement
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

How this is going to be done is I'm going to go from the top of the tree to the bottom, meaning that I need to start by implementing from main and work my way inward given all of the possibilities I can do



    
