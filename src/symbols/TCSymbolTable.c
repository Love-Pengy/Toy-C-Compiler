#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/symbols/TCsymbol.h"
#include "../../include/symbols/TCSymbolTable.h"
#include "../../lib/dynamicArray/dynamicArray.h"
#define MAXSYMBOLS 1000

struct symbolTableTypeStruct{
    symbol* symbols;
    int amountSymbols;
};

symbolTable createSymbolTable(void){
    symbolTable output = malloc(sizeof(struct symbolTableTypeStruct));
    output->amountSymbols = 0;
    output->symbols = malloc(sizeof(symbol) * MAXSYMBOLS);
    return(output);
}

//1 if symbol didnt already exist, 0 if it did 
int addSymbol(symbolTable* symTab, symbol* sym){
    if(getSymbol(symTab, sym) == NULL){
        (*symTab)->symbols[(*symTab)->amountSymbols] = (*sym);
        (*symTab)->amountSymbols++;
        return(1);
    }
    return(0);
}

//for getting the offset of a symbol
//int findSymbol(symbolTable*, char*);
//for getting the value of a symbol
//symbol* findSymbol(symbolTable*, symbol*);
symbol* getSymbol(symbolTable* symTable, symbol* sym){
    for(int i = 0; i < (*symTable)->amountSymbols; i++){
        if(!strcmp(getId(((*symTable)->symbols[i])), getId((*sym)))){
            return((*symTable)->symbols);
        }
    }
    return(NULL);
}

char * symbolTableToString(symbolTable symTP){
    list output = createList(); 
    listCat(&output, "{");

    for(int i = 0; i < symTP->amountSymbols; i++){
        listCat(&output, symbolToString(symTP->symbols[i]));
        if(i != (symTP->amountSymbols - 1)){
            listCat(&output, " ");
        }
        
    }
    listCat(&output, "}\n");
    return(listToString(output));
}

void freeSymbolTable(symbolTable* symTP){
    symbol * currentSymbol; 
    for(int i = 0; i < (*symTP)->amountSymbols; i++){
        currentSymbol = &((*symTP)->symbols[i]);
        freeSymbol(currentSymbol);
    } 
    free((*symTP));
}
