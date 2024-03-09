# Parser Notes 



+ whole grammer is provided 
+ goal is to make an abstract syntax from the program (listed in 3.1)
+ determine its legal, create AST, traverse AST to create assembly for java virtual machine
+ in 3.1 the part that is to the left of the parenthesis is a tag
    + so it would be tag(**what the tag holds**)
+ the triangle with the two lines under it just means goes to 

# AST Notes
+ * 
    + zero or more
+ + 
    + one or more 
+ we only create an AST if we have a valid parse 


# Recursive-Descent Parser Example
+ {} in grammer mean 0 or more
+ make a function for each state
+ use a global for the look ahead token

```C
//function for checking valid
void accept(char terminal){
    if(sym == terminal) load_sym();
    else printf("syntax error\n");
}
```
+ when you're at the beginning of a state print entering, when you are at the bottom print exiting
+ before you call the next state load the look ahead buffer with the next token if you used one of the tokens
+ if you're in a state and it had an epsilon option and one of the tokens you get is not one of the beginnings of the other options it is epsilon
+ if you have a zero or more option use a while loop
+ as you're going through the states each state is responsible for creating their part of the tree
+ create a tree file for each state
+ set up a print function for each state
+ when going throught each state should do its thing then call the creator for where it came from and pass itself in 
+ outdent -> subtracting four spaces
+ pretty printing is just managing the spacing and can manage it through functions without managing it when doing the print trees 
+ check out unions to make things a bit easier potentially
+ files are in the files section in canvas

