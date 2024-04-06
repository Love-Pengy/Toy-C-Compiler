#include <stdio.h>
#include "../../include/symbols/TCsymbol.h"
#ifndef TCSYMBOLTABLE
#define TCSYMBOLTABLE

typedef struct symbolTableTypeStruct* symbolTable;

symbolTable createSymbolTable(void);
int addSymbol(symbolTable*, symbol*);
//for getting the offset of a symbol
//int findSymbol(symbolTable*, char*);
//for getting the value of a symbol
//symbol* findSymbol(symbolTable*, symbol*);
symbol* getSymbol(symbolTable*, symbol*);
char * symbolTableToString(symbolTable);
void freeSymbolTable(symbolTable*);

#endif
