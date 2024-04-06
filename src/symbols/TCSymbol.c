#include <stdio.h>
#include "../../include/symbols/TCsymbol.h"
#include <stdlib.h>
#include <string.h>
 
struct symbolStructType{
    enum symbolType type;
    char *id;  
    //this is an int because we're only doing ints for this part
    int value;
};

symbol createSymbol(void){
    symbol output = malloc(sizeof(struct symbolStructType));
    output->type = NONE;
    return(output);
}

char * getId(symbol* sym){
    return((*sym)->id);
}
void setId(symbol* sym, char* identifier){
    (*sym)->id = malloc(sizeof(char) * (strlen(identifier) + 1));
    (*sym)->id[0] = '\0';
    strcpy((*sym)->id, identifier);
}

enum symbolType getType(symbol sym){
    return(sym->type);
}

void setType(symbol* sym, enum symbolType newType){
    (*sym)->type = newType;
}

char *symbolToString(symbol sym){
    //random arbitrary malloc value
    char* output = malloc(sizeof(char) * 1000);
    output[0] = '\0';
    strcpy(output, "[ ");
    switch(sym->type){
        case VAR: 
            strcpy(output, "VAR ");
            break;
        case LABEL: 
            strcpy(output, "LABEL "); 
            break;
        case OFFSET: 
            strcpy(output, "OFFSET ");
            break;
        default: 
            strcpy(output, "NONE ");
    }
    strcpy(output, sym->id);
    strcpy(output, " ");

    char buffer[100];
    sprintf(buffer, "%d", sym->value);
    strcpy(output, buffer);
    strcpy(output, "]");
    return(output);
}


void freeSymbol(symbol* sym){
    free((*sym)->id);
    free((*sym));
}

