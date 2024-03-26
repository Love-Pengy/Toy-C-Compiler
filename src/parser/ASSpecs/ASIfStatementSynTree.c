//B. Frazier 3/20/24

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

#ifndef STRING
    #define STRING
    #include <string.h>
#endif

//enum expressionType {specifier, funcCall, expr, minus, not} 

//Expression, Statement, Statement?
struct ifStatementTreeType{
    expressionTree exp;
    statementTree ifExpression; 
    statementTree elseExpression;
};

//ifs is required elseS is not (can be passed NULL if it does not exist
ifStatementTree createIfStatementTree(expressionTree expr, statementTree ifS, statementTree elseS){
    ifStatementTree ist = malloc(sizeof(struct ifStatementTreeType));
    ist->exp = expr;
    ist->ifExpression = ifS;
    ist->elseExpression = elseS;
    return(ist);
}

list ifStatementTreeToString(ifStatementTree ist){
    list string = createList();
    listCat(string, "ifState(");
    llistCat(string, expressionTreeToString(ist->exp));
    llistCat(string, statementTreeToString(ist->ifExpression));
    if(ist->elseExpression != NULL){
        llistCat(string, statementTreeToString(ist->elseExpression));
    }
    listCat(string, ")\n");
    return(string);
}

