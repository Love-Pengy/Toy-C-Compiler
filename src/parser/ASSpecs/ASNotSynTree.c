//B. Frazier 3/23/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/prettyPrinting.h"
#include "../../../include/parser/ASsynTree.h"
#include "../../../include/cmdLine/TCglobals.h"
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

void generateNotTree(notTree not, FILE* fptr){
    generateExpressionTree(not->exp,fptr);
    fprintf(fptr, "ifeq Label%d\n", CURRENTLABEL);
    fprintf(fptr, "bipush 0\n");
    fprintf(fptr, "goto Label%d\n", CURRENTLABEL+1);
    fprintf(fptr, "Label%d:\n", CURRENTLABEL);
    fprintf(fptr, "bipush 1\n");
    fprintf(fptr, "Label%d:\n", CURRENTLABEL+1);    
    CURRENTLABEL+=2;
}
