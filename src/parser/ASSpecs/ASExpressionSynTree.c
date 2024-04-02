//B. Frazier 3/21/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/prettyPrinting.h"
#include "../../../include/parser/ASsynTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct expressionTreeType{
    enum expressionType type;
    union{  
        char* number;
        char* id;
        char* charLit;
        char* string;
        functionCallTree funcC;
        opExpressionTree exp;
        minusTree min;
        notTree not;
    };
};



enum expressionType getExpressionType(expressionTree e){
    return(e->type);
}

expressionTree initExpressionTree(void){
    expressionTree est = malloc(sizeof(struct expressionTreeType));
    est->type = undefinedExpression;
    est->charLit = malloc(sizeof(char) * 100);
    est->charLit[0] = '\0';
    est->number = malloc(sizeof(char) * 100);
    est->number[0]  = '\0';
    est->string = malloc(sizeof(char) * 100);
    est->string[0] = '\0';
    est->id = malloc(sizeof(char) * 500);
    est->id[0] = '\0';
    return(est);
}

expressionTree createExpressionTree(enum expressionType t, void* val){
    expressionTree est = initExpressionTree();
    switch(t){
        case Number:
            strcpy(est->number, (*(char**)val));
            break;
        case ID:
            strcpy(est->id, (*(char**)val));
            break;
        case CharLiteral:
            strcpy(est->charLit, (*(char**)val));
            break;
        case StringLiteral:
            strcpy(est->string, (*(char**)val));
            break;
        case funcCall:
            est->funcC = *(functionCallTree*)val;
            break;
        case Expr:
            est->exp = *(opExpressionTree*)val;
            break;
        case Minus:
            est->min = *(minusTree*)val;
            break;
        case Not:
            est->not = *(notTree*)val;
            break;
        default:
            printf("internal error\n");
            break;
    }
    est->type = t;
    return(est);
}

list expressionTreeToString(expressionTree exprT){
    list string = createList();
    listCat(&string, spaces());
    listCat(&string, "Expression(");
    indent();
    if(exprT == NULL){
        outdent();
        listCat(&string, ")");
        return(string);
    }
    switch(exprT->type){
        case Number:
            listCat(&string, (exprT->number));
            break;
        case ID:
            listCat(&string, (exprT->id));
            break;
        case CharLiteral:
            listCat(&string, (exprT->charLit));
            break;
        case StringLiteral:
            listCat(&string, (exprT->string));
            break;
        case funcCall:
            listCat(&string, "\n");
            llistCat(&string, functionCallTreeToString(exprT->funcC));
            break;
        case Expr:
            listCat(&string, "\n");
            llistCat(&string, opExpressionTreeToString(exprT->exp));
            break;
        case Minus:
            listCat(&string, "\n");
            llistCat(&string, minusTreeToString(exprT->min));
            break;
        case Not:
            listCat(&string, "\n");
            llistCat(&string, notTreeToString(exprT->not));
            break;
        default:
            printf("internal error\n");
            break;
    }
    outdent();
    listCat(&string, ")\n");
    return(string);
}

