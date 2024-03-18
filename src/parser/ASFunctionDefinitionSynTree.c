//B. Frazier 3/18/24

#ifndef DYNAMICARRAY
    #define DYNAMICARRAY
    #include "../../lib/dynamicArray/dynamicArray.h"
#endif

#ifndef ASSYNTREE
    #define ASSYNTREE
    #include "../../include/parser/ASsynTree.h"
#endif

//function definition consists of an id, a type, 0 or moer variable definitions, or a statement 
//ask about the AST syntax, I don't know at the moment whether tha functions are supposed to be specifically that or you can pick and choose
struct functionDefinitionTreeType{
    list id;
    //type can have a max value of 4 characters (char)
    char *type;
    variableDefinitionTree vDef;
    statementDefinitionTree sDef;
};


