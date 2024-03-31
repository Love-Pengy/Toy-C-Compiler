//B. Frazier 3/20/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/ASsynTree.h"
#include <stdlib.h>



struct whileStatementTreeType{
    expressionTree exp;
    statementTree st;
};


whileStatementTree initWhileStatementTree(void){
    whileStatementTree wst = malloc(sizeof(struct whileStatementTreeType));
    return(wst);
}

whileStatementTree createWhileStatementTree(expressionTree* expr, statementTree* stt){
    whileStatementTree wst = malloc(sizeof(struct whileStatementTreeType));
    wst->exp = (*expr);
    wst->st = (*stt);
    return(wst);

}

list whileStatementTreeToString(whileStatementTree ws){
    list string = createList();
    listCat(&string, "whileState(");
    llistCat(&string, expressionTreeToString(ws->exp));
    llistCat(&string, statementTreeToString(ws->st));
    listCat(&string, ")\n");
    return(string);
}

