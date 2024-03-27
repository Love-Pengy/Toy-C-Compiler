//B. Frazier 3/21/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/ASsynTree.h"
#include <stdlib.h>


struct writeStatementTreeType{
    expressionTree *exprs;
    int amtExprs;
};


writeStatementTree createWriteStatementTree(expressionTree* exp,int amt){
    writeStatementTree wst = malloc(sizeof(struct writeStatementTreeType));
    wst->exprs = exp;
    wst->amtExprs = amt;
    return(wst);
}

list writeStatementTreeToString(writeStatementTree ws){
    list string = createList();
    listCat(string, "writeState(");
    for(int i = 0; i < ws->amtExprs; i++){
        llistCat(string, expressionTreeToString(ws->exprs[i]));
    }
    listCat(string, ")\n");
    return(string);
}

