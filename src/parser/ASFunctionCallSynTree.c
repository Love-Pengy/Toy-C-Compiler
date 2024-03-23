//B. Frazier 3/22/24

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

#ifndef STRING
    #define STRING
    #include <string.h>
#endif


struct functionCallTreeType{
    char * id;
    expressionTree * exprs;
    int numExprs;
};

functionCallTree createFunctionCallTree(char *ident, expressionTree* exp, int amt){
    functionCallTree fct = malloc(sizeof(struct functionCallTreeType));

    fct->id = malloc(sizeof(char) * (strlen(ident) + 1));
    strcpy(fct->id, ident);
    fct->expressionTree = malloc(sizeof(struct expressionTreeType) * amt);

    for(int i = 0; i < amt; i++){
        fct->exprs[i] = exp[i];
    }

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

