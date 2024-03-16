//B. Frazier 


#ifndef STDLIB_H
    #include <stdlib.h>
#endif
#ifndef STDIO_H
    #include <stdio.h>
#endif
#ifndef TCCMDLINEREADER_H
    #include "../include/TCCMDLineReader.h"
#endif
#ifndef STRING_H
    #include <string.h>
#endif
#ifndef CTYPE_H
    #include <ctype.h>
#endif
#ifndef TCGLOBALS_H 
    #include "../include/TCglobals.h"
#endif
#ifndef STDBOOL_H
    #include <stdbool.h>
#endif


int CLINEDEBUG = 0;


void throwCmdLineError(char* error){
    printf("ERROR: %s\n", error);
    fflush(stdout);
    exit(EXIT_FAILURE);
}


void cmdLineParser(char ** input){
    int arrayLength = -1;
    bool fileSpecified = false;
    while(input[++arrayLength] != NULL){    
    }
    
    for(int i = 1; i < arrayLength; i++){
        if(strcmp(input[i], "-help") == 0){   
            printf("Usage: tc [options] toyc_source_file\n");
            printf("\n where options include:\n");
            printf("    -help             display this usage message\n");
            printf("    -output <file>    specifies target file name\n");
            printf("    -class  <file>    specifies class file name\n");
            printf("    -debug <level>    display messages that aid in tracing the\n"); 
            printf("                      compilation process. If level is:\n");             
            printf("                         0 - all messages\n");
            printf("                         1 - scanner messages only\n");
            printf("                         2 - parser messages only\n");
            printf("                         3 - code generation messages only\n");
            printf("    -abstract         dump the abstract syntax tree\n");
            printf("    -symbol           dump the symbol table\n");
            printf("    -code             dump the generated program\n");
            printf("    -verbose          display all information\n");
            printf("    -version          display program version\n");
            exit(EXIT_SUCCESS);
        }
        else if(strcmp(input[i], "-debug") == 0){
            i++;
            if(i >= arrayLength){
                throwCmdLineError("Debug Number Not Specified");
            }
            //display all messages
            if(strcmp(input[i], "0") == 0){
                debug_scanner = true;
                debug_parser = true;
                if(CLINEDEBUG){
                    printf("Debug 0 Set\n");
                }
            }
            //scanner messages only
            else if(strcmp(input[i], "1") == 0){
                debug_scanner = true;
                if(CLINEDEBUG){
                    printf("Debug 1 Set\n");
                }
            }
            //parser messages only 
            else if(strcmp(input[i], "2") == 0){
                debug_parser = true;
                if(CLINEDEBUG){
                    printf("Debug 2 Set\n");
                }
            }
            //code generation messages only 
            else if (strcmp(input[i], "3") == 0){ 
               debug_codeGen = true; 
                if(CLINEDEBUG){
                    printf("Debug 3 Set\n");
                }
            }
            else{
                throwCmdLineError("Debug Number Not Specified");
            }
        }
        else if(strcmp(input[i], "-output") == 0){
            if((i + 1) < arrayLength){
                i++;
                strcpy(inputFileName, input[i]);
            }
            //case for when there are no more left
            else{
                throwCmdLineError("Output File Not Specified");
            }
        }
        else if(strcmp(input[i], "-abstract") == 0){
            dump_abstractCode = true;
        }
        else if(strcmp(input[i], "-symbol") == 0){
            dump_symbolTable = true;
        }
        else if(strcmp(input[i], "-code") == 0){
            dump_objectCode = true;
        }
        else if(strcmp(input[i], "-version") == 0){
            printf("Toy C Compiler 1.0.0\n          Created By Brandon Frazier\n");
        }
        else if(strcmp(input[i], "-verbose") == 0){ 
            turnVerboseOn();
            if(CLINEDEBUG){
                printf("Verbose Turned On\n");
            }
            //display all information and dump source file
        }
        else{  
            if(fileSpecified){
                throwCmdLineError("Multiple Files Specified");
            }
            else{
                inputFileName = input[i]; 
                fileSpecified = true;
            }
        }
    }
}


