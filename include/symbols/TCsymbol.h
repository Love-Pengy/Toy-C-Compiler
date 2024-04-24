#include <stdio.h>

#ifndef TCSYMBOL
#define TCSYMBOL

typedef struct symbolStructType* symbol;

//var is var
//label is function label (what is supposed to be returned)
//RTYPE is the return type of the current scope (there is only going to be one)
//none is the undefined value
enum symbolType {VAR, LABEL, FUNCTION, NONE};

symbol createSymbol(void);
char* getId(symbol);
enum symbolType getSymbolType(symbol);
char* getVarType(symbol);
void freeSymbol(symbol*);
void setId(symbol*, char*);
void setSymbolType(symbol*, enum symbolType);
void setType(symbol*, enum symbolType);
void setVarType(symbol*, char*);
char *getId(symbol);
enum symbolType getType(symbol);
char *symbolToString(symbol);

//offsets are scope dependent therefore they should not be needed for the first part 
//int getOffset(symbol);
//void setOffset(symbol *, int);


#endif


