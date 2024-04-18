//B. Frazier 3/23/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/prettyPrinting.h"
#include "../../../include/parser/ASsynTree.h"
#include <stdlib.h>


struct notTreeType{
    expressionTree exp;
};

notTree initNotTree(void){
    notTree not = malloc(sizeof(struct notTreeType));
    return(not);
}

notTree createNotTree(expressionTree* ex){
    notTree not = malloc(sizeof(struct notTreeType));
    not->exp = (*ex);
    return(not);
}

list notTreeToString(notTree not){
    list string = createList();
    listCat(&string, spaces());
    listCat(&string, "not(\n");
    indent();
    llistCat(&string, expressionTreeToString(not->exp));
    outdent();
    listCat(&string, spaces());
    listCat(&string, ")\n");
    return(string);
}

//no not evaluation is done within this function
void generateNotTree(notTree not, FILE* fptr){
    generateExpressionTree(not->exp,fptr);
}
