//B. Frazier 3/20/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/ASsynTree.h"
#include <stdlib.h>

//varDef(Id+, Type)∗, Statement∗
struct blockStatementTreeType{
    variableDefinitionTree * vdt;
    int vAmount;
    statementTree* statements;
    int sAmount;
};

void addVarDefBlockStatementTree(blockStatementTree* bst, variableDefinitionTree* v){
    (*bst)->vdt[(*bst)->vAmount] = (*v);
    (*bst)->vAmount++;
}

void addStatementBlockStatementTree(blockStatementTree* bst, statementTree* s){
    (*bst)->statements[(*bst)->sAmount] = (*s);
    (*bst)->sAmount++;
}

blockStatementTree initBlockStatementTree(void){
    blockStatementTree output = malloc(sizeof(struct blockStatementTreeType));
    output->vdt = malloc(sizeof(variableDefinitionTree) * 100);
    output->statements = malloc(sizeof(statementTree) * 100);
    output->vAmount = 0;
    output->sAmount = 0;
    return(output);
}
//if a parameter is 0 then it will be passed NULL and an amount of 0
blockStatementTree createBlockStatementTree(variableDefinitionTree *variables, int amountVars, statementTree *stats, int amountStats){
    blockStatementTree output = malloc(sizeof(struct blockStatementTreeType));
    output->vdt = malloc(sizeof(variableDefinitionTree));
    output->vdt = variables; 
    output->vAmount = amountVars;
    output->statements = stats;
    output->sAmount = amountStats;
    return(output);
}


list blockStatementTreeToString(blockStatementTree bst){
    list string = createList();
    listCat(&string, "blockState(");
    for(int i = 0; i < bst->vAmount; i++){
        llistCat(&string, variableDefinitionTreeToString((bst->vdt[i])));
    }    
    for(int i = 0; i < bst->sAmount; i++){
        llistCat(&string, statementTreeToString(bst->statements[i]));
    }
    listCat(&string, ")\n");
    return(string);
}

