+~~ what is returned out of the lexer needs to be a struct with a LEXEME and a STRING (this will represent what it actually is)~~
+~~ lets call this struct a token~~
+ ~~implement getLineNum~~
+ ~~implement getPos~~
+ ~~make a print function for the structs~~
+ ~~Write up a file for trees so I can just call it and test it seperately~~
^^^ this tree structure is going to be the states stores within other states so the actual tree data structure isnt nescessary 
~~+ finish the command line arguments~~ 
    ~~+ help~~
    ~~+ output ~~
    ~~+ class~~
    ~~+ debug ~~
        ~~+ 0~~
        ~~+ 1~~
        ~~+ 2~~
    ~~+ abstract~~ 
    ~~+ symbol~~
    ~~+ code~~
    ~~+ verbose~~
    ~~+ version~~ 

~~+ fix up makefile to actually make use of .o files and dont rewrite everytime~~
~~+ make file pointer global so that it doesn't have to be passed in everywhere~~
~~+ finish the parser ~~
~~+ make errors flush buffer before exiting the program~~
~~+ make readme file dumb verbose - explain every function in the make file~~ 
~~+ make scanner messages output useful information for location~~
~~+ make command line parser not require .tc at the end~~ 
~~+ put name on file~~
~~+ make a free token option for when it's done with~~
~~+ make tokens free when next token is loaded into currentToken ~~
~~+ make a dynamic array library for the holding of the string for the print functions in the AST files because I don't want to hard code it~~ 
~~+ test said dynamic array library~~ 
~~+ make a while loop for the expand function so that you can expand as many chunks as needed~~
IMPORTANT 
    all of the overall categories need to have their own structs and be part of this all, so all of the functions that had expression in them need to be changed to the struct
        + ones that need to be made: 
            + ~~program ~~
            + ~~definition~~ 
            + ~~statement~~
            + ~~expression~~
            + ~~operator~~
+ make a string to list functon to easily convert items to lists when concatonating things like new line or whatever 
+ implement creation of the AST into the parser
+ to make message pointer make more sense you might have to make it only go to the beginning/end of tokens 
+ make a free tree option for the ast when done with it
+ update the make file with the dynamic array library and AST stuff
