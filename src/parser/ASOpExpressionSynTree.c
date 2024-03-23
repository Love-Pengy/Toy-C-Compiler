//B. Frazier 3/22/24

#ifndef DYNAMICARRAY
    #define DYNAMICARRAY
    #include "../../lib/dynamicArray/dynamicArray.h"
#endif

#ifndef ASSYNTREE
    #define ASSYNTREE
    #include "../../include/parser/ASsynTree.h"
#endif

#ifndef STDLIB
    #define STDLIB
    #include <stdlib.h>
#endif

#ifndef STRING
    #define STRING
    #include <string.h>
#endif


struct opExpressionTreeType{
    operatorTree op;
    expressionTree exp1;
    expressionTree exp2;
};

opExpressionTree createOpExpressionTree(operatorTree oper, expressionTree ex1, expressionTree ex2){
    opExpressionTree oet = malloc(sizeof(struct opExpressionTreeType));
    oet->op = oper;
    oet->exp1 = ex1;
    oet->exp2 = ex2;
    return(oet);
}

list opExpressionTreeToString(opExpressionTree oe){
    list string = createList();
    listCat(string, "expr(");
    listCat(string, operatorTreeToString(oe->op));
    listCat(string, expressionTreeToString(oe->exp1)); 
    listCat(string, expressionTreeToString(oe->exp2)); 
    listCat(string, ")\n");
    return(string);
}

