//B. Frazier 3/19/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/ASsynTree.h"
#include <stdlib.h>


struct expressionStatementTreeType{
    expressionTree expression;
};


expressionStatementTree initExpressionStatementTree(void){
    expressionStatementTree est = malloc(sizeof(struct expressionStatementTreeType));
    return(est);
}

expressionStatementTree createExpressionStatementTree(expressionTree* expr){
    expressionStatementTree est = initExpressionStatementTree();
    est->expression = (*expr);
    return(est);
}


list expressionStatementTreeToString(expressionStatementTree est){
    list string = createList();
    listCat(&string, "exprState(");
    llistCat(&string, expressionTreeToString(est->expression));    
    listCat(&string, ")\n");
    return(string);
}

