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



struct returnStatementTreeType{
    expressionTree exp;
};

returnStatementTree createReturnStatementTree(expressionTree ex){
    returnStatementTree rst = malloc(sizeof(struct returnStatementTreeType));

    if(ex != NULL){
        rst->exp = ex;
    }
    else{
        rst->exp = NULL;
    }

    return(rst);

}

list returnStatementTreeToString(returnStatementTree rsi){
    list string = createList();
    listCat(string, "returnState(");
    llistCat(string, expressionTreeToString(rsi->exp));
    listCat(string, ")\n");
    return(string);
}

