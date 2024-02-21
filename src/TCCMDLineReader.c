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

/* 
* if -help is specified then print the help message 
* if -debug <level> then display messages that aid in tracing the compilation process
*   if the number is 0 then display all messages 
*   if the number is 1 then display just scanner messages 
*   these are going to be the same because we just have the scanner 
* if -verbose then display all information
*   verbose does debug but also the source file 
*/

int CLINEDEBUG = 0;

void cmdLineParser(char ** input){
    int arrayLength = -1;
    while(input[++arrayLength] != NULL){    
    }

    for(int i = 1; i < arrayLength; i++){
        if(strcmp(input[i], "-help") == 0){   
            printf("Usage: tc [options] toyc_source_file\n");
            printf("\n where options include:\n");
            printf("    -help             display this usage message\n");
            printf("    -debug <level>    display messages that aid in tracing the\n"); 
            printf("                      compilation process. If level is:\n");             
            printf("                         0 - all messages\n");
            printf("                         1 - scanner messages only\n");
            printf("    -verbose           display all information\n");
        }
        else if(strcmp(input[i], "-debug") == 0){
            i++;
            if(i >= arrayLength){
                printf("Debug number not specified\n");
                exit(EXIT_FAILURE);
            }
            if(strcmp(input[i], "0") == 0){
                debug_scanner = true;
                debug_parser = true;
                debug_codeGen = true;
                if(CLINEDEBUG){
                    printf("debug 2 set\n");
                }
                //display all messages
            }
            else if(strcmp(input[i], "1") == 0){
                debug_scanner = true;
                if(CLINEDEBUG){
                    printf("debug 1 set\n");
                }
                //scanner messages only
            }
            else{
                printf("debug number error\n");
                exit(EXIT_FAILURE);
            }
        }
        else if(strcmp(input[i], "-verbose") == 0){ 
            turnVerboseOn();
            if(CLINEDEBUG){
                printf("Verbose Turned On\n");
            }
            //display all information and dump source file
        }
        else{  
            int charCount = 0;
            for(int j = 0; j < strlen(input[i]); j++){
                if(!isspace(input[i][j])){
                    charCount++;
                }
            }
            if(charCount > 0){
                char *cut = strtok(strdup(input[i]), ".");
                char *last = NULL;

                while(cut != NULL){
                    last = cut;
                    cut = strtok(NULL, ".");
                }       
                if(strcmp(last, "tc") == 0){
                    inputFileName = input[i];
                    if(CLINEDEBUG){
                        printf("Input File Set To %s\n", inputFileName);
                    }
                }
                else{
                    printf("Invalid argument passed\n");
                }
            }
            else{
                printf("filename not specified correctly\n");
                exit(EXIT_FAILURE);
            }
    }
}
}


