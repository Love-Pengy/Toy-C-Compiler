# Notes for the lexer

+ goal is to convert the dfa writted before into code. 
+ Idea 1 was to take the line, delimit it by spaces and compare with strings
    + this obviously didnt work because you cant strcmp the digits for example because they can theoretically have any number of digits 
+ Idea 2 is to actually treat it like a DFA. Meaning that I take the delimited string and character by character evaluate like that
