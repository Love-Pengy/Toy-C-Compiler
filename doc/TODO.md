+~~ what is returned out of the lexer needs to be a struct with a LEXEME and a STRING (this will represent what it actually is)~~
+~~ lets call this struct a token~~
+ ~~implement getLineNum~~
+ ~~implement getPos~~
+ ~~make a print function for the structs~~
+ ~~Write up a file for trees so I can just call it and test it seperately~~
^^^ this tree structure is going to be the states stores within other states so the actual tree data structure isnt nescessary 
+ finish the command line arguments 
    ~~+ help~~
    ~~+ output ~~
    + class
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
+ finish the parser 
+ make errors flush buffer before exiting the program
+ make readme file dumb verbose - explain every function in the make file 
