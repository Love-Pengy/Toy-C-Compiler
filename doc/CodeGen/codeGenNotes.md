# Code Generation and Semantic Analysis

### Overall Restrictions/Features
+ Code generation and semantic analysis only happens for integers 
+ No code needs to be generated for break statements or char literals


### Semantic Analysis
+ All identifiers must be declared before usage
+ Identifiers can only have one binding per scope 
    + AKA they cant be redefined within a scope
+ function parameters and return types must agree in number and type
+ all expressions must be type compatible
+ division by 0 is undefined (I think this should throw an error)


### Symbol Table
+ if not doing EC there will only be one scope (main) and therefore one symbol table
+ symbol table should have the following operations with the parameters following in () and the return argument in {} preceeding it: 
    + {int} [I think this is whether or not it exists already] } add (symTable \*, symbol \*)
    + {int} find (symTable \*, char \* [this will be the id we're looking for]) 
    + {symbol \*} find (symTable \*, symbol \*)
    + {symbol \*} getSym (symTable \*, int [offset])
    + {symbol \*} getSym(symTable \*, symbol \*)
    + {char \*} toString (symTable)

+ the symbols themselves should have the following operations with the parameters following in () and the return argument in {} preceeding it: 
    + REFERENCE
        + enum symType = {VAR, LABEL, OFFSET, NO_TYPE}
    + {char\*} getId (symbol \*)
    + {void} setId (symbol \*, char\*)
    + {enum symType} getType (symbol)
    + {void} setType (symbol \*, enum symType)
    + {int} getOffset (symbol)
    + {void} setOffset (symbol \*, int)
    + {char \*} toString (symbol)
