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
    if(exprT == NULL){
    }
    switch(exprT->type){
        case Number:
            fprintf(fptr, "%s%s\n", "iconst_", exprT->number);  
            break;
        case ID:
            fprintf(fptr, "%s%d\n", "iload_", getSymbolIndex(symTable,exprT->id));
            break;
        case CharLiteral:
            //only doing ints
            break;
        case StringLiteral:
            //only doing ints
            break;
        case funcCall:
            //not doing functions
            break;
        case Expr:
            generateOpExpressionTree(exprT->exp);
            break;
        case Minus:
            generateMinusTree(exprT->min);
            break;
        case Not:
            generateNotTree(exprT->not);
            break;
        default:
            printf("internal error\n");
            break;
    }
}

void generateIfStatement(expressionTree operation, statementTree ifStat, FILE* fptr){
    generateExpressionTree(operation, fptr); 
    char* operator;
    switch(getExpressionType(operation)){
        case Expr: 
            //get the operator and slap the needed thingy at the end with the label 
            operator = getOperatorFromTree(operation->exp);
            if(!strcmp(operator, "||")){
                //compare the first one if you get the first one go inside of the statement
                //if first is false check if second is false if it is skip over statement
            }
            else if(!strcmp(operator, "&&")){
                //compare both of them and if either is false go to the next label 
            }
            else if(!strcmp(operator, "<=")){
                //if_icmpgt
            }
            else if(!strcmp(operator, "<")){
                //this can be if_icmplt
            }
            else if(!strcmp(operator, ">")){
                //if_icmple then skip statement 
            }
            else if(!strcmp(operator, ">=")){
                //if_icmplt then skip statemnet 
            }
            else if(!strcmp(operator, "!=")){
                //if_icmpeq
            }
            else{
                printf("ERROR: CHECK OPERATOR\n");
                fflush(stdout);
                exit(EXIT_FAILURE);
            }
        case Number:   
            //if it is not zero then go to the label 
        case ID:    
            //get the value and then if it is not zero go to label 
        case Minus: 
            //if this is not zero then go to label 
        case Not: 
            //if this is 0 go to label 
        default: 
            break;
    }
}
