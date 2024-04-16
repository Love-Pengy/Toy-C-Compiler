+~~ what is returned out of the lexer needs to be a struct with a LEXEME and a STRING (this will represent what it actually is)~~
+~~ lets call this struct a token~~
+ ~~implement getLineNum~~
+ ~~implement getPos~~
+ ~~make a print function for the structs~~
+ ~~Write up a file for trees so I can just call it and test it seperately~~
^^^ this tree structure is going to be the states stores within other states so the actual tree data structure isnt nescessary 
+ ~~finish the command line arguments~~ 
    + ~~help~~
    + ~~output~~
    + ~~class~~
    + ~~debug~~
        + ~~0~~
        + ~~1~~
        + ~~2~~
    + ~~abstract~~ 
    + ~~symbol~~
    + ~~code~~
    + ~~verbose~~
    + ~~version~~ 

+ ~~fix up makefile to actually make use of .o files and dont rewrite everytime~~
+ ~~make file pointer global so that it doesn't have to be passed in everywhere~~
+ ~~finish the parser~~
+ ~~make errors flush buffer before exiting the program~~
+ ~~make readme file dumb verbose - explain every function in the make file~~ 
+ ~~make scanner messages output useful information for location~~
+ ~~make command line parser not require .tc at the end~~ 
+ ~~put name on file~~
+ ~~make a free token option for when it's done with~~
+ ~~make tokens free when next token is loaded into currentToken ~~
+ ~~make a dynamic array library for the holding of the string for the print functions in the AST files because I don't want to hard code it~~ 
+ ~~test said dynamic array library~~ 
+ ~~make a while loop for the expand function so that you can expand as many chunks as needed~~
+ ~~all of the overall categories need to have their own structs and be part of this all, so all of the functions that had expression in them need to be changed to the struct~~
    + ~~ones that need to be made: ~~
        + ~~program ~~
        + ~~definition~~ 
        + ~~statement~~
        + ~~expression~~
        + ~~operator~~
+ ~~make a string to list functon to easily convert items to lists when concatonating things like new line or whatever~~ 
+ ~~fix functions that got messed up due to understanding (all functions should return the category)~~
+ ~~implement creation of the AST into the parser~~
+ ~~update the make file with the dynamic array library and AST stuff~~
+ ~~go through and make adders and initializers for everything that needs it in the main parser file~~
+ ~~run through warnings and errors for the AST~~
+ ~~test the entirety of the language~~ 
+ ~~Debug WColumn memory issue~~
+ ~~change pretty printing indents to four spaces~~
+ ~~fix pretty printing that shit is NOT pretty~~ 
+ ~~for op expression trees I need to fix two op expression trees being within one another they are not showing up~~ 
+ ~~Thoroughly test the parser before moving onto code generation~~ 
+ ~~write out skeleton for symbols~~
+ ~~write out skeleton for symbol tables~~
+ ~~change symbol and symbol table functions to lists so I don't have to worry about it~~
+ ~~test symbols and symbol tables~~
+ ~~add semantic analysis to the parser~~ 
    + ~~all programs must have a main function otherwise it is not valid~~
    + ~~need to go through everytime you get an id and check if its defined or not~~
    + ~~if not defined and declaration then add to symbol table~~
    + ~~else fail because it was called without declaration~~
    + ~~all expressions must be type compatible (only ints)~~
    + ~~SEMANTICS TO DO~~ 
        + ~~primary~~
            + ~~tentative implementation~~ 
            + ~~testing~~
        + ~~read~~
            + ~~tentative implementation~~ 
            + ~~testing~~
        + ~~formal param list (function header AKA what is inside the paren)~~
            + ~~tentative implementation~~ 
            + ~~testing~~
        + ~~compound statement (function body)~~
            + ~~tentative implementation~~ 
            + ~~testing~~
        + ~~functionDefintion (grabbing return type)~~
            + ~~tentative implementation~~
            + ~~testing~~
+ ~~fix checker for compatible types (currently isn't checking properly but is implemented)~~
+ ~~make symbol table global so that it can be printed from main~~ 
+ make the templates for all of the functions 
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
+ generate code given the valid AST
+ debug output file 
    + currently it outputs with the file name '..j' in the root directory (means that the header of the file is jsut '.' 

THIS CAN BE DONE LATER WORK ON FUNCTIONALITY 
vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
+ program, definition, statement, expression, and operator should all have the block look
    + others should be one liners with the expception of the following: 
+ make a free tree option for the ast when done with it
+ to make message pointer make more sense you might have to make it only go to the beginning/end of tokens 
    + fix semantic error handling (it points to the wrong place) 
