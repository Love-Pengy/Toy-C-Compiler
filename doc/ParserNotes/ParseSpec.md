# Grammer

## NOTE: {} IN THIS CONTEXT MEANS 0 OR MORE. BASICALLY THE * OPERATOR 
## ANOTHER NOTE I THINK [] IN THIS CONTENXT MEANS YOU CAN ONLY HAVE ONE OR 0
## two |'s are completely optional

+ Program
    + {Definition} EOF
+ Definition
    + Type ID (FunctionDefinition | ;)
+ Type
    + int | char
+ FunctionDefinition
    + FunctionHeader FunctionBody
+ FunctionHeader
    + "("|FormalParamList|")"
+ FunctionBody
    + CompoundStatement
+ FormalParamList
    + Type ID { COMMA Type ID } 
+ Statement
    + ExpressionStatement | BreakStatement | CompoundStatement | IfStatement | NullStatament | ReturnStatement | WhileStatement | ReadStatement | WriteStatement | NewLineStatement

+ ExpressionStatement
    + Expression SEMICOLON
+ BreakStatement
    + break SEMICOLON
+ CompoundStatement 
    + LCURLY { Type ID SEMICOLON } { Statement } RCURLY
+ IfStatement
    + if RPAREN Expression LPAREN Statement [ else Statement ] 
+ NullStatament
    + SEMICOLON
+ ReturnStatement
    + return [ Expression ] SEMICOLON
+ WhileStatement
    + while RPAREN Expression LPAREN Statement
+ ReadStatement
    + read RPAREN ID { COMMA ID } LPAREN SEMICOLON
+ WriteStatement
    + write RPAREN ActualParameters LPAREN SEMICOLON
+ NewLineStatement
    + newline SEMICOLON
+ Expression
    + RelopExpression { ASSIGNOP RelopExpression } 
+ RelopExpression
    + SimpleExpression { RELOP SimpleExpression } 
+ SimpleExpression
    + Term { ADDOP Term } 
+ Term 
    + Primary { MULOP Primary } 
+ Primary 
    + ID [ FunctionCall ] | NUMBER | STRING | CHARLITERAL | LPAREN Expression RPAREN | ( - | NOT ) Primary
+ FunctionCall
    + RPAREN [ ActualParameters ] LPAREN
+ ActualParameters
    + Expression { COMMA Expression }

