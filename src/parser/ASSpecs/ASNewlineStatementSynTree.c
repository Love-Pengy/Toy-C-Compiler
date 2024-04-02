//B. Frazier 3/21/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/prettyPrinting.h"
#include "../../../include/parser/ASsynTree.h"
#include <stdlib.h>



struct newLineStatementTreeType{
};

newLineStatementTree initNewLineStatementTree(void){
    newLineStatementTree nst = malloc(sizeof(struct newLineStatementTreeType));
    return(nst);
}

newLineStatementTree createNewLineStatementTree(void){
    newLineStatementTree nst = malloc(sizeof(struct newLineStatementTreeType));
    return(nst);
}

list newLineStatementTreeToString(newLineStatementTree n){
    list string = createList();
    listCat(&string, spaces());
    listCat(&string, "newLineState(\n");
    indent();
    outdent();
    listCat(&string, spaces());
    listCat(&string, ")\n");
    return(string);
}

