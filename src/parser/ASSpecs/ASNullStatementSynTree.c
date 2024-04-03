//B. Frazier 3/20/24

#include "../../../include/parser/ASsynTree.h"
#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/prettyPrinting.h"
#include <stdlib.h>



struct nullStatementTreeType{
};



nullStatementTree initNullStatementTree(void){
    nullStatementTree nst = malloc(sizeof(struct nullStatementTreeType));
    return(nst);
}

nullStatementTree createNullStatementTree(void){
    nullStatementTree nst = initNullStatementTree();
    return(nst);

}

list nullStatementTreeToString(nullStatementTree nst){
    list string = createList();
    listCat(&string, spaces());
    listCat(&string, "nullState(");
    indent();
    outdent();
    listCat(&string, ")\n");
    return(string);
}

