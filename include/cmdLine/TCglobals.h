//B. Frazier 3/16/24

#include <stdbool.h>
#include <stdio.h>
#include "../../include/symbols/TCSymbolTable.h"

#ifndef TCGLOBALS
#define TCGLOBALS

void turnVerboseOn(void);
void turnVerboseOff(void);
extern bool debug_scanner;
extern bool debug_parser;
extern bool debug_codeGen;
extern bool dump_abstractCode;
extern bool dump_objectCode;
extern bool dump_symbolTable;
extern bool verbose;
extern char *inputFileName;
extern char *author;
extern char *outputFileName;
extern FILE *filePointer;
extern symbolTable symTable;
extern char* TAB;
extern int TOPVARIABLE;
extern int STACKSIZE;
extern int CURRENTLABEL;  
extern char* javaClassname; 

#endif
