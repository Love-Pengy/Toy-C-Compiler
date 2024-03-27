//B. Frazier 3/20/24

#include "../../../include/parser/ASsynTree.h"
#include "../../../lib/dynamicArray/dynamicArray.h"
#include <stdlib.h>



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

