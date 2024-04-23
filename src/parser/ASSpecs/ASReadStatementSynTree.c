//B. Frazier 3/21/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/ASsynTree.h"
#include "../../../include/parser/prettyPrinting.h"
#include "../../../include/cmdLine/TCglobals.h"
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
    listCat(&string, spaces());
    listCat(&string, "readState(");
    indent();
    for(int i = 0; i < rs->numIds; i++){
        if((!(i == 0)) && (1 != (rs->numIds - 2))){
            listCat(&string, ", ");
        }
        listCat(&string, rs->ids[i]);
    }
    outdent();
    listCat(&string, ")\n");
    return(string);
}

//this is assumed to be the scanner
void generateReadStatement(readStatementTree rs, FILE* fptr){
    int index;
    int index2;

    //initializing 
    fprintf(fptr, "%s\n", "new java/util/Scanner");
    fprintf(fptr, "%s\n", "dup");
    fprintf(fptr, "%s\n", "getstatic java/lang/System/in Ljava/io/InputStream;");
    fprintf(fptr, "%s\n", "invokespecial java/util/Scanner/<init>(Ljava/io/InputStream;)V");
    //this is the reference to the object
    index = getSymbolTableSize(symTable);
    if(index > 3){
        fprintf(fptr, "%s%d\n", "astore ", getSymbolTableSize(symTable));
    }
    else{
        fprintf(fptr, "%s%d\n", "astore_", getSymbolTableSize(symTable));
    }
    
    for(int i = 0; i < rs->numIds; i++){

        if(index > 3){
            fprintf(fptr, "%s%d\n", "aload ", getSymbolTableSize(symTable));
        }
        else{
            fprintf(fptr, "%s%d\n", "aload_", getSymbolTableSize(symTable));
        }
        
        fprintf(fptr, "%s\n", "invokevirtual java/util/Scanner/nextInt()I");    
        
        index2 = getSymbolIndex(symTable, rs->ids[i]);

        if(index2 > 3){
            fprintf(fptr, "%s%d\n", "istore ", getSymbolIndex(symTable, rs->ids[i]));
        }
        else{
            fprintf(fptr, "%s%d\n", "istore_", getSymbolIndex(symTable, rs->ids[i]));
        }

    }
}
