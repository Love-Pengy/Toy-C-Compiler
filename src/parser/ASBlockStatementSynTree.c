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

//varDef(Id+, Type)∗, Statement∗
struct blockStatementTreeType{
    variableDefinitionTree * vdt;
    int vAmount;
    char ** statements;
    int sAmount;
};

//if a parameter is 0 then it will be passed NULL and an amount of 0
blockStatementTree createBlockStatementTree(variableDefinitionTree *variables, int amountVars, char **stats, int amountStats){
    blockStatementTree output = malloc(sizeof(struct blockStatementTreeType));
    output->vdt = malloc(sizeof(variableDefinitionTree) * amountVars);
    output->vdt = variables; 
    output->vAmount = amountVars;
    output->statements = malloc(sizeof(stats) + 1);
    output->statements = stats;
    output->sAmount = amountStats;
    return(output);
}


list blockStatementTreeToString(blockStatementTree bst){
    list string = createList();
    listCat(string, "blockState(");
    for(int i = 0; i < bst->vAmount; i++){
        listCat(string, variableDefinitionTreeToString(bst->vdt[i]);
    }    
    for(int i = 0; i < bst->sAmount; i++){
        listCat(string, bst->statements[i]);
    }
    listCat(string, ")\n");
    return(string);
}

