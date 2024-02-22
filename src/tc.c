#include "../include/TCCMDLineReader.h"
#include <stdlib.h>
#include <stdio.h>
#include "../include/TCglobals.h"
#include "../include/TClexer.h"
#include <ctype.h>
#include <string.h>
int main(int argc, char **argv){
    
    //check if only runner was called 
    if(argc < 2){
        printf("Amount of arguments is not correct");
        exit(EXIT_FAILURE);
    }

    //parse command line flags
    int checker = cmdLineParser(argv);
    FILE *fp = fopen(inputFileName, "r");

    if(checker){
        char * currentLexeme = malloc(sizeof(char) * 501);
        

        if(fp == NULL){
            printf("File does not exist: %s\n", inputFileName);
            exit(EXIT_FAILURE);
        }


        //scanner
        while(strcmp((currentLexeme = getLexeme(fp)), "<EOF>, \"EOF\"")){
            //check if comment
            if(!strcmp(currentLexeme, " ")){
                continue;
            }
            if(debug_scanner){
                printf("%s\n", currentLexeme);
            }
        }
    } 
    dumpScannedFile(fp);        
        
return(0);
}
//this is the main file
