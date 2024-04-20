//B. Frazier 3/23/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/prettyPrinting.h"
#include "../../../include/parser/ASsynTree.h"
#include <stdlib.h>
#include <string.h>

struct operatorTreeType{
    char* op;
};

char* getOperator(operatorTree opTree){
    return(opTree->op);
}

operatorTree initOperatorTree(void){
    operatorTree oper = malloc(sizeof(struct operatorTreeType));
    return(oper);
}

operatorTree createOperatorTree(char* operator){
    operatorTree oper = malloc(sizeof(struct operatorTreeType));
    oper->op = malloc(sizeof(char) * (strlen(operator) + 1));
    strcpy(oper->op, operator);
    return(oper);
}

list operatorTreeToString(operatorTree oper){
    list string = createList();
    listCat(&string, spaces());
    listCat(&string, "Operator(");
    indent();
    listCat(&string, (oper->op));
    outdent();
    listCat(&string, ")\n");
    return(string);
}

