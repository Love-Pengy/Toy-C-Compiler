//B. Frazier 3/19/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/ASsynTree.h"
#include "../../../include/parser/prettyPrinting.h"
#include "../../../include/cmdLine/TCglobals.h"
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
    listCat(&string, spaces());
    listCat(&string, "exprState(\n");
    indent();
    llistCat(&string, expressionTreeToString(est->expression));    
    outdent();
    listCat(&string, spaces());
    listCat(&string, ")\n");
    return(string);
}

void generateExpressionStatementTree(expressionStatementTree est, FILE* fptr){

    if(debug_codeGen){
        printf("[CODE GENERATOR] Generating Expression Statement\n");
        fflush(stdout);
    }

    generateExpressionTree(est->expression, fptr);
}
