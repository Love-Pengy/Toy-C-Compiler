//B. Frazier 3/16/24

#ifndef STDIO
    #define STDIO
    #include <stdio.h>
#endif

#ifndef TCTOKEN
    #define TCTOKEN
    #include "TCtoken.h"
#endif

char* getLine(void);
token getLexeme(void);
int getLineNum(void);
int getPos(void);
void dumpScannedFile(void);
char* getCurrentLine(void);
