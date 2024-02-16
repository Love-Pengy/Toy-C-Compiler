#ifndef STDBOOL_h
    #include <stdbool.h>
#endif


extern string AUTHOR = "Brandon Frazier";
extern string VERSION;
extern char *inputFileName;
extern bool debug_scanner;
extern bool debug_parser;
extern bool debug_codeGen;
extern bool dump_abstractCode;
extern bool dump_objectCode;
extern bool dump_symbolTable;
extern bool verbose;

void turnVerboseOn();
void turnVerboseOff();


