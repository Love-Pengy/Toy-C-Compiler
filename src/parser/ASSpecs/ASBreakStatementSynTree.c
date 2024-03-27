//B. Frazier 3/20/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/ASsynTree.h"
#include <stdlib.h>


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

