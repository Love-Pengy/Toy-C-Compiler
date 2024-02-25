#ifndef STDIO_H
    #include <stdio.h>
#endif
#ifndef TCTOKEN_H
    #include "TCtoken.h"
#endif

char* getLine(FILE*);
token getLexeme(FILE*);
int getLineNum(void);
int getPos(void);
void dumpScannedFile(FILE*);
