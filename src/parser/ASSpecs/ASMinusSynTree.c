//B. Frazier 3/23/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/ASsynTree.h"
#include "../../../include/parser/prettyPrinting.h"
#include "../../../include/cmdLine/TCglobals.h"
#include <stdlib.h>

struct minusTreeType{
    expressionTree exp;
};


minusTree initMinusTree(void){
    minusTree min = malloc(sizeof(struct minusTreeType));
    return(min);
}

minusTree createMinusTree(expressionTree* ex){
    minusTree min = initMinusTree();
    min->exp = (*ex);
    return(min);
}

expressionTree getMinusExpression(minusTree min){
    return(min->exp);
}

list minusTreeToString(minusTree min){
    list string = createList();
    listCat(&string, spaces());
    listCat(&string, "minus(\n");
    indent();
    llistCat(&string, expressionTreeToString(min->exp));
    outdent();
    listCat(&string, spaces());
    listCat(&string, ")\n");
    return(string);
}

void generateMinusTree(minusTree min, FILE* fptr){
    
    if(debug_codeGen){
        printf("[CODE GENERATOR] Generating Minus Tree\n");
        fflush(stdout);
    }

    generateExpressionTree(min->exp,fptr);
    fprintf(fptr, "%s\n", "bipush -1");
    fprintf(fptr, "%s\n", "imul");

}


