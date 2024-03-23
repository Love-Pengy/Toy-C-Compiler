//B. Frazier 3/23/24

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




struct operatorTreeType{
    char* op;
};


operatorTree createOperatorTree(char* operator){
    operatorTree oper = malloc(sizeof(struct operatorTreeType));
    oper->op = malloc(sizeof(char) * (strlen(operator) + 1));
    strcpy(oper->op, operator)
    return(oper);
}

list operatorTreeToString(operatorTree oper){
    list string = createList();
    listCat(string, "Operator(");
    llistCat(string, (oper->op));
    listCat(string, ")\n");
    return(string);
}

