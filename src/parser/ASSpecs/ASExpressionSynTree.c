//B. Frazier 3/21/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/prettyPrinting.h"
#include "../../../include/parser/ASsynTree.h"
#include "../../../include/cmdLine/TCglobals.h"
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

int getIdIndexFromExpression(expressionTree et){
    return(getSymbolIndex(symTable, et->id));
}

char* getStringFromExpression(expressionTree et){

    char* newString = malloc(sizeof(char) * strlen(et->string));
    newString[0] = '\0';

    //get rid of "'s because for some reason I didn't take them out 
    for(int i = 0; i < strlen(et->string); i++){
        if(et->string[i] != '\"'){
            if(strlen(newString) == 0){
                newString[0] = et->string[i]; 
                newString[strlen(newString)] = '\0'; 
                continue;
            }
            newString[strlen(newString)] = et->string[i]; 
            newString[(strlen(newString) + 1)] = '\0';
        }
    }

    return(newString);
}

char* getCharFromExpression(expressionTree et){

    char * newString = malloc(sizeof(char) * strlen(et->charLit));
    newString[0] = '\0';

    for(int i = 0; i < strlen(et->charLit); i++){
        if(et->charLit[i] != '\''){
            if(strlen(newString) == 0){
                newString[0] = et->charLit[i]; 
                newString[strlen(newString)] = '\0'; 
                continue;
            }
            newString[strlen(newString)] = et->charLit[i]; 
            newString[(strlen(newString) + 1)] = '\0';
        }
    }

    return(newString);
}

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
        listCat(&string, ")\n");
        return(string);
    }
    switch(exprT->type){
        case Number:
            listCat(&string, (exprT->number));
            listCat(&string, ")\n");
            outdent();
            return(string);
            break;
        case ID:
            listCat(&string, (exprT->id));
            listCat(&string, ")\n");
            outdent();
            return(string);
            break;
        case CharLiteral:
            listCat(&string, (exprT->charLit));
            listCat(&string, ")\n");
            outdent();
            return(string);
            break;
        case StringLiteral:
            listCat(&string, (exprT->string));
            listCat(&string, ")\n");
            outdent();
            return(string);
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
    listCat(&string, spaces());
    listCat(&string, ")\n");
    return(string);
}

void generateExpressionTree(expressionTree exprT, FILE* fptr){

    if(debug_codeGen){
        printf("[CODE GENERATOR] Generating Expression\n");
        fflush(stdout);
    }

    int index;
    if(exprT == NULL){
    }
    switch(exprT->type){
        case Number:
            if(atoi(exprT->number) > 255){
                fprintf(fptr, "%s%s\n", "ldc_w ", exprT->number);  
            }
            else{
                fprintf(fptr, "%s%s\n", "bipush ", exprT->number);  
            }
            break;
        case ID:
            index = getSymbolIndex(symTable, exprT->id);
            if(index > 3){
                fprintf(fptr, "%s%d\n", "iload ", getSymbolIndex(symTable,exprT->id));    
            }
            else {
                fprintf(fptr, "%s%d\n", "iload_", getSymbolIndex(symTable,exprT->id));
            }
            break;
        case CharLiteral:
            //only doing ints
            break;
        case StringLiteral:
            //only doing ints
            break;
        case funcCall:
            //not doing functions
            printf("ERROR: Functions Not Allowed\n");
            fflush(stdout);
            exit(EXIT_FAILURE);
            break;
        case Expr:
            generateOpExpressionTree(exprT->exp, fptr);
            break;
        case Minus:
            generateMinusTree(exprT->min, fptr);
            break;
        case Not:
            generateNotTree(exprT->not, fptr);
            break;
        default:
            printf("internal error\n");
            break;
    }
}




