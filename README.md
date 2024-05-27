# Toy C Compiler

<!--toc:start-->
- [Toy C Compiler](#toy-c-compiler)
  - [Lexer Spec](#lexer-spec)
  - [Parser Spec](#parser-spec)
  - [AST Generator Spec](#ast-generator-spec)
  - [Semantic Analysis and Symbol Table Generation Spec](#semantic-analysis-and-symbol-table-generation-spec)
  - [Code Generator Spec](#code-generator-spec)
<!--toc:end-->

A compiler made to compile a subset of C into jasmin code

This compiler is comprised of three main parts:

- lexer
- parser
- AST generator
- code generator

[Build Instructions](./buildIntructions)

## Lexer Spec

The lexer tokenizes the following:

- Keywords
  - int, char, return, if, else, for, do, while, switch, case, default , write, read , continue, break , newline
- comments
  - /**/ and //
- IDs
  - defined as the following
    - letter -> [a-zA-Z]
    - digit -> [0-9]
    - ID -> letter(letter|digit)
- numbers
  - defined as the following
    - digits -> digit digit*
    - optional_fraction -> (.digits) | *epsilon*
    - optional_exponent -> (E (+ | - | *epsilon*) digits) | *epsilon*
    - NUMBER -> digits optional_fraction optional_exponent
- character literals
  - defined as the following
    - a char delimited by ' with no newlines
- string literals
  - a set of characters delimited by " without newlines
- Relational operators
  - ==, !=, <, <=, >=, >
- Addops
  - +, -, ||
- Mulops
  - *, /, %, &&
- Assign Operator: =

## Parser Spec

Toy C Compiler Parses the following specification:

- ToyCProgram -> { Definition } **EOF**
- Definition -> Type **identifier** (FunctionDefinition | <ins>;</ins> )
- Type -> *int* | *char*
- FunctionDefinition -> FunctionDefinition FunctionBody
- FunctionHeader → ( [ FormalParamList ] )
- FunctionBody → CompoundStatement
- FormalParamList → Type identifier { , Type identifier }
- Statement → ExpressionStatement\
| BreakStatement\
| CompoundStatement\
| IfStatement\
| NullStatement\
| ReturnStatement\
| WhileStatement\
| ReadStatement\
| WriteStatement\
| NewLineStatement\
- ExpressionStatement → Expression ;
- BreakStatement → break ;
- CompoundStatement → { { Type identifier ; } { Statement } }
- IfStatement → if ( Expression ) Statement [ else Statement ]
- NullStatement → ;
- ReturnStatement → return [ Expression ] ;
- WhileStatement → while ( Expression ) Statement
- ReadStatement → read ( identifier { , identifier } ) ;
- WriteStatement → write ( ActualParameters ) ;
- NewLineStatement → newline ;
- Expression → RelopExpression { assignop RelopExpression }
- RelopExpression → SimpleExpression { relop SimpleExpression }
- SimpleExpression → Term { addop Term }
- Term → Primary { mulop Primary }
- Primary → identifier [ FunctionCall ]\
| number\
| stringConstant\
| charConstant\
| ( Expression )\
| ( − | not ) Primary\
- FunctionCall → ( [ ActualParameters ] )
- ActualParameters → Expression { , Expression }

- Additional rule:
  - a main function is required for the program to be valid

## AST Generator Spec

The AST generator generates and AST based on the following grammar:

- Program ≜ prog(Definition∗)
- Definition ≜ funcDef(Id, Type, varDef(Id+, Type)∗, Statement) | varDef(Id+, Type)
- Statement ≜ exprState(Expression) \
| breakState()\
| blockState(varDef(Id+, Type)∗, Statement∗)\
| ifState(Expression, Statement, Statement?)\
| nullState()\
| returnState(Expression?)\
| whileState(Expression, Statement)\
| readState(Id+)\
| writeState(Expression+)\
| newLineState()\
- Expression ≜ Number | Identifier | CharLiteral | StringLiteral
| funcCall(Identifier, Expression∗)\
| expr(Operator, Expression, Expression)\
| minus(Expression)\
| not(Expression)\
- Operator ≜ + | − | ∗ | / | % | || | && | <= | < | = | > | >= | ! =

## Semantic Analysis and Symbol Table Generation Spec

The semantic analyzer analyses the code given the following restrictions:

- all programs must have a main function
- all IDs must be declared before they are used
- subroutine parameters and/or return types must agree in number and type
- all expressions must be type compatible
- division by zero is undefined

## Code Generator Spec

The code generator generates the code given the following restrictions:

- restricted to only integers
- code generation for characters and strings are restricted to write statements
- break statements are ignored
- function calls and definitions aside from the main function are ignored
- nested blocks are not implemented
