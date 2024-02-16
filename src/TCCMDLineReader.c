#include <stdlib.h>
#ifndef STDIO_H
    #include <stdio.h>
#endif
#ifndef TCCMDLINEREADER_H
    #include "TCCmdLineReader.h"


/* 
* if -help is specified then print the help message 
* if -debug <level> then display messages that aid in tracing the compilation process
*   if the number is 0 then display all messages 
*   if the number is 1 then display just scanner messages 
*   these are going to be the same because we just have the scanner 
* if -verbose then display all information
*   verbose does debug but also the source file 
*/
void cmdLineParser(char ** input){
    int arrayLength = -1;
    while(input[++arrayLength] != NULL){    
    }

    for(int i = 1; i < arrayLength; i++){
        switch(input[i]): 
            case "-help":   
                printf("Usage: tc [options] toyc_source_file\n");
                printf("\n where options include:\n");
                printf("    -help             display this usage message\n");
                printf("    -debug <level>    display messages that aid in tracing the compilation process. If level is:\n");             
                printf("                                                                     0 - all messages\n");
                printf("                                                                     1 - scanner messages only\n");
                printf("    -verbose           display all information\n");
                break;
            case "-debug":
                arrayLength++;
                if(input[arrayLength] == 0){
                    //display all messages
                }
                else if(input[arrayLength] == 1){
                    //scanner messages only
                }
                else{
                    printf("debug message error");
                    exit(EXIT_FAILURE);
                }
                break;
            case "-verbose": 
                //display all information and dump source file
                break;
    }
}


#endif
