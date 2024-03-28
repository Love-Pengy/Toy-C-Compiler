//B. Frazier 3/21/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/ASsynTree.h"
#include <stdlib.h>
#include <stdio.h>

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

statementTree initStatementTree(void){
    statementTree st = malloc(sizeof(struct statementTreeType));
    return(st);
}

void addExprStateStatementTree(statementTree* st, expressionStatementTree e){
    (*st)->type = exprState;
    (*st)->exp = e;
}

void addBreakStateStatementTree(statementTree* st, breakStatementTree b){
    (*st)->type = breakState;
    (*st)->bst = b;
}

void addBlockStateStatementTree(statementTree* st, blockStatementTree b){
    (*st)->type = blockState;
    (*st)->blt = b;
}
    
void addIfStateStatementTree(statementTree* st, ifStatementTree i){
    (*st)->type = ifState;
    (*st)->ist = i;
}

void addNullStateStatementTree(statementTree* st, nullStatementTree n){
    (*st)->type = nullState;
    (*st)->nst = n;
}

void addReturnStateStatementTree(statementTree* st, returnStatementTree r){
    (*st)->type = returnState;
    (*st)->rst = r;
}

void addWhileStateStatementTree(statementTree* st, whileStatementTree w){
    (*st)->type = whileState;
    (*st)->wst = w;
}

void addWriteStateStatementTree(statementTree* st, writeStatementTree w){
    (*st)->type = writeState;
    (*st)->author = w;
}

void addNewlineStateStatementTree(statementTree* st, newLineStatementTree n){
    (*st)->type = newLineState;
    (*st)->nlst = n;
}

void addReadStateStatementTree(statementTree* st, readStatementTree r){
    (*st)->type = readState;
    (*st)->book = r;
}

statementTree createStatementTree(enum statementType t, void* val){
    statementTree st = initStatementTree();
    switch(t){
        case exprState:
            st->exp = (expressionStatementTree)val;
            break;
        case breakState:
            st->bst = (breakStatementTree)val;
            break;
        case blockState:
            st->blt = (blockStatementTree)val;
            break;
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
    return(st);
}

list statementTreeToString(statementTree state){
    list string = createList();
    listCat(&string, "Statement(");
    switch(state->type){
        case exprState:
            llistCat(&string, expressionStatementTreeToString(state->exp));
            break;
        case breakState:
            llistCat(&string, breakStatementTreeToString(state->bst));
            break;
        case blockState:
            llistCat(&string, blockStatementTreeToString(state->blt));
            break;
        case ifState:
            llistCat(&string, ifStatementTreeToString(state->ist));
            break;
        case nullState:
            llistCat(&string, nullStatementTreeToString(state->nst));
            break;
        case returnState:
            llistCat(&string, returnStatementTreeToString(state->rst));
            break;
        case whileState:
            llistCat(&string, whileStatementTreeToString(state->wst));
            break;
        case readState:
            llistCat(&string, readStatementTreeToString(state->book));
            break;
        case writeState:
            llistCat(&string, writeStatementTreeToString(state->author));
            break;
        case newLineState:
            llistCat(&string, newLineStatementTreeToString(state->nlst));
            break;
        default:
            printf("internal error\n");
            break;
    }
    listCat(&string, ")\n");
    return(string);
}

