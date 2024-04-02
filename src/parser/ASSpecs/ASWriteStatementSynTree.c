//B. Frazier 3/21/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/ASsynTree.h"
#include <stdlib.h>
#include "../../../include/parser/prettyPrinting.h"


struct writeStatementTreeType{
    expressionTree *exprs;
    int amtExprs;
};

writeStatementTree initWriteStatementTree(void){
    writeStatementTree wst = malloc(sizeof(struct writeStatementTreeType));
    wst->exprs = malloc(sizeof(expressionTree) *100);
    wst->amtExprs = 0;
    return(wst);
}

void addExpressionTreeWriteStatementTree(writeStatementTree *w, expressionTree* e){ 
    (*w)->exprs[(*w)->amtExprs] = (*e);
    (*w)->amtExprs++;
}

writeStatementTree createWriteStatementTree(expressionTree* exp,int amt){
    writeStatementTree wst = initWriteStatementTree();
    wst->exprs = exp;
    wst->amtExprs = amt;
    return(wst);
}

list writeStatementTreeToString(writeStatementTree ws){
    list string = createList();
    listCat(&string, spaces());
    listCat(&string, "writeState(\n");
    indent();
    for(int i = 0; i < ws->amtExprs; i++){
        llistCat(&string, expressionTreeToString(ws->exprs[i]));
    }
    outdent();
    listCat(&string, spaces());
    listCat(&string, ")\n");
    return(string);
}

