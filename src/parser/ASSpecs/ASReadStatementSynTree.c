//B. Frazier 3/21/24

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



struct readStatementTreeType{
    //one or more
    char** ids;
    int numIds;
};


readStatementTree createReadStatementTree(char** identifiers, int idAmt){
    readStatementTree rst = malloc(sizeof(struct readStatementTreeType));
    rst->ids = malloc(sizeof(identifiers));
    rst->ids = identifiers;
    rst->numIds = idAmt;
    return(rst);
}

list readStatementToString(readStatementTree rs){
    list string = createList();
    listCat(string, "readState(");

    for(int i = 0; i < rs->numIds; i++){
        listCat(string, rs->ids[i]);
    }

    listCat(string, ")\n");
    return(string);
}

