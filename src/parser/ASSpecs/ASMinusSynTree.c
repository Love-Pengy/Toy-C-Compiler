//B. Frazier 3/23/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/ASsynTree.h"
#include <stdlib.h>


struct notTreeType{
    expressionTree exp;
};


notTree createNotTree(expressionTree ex){
    notTree not = malloc(sizeof(struct notTreeType));
    not->exp = ex;
    return(not);
}

list notTreeToString(notTree not){
    list string = createList();
    listCat(string, "not(");
    llistCat(string, expressionTreeToString(not->exp));
    listCat(string, ")\n");
    return(string);
}

