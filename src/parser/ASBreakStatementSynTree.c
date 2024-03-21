//B. Frazier 3/20/24

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


struct breakStatementTreeType{
};


breakStatementTree createBreakStatementTree(void){
    breakStatementTree bst = malloc(sizeof(struct breakStatementTreeType));
    return(bst);
}


list breakStatementTreeToString(breakStatementTree bst){
    list string = createList();
    listCat(string, "breakState(");
    listCat(string, ")\n");
    return(string);
}

