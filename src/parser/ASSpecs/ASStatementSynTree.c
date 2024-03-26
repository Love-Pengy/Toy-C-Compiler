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

#ifndef STDIO
    #define STDIO
    #include <stdio.h>
#endif

struct statementTreeType{
    enum statementType type;
    union{
        expressionStatementTree exp;
        breakStatementTree bst; 
        blockStatementTree blt; //yum
        ifStatementTree ist;
        nullStatementTree nst; 
        returnStatementTree rst;
        whileStatementTree wst;
        readStatementTree book; 
        writeStatementTree author;
        newLineStatementTree nlst;
    };
};


statementTree createStatementTree(enum statementType t; void* val){
    statementTree st = malloc(sizeof(struct statementTreeType));
    switch(t){
        case exprState:
            st->exp = (expressionStatementTree)val;
            break;
        case breakState:
            st->bst = (breakStatementTree)val;
            break;
        case blockState:
            st->blt = (blockStatementTree)val;
            break
        case ifState:
            st->ist = (ifStatementTree)val;
            break;
        case nullState:
            st->nst = (nullStatementTree)val;
            break;
        case returnState:
            st->rst = (returnStatementTree)val;
            break;
        case whileState:
            st->wst = (whileStatementTree)val;
            break;
        case readState:
            st->book = (readStatementTree)val;
            break;
        case writeState:
            st->author = (writeStatementTree)val;
            break;
        case newLineState:
            st->nlst = (newLineStatementTree)val;
            break;
        default:
            printf("internal error\n");
            break;
    }
    return(nst);
}

list statementTreeToString(statementTree state){
    list string = createList();
    listCat(string, "Statement(");
    switch(state->type){
        case exprState:
            llistCat(string, expressionStatementTreeToString(state->exp));
            break;
        case breakState:
            llistCat(string, breakStatementTreeToString(state->bst));
            break;
        case blockState:
            llistCat(string, blockStatementTreeToString(state->blt));
            break;
        case ifState:
            llistCat(string, ifStatementTreeToString(state->ist)):
            break;
        case nullState:
            llistCat(string, nullStatementTreeToString(state->nst));
            break;
        case returnState:
            llistCat(string, returnStatementTreeToString(state->rst));
            break;
        case whileState:
            llistCat(string, whileStatementTreeToString(state->wst));
            break;
        case readState:
            llistCat(string, readStatementTreeToString(state->book));
            break;
        case writeState:
            llistCat(string, writeStatementTreeToString(state->author));
            break;
        case newLineState:
            llistCat(string, newLineStatementTreeToString(state->nlst));
            break;
        default:
            printf("internal error\n");
            break;
    }
    listCat(string, ")\n");
    return(string);
}

