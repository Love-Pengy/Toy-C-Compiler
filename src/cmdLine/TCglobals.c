//B. Frazier 3/16/24

#include <stdbool.h>
#include "../../include/cmdLine/TCglobals.h"
#include "../../include/symbols/TCSymbolTable.h"

char *inputFileName = "";
bool debug_scanner = false;
bool debug_parser = false;
bool debug_codeGen = false;
bool dump_abstractCode = false;
bool dump_objectCode = false;
bool dump_symbolTable = false;
bool verbose = false;
char *author = "Brandon Frazier";
char *outputFileName = "";
FILE* filePointer = NULL;
symbolTable symTable = NULL; 
char* TAB = "    ";
int TOPVARIABLE = 0;
int STACKSIZE = 1000;
int CURRENTLABEL = 1;  

void turnVerboseOn(){
      debug_scanner = true;
      debug_parser = true;
      debug_codeGen = true;
      dump_abstractCode = true;
      dump_objectCode = true;
      dump_symbolTable = true;
      verbose = true;
}    

void turnVerboseOff(){
      debug_scanner = false;
      debug_parser = false;
      debug_codeGen = false;
      dump_abstractCode = false;
      dump_objectCode = false;
      dump_symbolTable = false;
      verbose = false;

}



