//B. Frazier 3/16/24

#include <stdio.h>
#include "TCtoken.h"

#ifndef TCLEXER
#define TCLEXER

char* getLine(void);
token getLexeme(void);
int getLineNum(void);
int getPos(void);
void dumpScannedFile(void);
char* getCurrentLine(void);

#endif
