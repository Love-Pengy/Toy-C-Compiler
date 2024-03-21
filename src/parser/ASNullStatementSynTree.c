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



struct nullStatementTreeType{
};

nullStatementTree createNullStatementTree(void){
    nullStatementTree nst = malloc(sizeof(struct nullStatementTreeType));
    return(nst);

}

list nullStatementTreeToString(nullStatementTree nst){
    list string = createList();
    listCat(string, "nullState(");
    listCat(string, ")\n");
    return(string);
}

