//B. Frazier 3/20/24

#include "../../../include/parser/prettyPrinting.h"
#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/ASsynTree.h"
#include "../../../include/cmdLine/TCglobals.h"
#include "../../../include/symbols/TCSymbolTable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//enum expressionType {specifier, funcCall, expr, minus, not} 

//Expression, Statement, Statement?
struct ifStatementTreeType{
    expressionTree exp;
    statementTree ifExpression; 
    statementTree elseExpression;
};

ifStatementTree initIfStatementTree(void){
    ifStatementTree ist = malloc(sizeof(struct ifStatementTreeType));
    return(ist);
}

//ifs is required elseS is not (can be passed NULL if it does not exist
ifStatementTree createIfStatementTree(expressionTree* expr, statementTree* ifS, statementTree* elseS){
    ifStatementTree ist = initIfStatementTree();
    ist->exp = (*expr);
    ist->ifExpression = (*ifS);
    ist->elseExpression = (*elseS);
    return(ist);
}

list ifStatementTreeToString(ifStatementTree ist){
    list string = createList();
    listCat(&string, spaces());
    listCat(&string, "ifState(\n");
    indent();
    llistCat(&string, expressionTreeToString(ist->exp));
    llistCat(&string, statementTreeToString(ist->ifExpression));
    if(ist->elseExpression != NULL){
        llistCat(&string, statementTreeToString(ist->elseExpression));
    }
    outdent();
    listCat(&string, spaces());
    listCat(&string, ")\n");
    return(string);
}

void generateIfStatementTree(ifStatementTree ist, FILE* fptr){    
    switch(getExpressionType(ist->exp)){
        case funcCall: 
            //skip becasue no functions
            printf("ERROR: Functions Not Allowed\n");
            fflush(stdout);
            exit(EXIT_FAILURE);
            break;

        case Expr: 
            if(ist->elseExpression != NULL){ 
                //CURRENTLABEL + 1 is end CURRENTLABEL is else
                //generateIfElseStatement(ist->exp, ist->ifExpression, ist->elseExpression, fptr);
                generateExpressionTree(ist->exp, fptr);
                fprintf(fptr, "bipush 0\n");
                fprintf(fptr, "%s%d\n", "if_icmpeq Label", CURRENTLABEL);  
                generateStatementTree(ist->ifExpression, fptr);
                fprintf(fptr, "%s%d\n", "goto Label", CURRENTLABEL+1);  
                fprintf(fptr, "%s%d:\n", "Label", CURRENTLABEL); 
                generateStatementTree(ist->elseExpression, fptr);
                fprintf(fptr, "%s%d\n", "goto Label", CURRENTLABEL+1);  
                fprintf(fptr, "Label%d:\n", CURRENTLABEL+1);
                CURRENTLABEL += 2;
            }
            else{
                generateExpressionTree(ist->exp, fptr);
                fprintf(fptr, "bipush 0\n");
                fprintf(fptr, "%s%d\n", "if_icmpeq Label", CURRENTLABEL);  
                generateStatementTree(ist->ifExpression, fptr);
                fprintf(fptr, "%s%d\n", "goto Label", CURRENTLABEL);  
                fprintf(fptr, "%s%d:\n", "Label", CURRENTLABEL);
                CURRENTLABEL++;
            }
            break;
        case ID: 
            generateExpressionTree(ist->exp, fptr);
            fprintf(fptr, "bipush 0\n");
            fprintf(fptr, "%s%d\n", "if_icmpeq Label", CURRENTLABEL);  
            generateStatementTree(ist->ifExpression, fptr);
            fprintf(fptr, "%s%d\n", "goto Label", CURRENTLABEL);  
            fprintf(fptr, "%s%d:\n", "Label", CURRENTLABEL);
            CURRENTLABEL++;
            break;

        default: 
            break;
    }   

}

