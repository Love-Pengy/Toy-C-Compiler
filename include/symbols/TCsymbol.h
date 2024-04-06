#include <stdio.h>

#ifndef TCSYMBOL
#define TCSYMBOL

typedef struct symbolStructType* symbol;

enum symbolType {VAR, LABEL, OFFSET, NONE};

symbol createSymbol(void);
void freeSymbol(symbol*);
void setId(symbol*, char*);
void setType(symbol*, enum symbolType);
char *getId(symbol);
enum symbolType getType(symbol);
char *symbolToString(symbol);

//offsets are scope dependent therefore they should not be needed for the first part 
//int getOffset(symbol);
//void setOffset(symbol *, int);


#endif


