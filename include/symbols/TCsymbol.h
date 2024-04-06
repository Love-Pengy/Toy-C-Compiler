#include <stdio.h>

#ifndef TCSYMBOL
#define TCSYMBOL

typedef struct symbolStructType* symbol;

enum symbolType {VAR, LABEL, OFFSET, NONE};

char *getId(symbol*);
void setId(symbol*, char*);
enum symbolType getType(symbol);
void setType(symbol*, enum symbolType);
char *symbolToString(symbol);
void freeSymbol(symbol*);

//offsets are scope dependent therefore they should not be needed for the first part 
//int getOffset(symbol);
//void setOffset(symbol *, int);


#endif


