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



struct minusTreeType{
    expressionTree exp;
};


minusTree createMinusTree(expressionTree ex){
    minusTree min = malloc(sizeof(struct minusTreeType));
    min->exp = ex;
    return(min);
}

list minusTreeToString(minusTree min){
    list string = createList();
    listCat(string, "minus(");
    llistCat(string, expressionTreeToString(min->exp));
    listCat(string, ")\n");
    return(string);
}

