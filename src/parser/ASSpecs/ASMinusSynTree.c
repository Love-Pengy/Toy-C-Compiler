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

