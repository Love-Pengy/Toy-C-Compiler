//B. Frazier 3/21/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/ASsynTree.h"
#include <stdlib.h>
#include <string.h>


struct readStatementTreeType{
    //one or more
    char** ids;
    int numIds;
};

readStatementTree initReadStatementTree(void){
    readStatementTree rst = malloc(sizeof(struct readStatementTreeType));
    rst->numIds = 0;
    rst->ids = malloc(sizeof(char*) * 100);

    for(int i = 0; i < 100; i++){
        rst->ids[i] = malloc(sizeof(char) * 200); 
    }

    return(rst);
}

void addIdReadStatement(readStatementTree * rst, char *id){
    (*rst)->ids[(*rst)->numIds] = malloc(sizeof(char) * (strlen(id) + 1));
    strcpy((*rst)->ids[(*rst)->numIds], id);
    (*rst)->numIds++;
}

readStatementTree createReadStatementTree(char** identifiers, int idAmt){
    readStatementTree rst = malloc(sizeof(struct readStatementTreeType));
    rst->ids = malloc(sizeof(identifiers));
    rst->ids = identifiers;
    rst->numIds = idAmt;
    return(rst);
}

list readStatementTreeToString(readStatementTree rs){
    list string = createList();
    listCat(&string, "readState(");

    for(int i = 0; i < rs->numIds; i++){
        listCat(&string, rs->ids[i]);
    }

    listCat(&string, ")\n");
    return(string);
}

