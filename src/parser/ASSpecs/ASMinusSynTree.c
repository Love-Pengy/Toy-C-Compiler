//B. Frazier 3/23/24

//B. Frazier 3/23/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/ASsynTree.h"
#include <stdlib.h>

struct minusTreeType{
    expressionTree exp;
};


minusTree initMinusTree(void){
    minusTree min = malloc(sizeof(struct minusTreeType));
    return(min);
}

minusTree createMinusTree(expressionTree* ex){
    minusTree min = initMinusTree();
    min->exp = (*ex);
    return(min);
}

list minusTreeToString(minusTree min){
    list string = createList();
    listCat(&string, "minus(");
    llistCat(&string, expressionTreeToString(min->exp));
    listCat(&string, ")\n");
    return(string);
}


