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



struct whileStatementTreeType{
    expressionTree exp;
    statementTree st;
};


whileStatementTree createWhileStatementTree(expressionTree expr, statementTree stt){
    whileStatementTree wst = malloc(sizeof(struct whileStatementTreeType));
    wst->exp = expr;
    wst->st = stt;
    return(wst);

}

list whileStatementTreeToString(whileStatementTree ws){
    list string = createList();
    listCat(string, "whileState(");
    listCat(string, expressionTreeToString(ws->exp));
    listCat(string, statementTreeToString(ws->st));
    listCat(string, ")\n");
    return(string);
}

