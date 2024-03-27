//B. Frazier 3/22/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/ASsynTree.h"
#include <stdlib.h>
#include <string.h>


struct functionCallTreeType{
    char * id;
    expressionTree * exprs;
    int numExprs;
};

functionCallTree initFunctionCallTree(void){
    functionCallTree fct = malloc(sizeof(struct functionCallTreeType));
    return(fct);
}

functionCallTree createFunctionCallTree(char *ident, expressionTree* exp, int amt){

    functionCallTree fct = initFunctionCallTree();

    fct->id = malloc(sizeof(char) * (strlen(ident) + 1));
    strcpy(fct->id, ident);
    fct->exprs = exp;
    fct->numExprs = amt;
    return(fct);
}

list functionCallTreeToString(functionCallTree fct){
    list string = createList();
    listCat(string, "funcCall(");
    listCat(string, fct->id);

    for(int i = 0; i < fct->numExprs; i++){
        llistCat(string, expressionTreeToString(fct->exprs[i]));
    } 

    listCat(string, ")\n");
    return(string);
}

