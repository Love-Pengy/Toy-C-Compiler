//B. Frazier 3/20/24

#include "../../../include/parser/prettyPrinting.h"
#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/ASsynTree.h"
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

//evaluate primitives on their own. For instance if you have if(1) always go inside of the if statement
void generateIfStatementTree(ifStatementTree ist, FILE* fptr){    
    switch(getExpressionType(ist->exp)){
        case funcCall: 
            //skip becasue no functions
            break;
        case Expr: 
            if(ist->elseExpression != NULL){
                //generateIfElseStatement(ist->exp, ist->ifExpression, ist->elseExpression, fptr);
            }
            else{
                //generateIfStatement(ist->exp, ist->ifExpression, fptr);
            }
            break;
        default: 
            break;
    }   

}

