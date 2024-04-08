#include "../../include/symbols/TCsymbol.h"
#include <stdlib.h>
#include <string.h>
#include "../../lib/dynamicArray/dynamicArray.h"
struct symbolStructType{
    enum symbolType type;
    char* varType;
    char* id;  
};

symbol createSymbol(void){
    symbol output = malloc(sizeof(struct symbolStructType));
    output->type = NONE;
    return(output);
}

char * getId(symbol sym){
    return(sym->id);
}
void setId(symbol* sym, char* identifier){
    (*sym)->id = malloc(sizeof(char) * (strlen(identifier) + 1));
    (*sym)->id[0] = '\0';
    strcpy((*sym)->id, identifier);
}

enum symbolType getSymbolType(symbol sym){
    return(sym->type);
}

void setSymbolType(symbol* sym, enum symbolType newType){
    (*sym)->type = newType;
}

char* getVarType(symbol sym){
    return(sym->varType);
}

void setVarType(symbol* sym, char* vType){
    (*sym)->varType = malloc(sizeof(char) * (strlen(vType) + 1));
    strcpy((*sym)->varType, vType);
}

char *symbolToString(symbol sym){
    list output = createList();
    if(sym->type == NONE){
        return("[]\n");
    }

    listCat(&output, "[");
    switch(sym->type){
        case VAR: 
            listCat(&output, "VAR, ");
            break;
        case LABEL: 
            listCat(&output, "LABEL, "); 
            break;
        case RTYPE: 
            listCat(&output, "RTYPE, ");
            break;
        default: 
            listCat(&output, "NONE, ");
    }
    listCat(&output, sym->varType);
    listCat(&output, ", ");
    listCat(&output, sym->id);
    listCat(&output, "]");
    return(listToString(output));
}


void freeSymbol(symbol* sym){
    free((*sym)->id);
    free((*sym));
}

