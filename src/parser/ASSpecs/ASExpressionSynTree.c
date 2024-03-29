//B. Frazier 3/21/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/ASsynTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct expressionTreeType{
    enum expressionType type;
    union{  
        char * number;
        char * id;
        char * charLit;
        char * string;
        functionCallTree funcC;
        opExpressionTree exp;
        minusTree min;
        notTree not;
    };
};


expressionTree initExpressionTree(void){
    expressionTree est = malloc(sizeof(struct expressionTreeType));
    return(est);
}

expressionTree createExpressionTree(enum expressionType t, void* val){
    expressionTree est = initExpressionTree();
    switch(t){
        case Number:
            est->number = malloc(sizeof(char) * strlen((char*)val) + 1);
            strcpy(est->number, (char*)val);
            break;
        case ID:
            est->id = malloc(sizeof(char) * strlen((char*)val) + 1);
            strcpy(est->id, (char*)val);
            break;
        case CharLiteral:
            est->charLit = malloc(sizeof(char) * strlen((char*)val) + 1);
            strcpy(est->charLit, (char*)val);
            break;
        case StringLiteral:
            est->string = malloc(sizeof(char) * strlen((char*)val) + 1);
            strcpy(est->string, (char*)val);
            break;
        case funcCall:
            est->funcC = (functionCallTree)val;
            break;
        case Expr:
            est->exp = (opExpressionTree)val;
            break;
        case Minus:
            est->min = (minusTree)val;
            break;
        case Not:
            est->not = (notTree)val;
            break;
        default:
            printf("internal error\n");
            break;
    }
    return(est);
}

list expressionTreeToString(expressionTree exprT){
    list string = createList();
    listCat(string, "Expression(");
    switch(exprT->type){
        case Number:
            listCat(string, (exprT->number));
            break;
        case ID:
            listCat(string, (exprT->id));
            break;
        case CharLiteral:
            listCat(string, (exprT->charLit));
            break;
        case StringLiteral:
            listCat(string, (exprT->string));
            break;
        case funcCall:
            llistCat(string, functionCallTreeToString(exprT->funcC));
            break;
        case Expr:
            llistCat(string, opExpressionTreeToString(exprT->exp));
            break;
        case Minus:
            llistCat(string, minusTreeToString(exprT->min));
            break;
        case Not:
            llistCat(string, notTreeToString(exprT->not));
            break;
        default:
            printf("internal error\n");
            break;
    }
    listCat(string, ")\n");
    return(string);
}

