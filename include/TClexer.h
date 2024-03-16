//B. Frazier 3/16/24
#ifndef STDIO_H
    #include <stdio.h>
#endif
#ifndef TCTOKEN_H
    #include "TCtoken.h"
#endif

char* getLine(void);
token getLexeme(void);
int getLineNum(void);
int getPos(void);
void dumpScannedFile(void);
char* getCurrentLine(void);
