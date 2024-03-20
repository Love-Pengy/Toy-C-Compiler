//B. Frazier 3/19/24

#ifndef DYNAMICARRAY
    #define DYNAMICARRAY
    #include "../../lib/dynamicArray/dynamicArray.h"
#endif

#ifndef ASSYNTREE
    #define ASSYNTREE
    #include "../../include/parser/ASsynTree.h"
#endif

#ifndef STRING
    #define STRING
    #include <string.h>
#endif

#ifndef STDLIB
    #define STDLIB
    #include <stdlib.h>
#endif


struct expressionStatementTreeType{
    char* expression;
};


expressionStatementTree createExpressionStatementTree(char * expr){
    expressionStatementTree est = malloc(sizeof(struct expressionStatementTreeType));
    est->expression = malloc(sizeof(char) * (strlen(expr) + 1));
    strcpy(est->expression, expr);
    return(est);
}


list expressionStatementTreeToString(expressionStatementTree est){
    list string = createList();
    listCat(string, "exprState(");
    listCat(string, est->expression);    
    listCat(string, ")\n");
    return(string);
}

