#ifndef STDBOOL_h
    #include <stdbool.h>
#endif

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
