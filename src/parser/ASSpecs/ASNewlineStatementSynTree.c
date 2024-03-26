//B. Frazier 3/21/24

#ifndef DYNAMICARRAY
    #define DYNAMICARRAY
    #include "../../../lib/dynamicArray/dynamicArray.h"
#endif

#ifndef ASSYNTREE
    #define ASSYNTREE
    #include "../../../include/parser/ASsynTree.h"
#endif

#ifndef STDLIB
    #define STDLIB
    #include <stdlib.h>
#endif



struct newLineStatementTreeType{
};


newLineStatementTree createNewLineStatementTreeType(void){
    newLineStatementTree nst = malloc(sizeof(struct newLineStatementTreeType));
    return(nst);
}

list newLineStatementTreeToString(newLineStatementTree n){
    list string = createList();
    listCat(string, "newLineState(");
    listCat(string, ")\n");
    return(string);
}

