//B. Frazier 3/21/24

#ifndef DYNAMICARRAY
    #define DYNAMICARRAY
    #include "../../../lib/dynamicArray/dynamicArray.h"
#endif

#ifndef ASSYNTREE
    #define ASSYNTREE
    #include "../../../include/parser/ASsynTree.h"
#endif

#ifndef STDLIB
    #define STDLIB
    #include <stdlib.h>
#endif



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

