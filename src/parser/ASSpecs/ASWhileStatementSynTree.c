//B. Frazier 3/20/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/ASsynTree.h"
#include "../../../include/parser/prettyPrinting.h"
#include "../../../include/cmdLine/TCglobals.h"
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
    listCat(&string, spaces());
    listCat(&string, "whileState(\n");
    indent();
    llistCat(&string, expressionTreeToString(ws->exp));
    llistCat(&string, statementTreeToString(ws->st));
    outdent();
    listCat(&string, spaces());
    listCat(&string, ")\n");
    return(string);
}

void generateWhileStatementTree(whileStatementTree ws, FILE* fptr){
    int label1 = CURRENTLABEL;
    int label2 = CURRENTLABEL+1;
    CURRENTLABEL += 2;
    fprintf(fptr, "Label%d: \n", label1);
    generateExpressionTree(ws->exp, fptr);
    fprintf(fptr, "bipush 0\n");
    fprintf(fptr, "%s%d\n", "if_icmpeq Label", label2);  
    generateStatementTree(ws->st, fptr);
    fprintf(fptr, "goto Label%d\n", label1);
    fprintf(fptr, "Label%d:\n", label2);
}
