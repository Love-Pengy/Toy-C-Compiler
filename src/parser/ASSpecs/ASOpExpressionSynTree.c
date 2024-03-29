//B. Frazier 3/22/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/ASsynTree.h"
#include <stdlib.h>


struct opExpressionTreeType{
    operatorTree op;
    expressionTree exp1;
    expressionTree exp2;
};


opExpressionTree initOpExpressionTree(void){
    opExpressionTree oet = malloc(sizeof(struct opExpressionTreeType));
    return(oet);
}

opExpressionTree createOpExpressionTree(operatorTree oper, expressionTree ex1, expressionTree ex2){
    opExpressionTree oet = initOpExpressionTree();
    oet->op = oper;
    oet->exp1 = ex1;
    oet->exp2 = ex2;
    return(oet);
}

list opExpressionTreeToString(opExpressionTree oe){
    list string = createList();
    listCat(string, "expr(");
    llistCat(string, operatorTreeToString(oe->op));
    llistCat(string, expressionTreeToString(oe->exp1)); 
    llistCat(string, expressionTreeToString(oe->exp2)); 
    listCat(string, ")\n");
    return(string);
}

