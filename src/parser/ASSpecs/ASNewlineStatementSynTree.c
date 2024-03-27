//B. Frazier 3/21/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/ASsynTree.h"
#include <stdlib.h>



struct newLineStatementTreeType{
};


newLineStatementTree createNewLineStatementTree(void){
    newLineStatementTree nst = malloc(sizeof(struct newLineStatementTreeType));
    return(nst);
}

list newLineStatementTreeToString(newLineStatementTree n){
    list string = createList();
    listCat(string, "newLineState(");
    listCat(string, ")\n");
    return(string);
}

