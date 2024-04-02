//B. Frazier 3/20/24

#include "../../../include/parser/prettyPrinting.h"
#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/ASsynTree.h"
#include <stdlib.h>



struct returnStatementTreeType{
    expressionTree exp;
};

returnStatementTree initReturnStatementTree(void){
    returnStatementTree rst = malloc(sizeof(struct returnStatementTreeType));
    rst->exp = NULL;
    return(rst);
}

returnStatementTree createReturnStatementTree(expressionTree* ex){
    returnStatementTree rst = initReturnStatementTree();

    if(ex != NULL){
        rst->exp = (*ex);
    }
    else{
        rst->exp = NULL;
    }

    return(rst);

}

list returnStatementTreeToString(returnStatementTree rsi){
    list string = createList();
    listCat(&string, spaces());
    listCat(&string, "returnState(\n");
    indent();
    llistCat(&string, expressionTreeToString(rsi->exp));
    outdent();
    listCat(&string, spaces());
    listCat(&string, ")\n");
    return(string);
}

