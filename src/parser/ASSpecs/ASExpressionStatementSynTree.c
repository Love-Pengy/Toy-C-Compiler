//B. Frazier 3/19/24

#ifndef DYNAMICARRAY
    #define DYNAMICARRAY
    #include "../../../lib/dynamicArray/dynamicArray.h"
#endif

#ifndef ASSYNTREE
    #define ASSYNTREE
    #include "../../../include/parser/ASsynTree.h"
#endif


#ifndef STDLIB
    #define STDLIB
    #include <stdlib.h>
#endif


struct expressionStatementTreeType{
    expressionTree expression;
};


expressionStatementTree createExpressionStatementTree(expressionTree expr){
    expressionStatementTree est = malloc(sizeof(struct expressionStatementTreeType));
    est->expression = expr;
    return(est);
}


list expressionStatementTreeToString(expressionStatementTree est){
    list string = createList();
    listCat(string, "exprState(");
    llistCat(string, expressionTreeToString(est->expression));    
    listCat(string, ")\n");
    return(string);
}

