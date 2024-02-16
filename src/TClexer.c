#ifndef TCLEXER_H
    #define TCLEXER_H

#include "TCtoken.h"


//gets raw string
char *getLine();
//get the sequence of characters that we're lookiung for (or error ig)
char *getLexeme();
int getLineNum();
int getPos();


#endif
