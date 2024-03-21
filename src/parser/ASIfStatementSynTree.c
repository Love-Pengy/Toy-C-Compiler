//B. Frazier 3/20/24

#ifndef DYNAMICARRAY
    #define DYNAMICARRAY
    #include "../../lib/dynamicArray/dynamicArray.h"
#endif

#ifndef ASSYNTREE
    #define ASSYNTREE
    #include "../../include/parser/ASsynTree.h"
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
    enum expressionTypeEnum type;
    union{
        char *specifier; 
        functionCallTree fct;
        expressionTree ext;
        minusTree min;
        notTree nt;
    };
    char * ifExpression; 
    char * elseExpression;
};

ifStatementTree createIfStatementTree(enum expressionTypeEnum t, void* expression, char*stat1, char*stat2){
    ifStatementTree ist = malloc(sizeof(struct ifStatementTreeType));
    ist->type = t;
    switch(t){
        case Specifier: 
            ist->specifier = malloc(sizeof(expression) +1);
            strcpy(ist->specifier, (char*)expression);
            break;
        case FuncCall:
            ist->fct = (functionCallTree)expression;
            break;
        case Expr: 
            ist->ext = (char*)expression;
            break;
        case Minus: 
            ist->min = (minusTree)expression;
            break;
        case Not:
            ist->nt = (notTree)expression;
            break;
        case default:  
            printf("Internal Error\n");
    }
    ist->ifExpression = malloc(sizeof(char) * (strlen(stat1) + 1));
    strcpy(ist->ifExpression, stat1);

    if(stat2 != NULL){
        ist->elseExpression = malloc(sizeof(char) * (strlen(stat2) + 1));
        strcpy(ist->elseExpression, stat2);
    }
    else{
        ist->elseExpression = NULL;
    }

    return(ist);

}

list ifStatementTreeToString(ifStatementTree ist){
    list string = createList();
    listCat(string, "ifState(");
    switch(ist->type){
        case Specifier: 
            listCat(string, ist->specifier);
            break;
        case FuncCall:
            listCat(string, functionCallTreeToString(ist->fct));
            break;
        case Expr: 
            listCat(string, expressionTypeTreeToString(ist->ext));
            break;
        case Minus: 
            listCat(string, minusTreeToString(ist->min));
            break;
        case Not:
            listCat(string, notTreeToString(ist->nt));
            break;
        case default:  
            printf("Internal Error\n");
            break;
    }
    listCat(string, ist->ifExpression);
    if(ist->elseExpression != NULL){
        listCat(string, ist->elseExpression);
    }
    listCat(string, ")\n");
    return(string);
}

