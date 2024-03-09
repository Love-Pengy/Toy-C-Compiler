#include "../include/TCCMDLineReader.h"
#include <stdlib.h>
#include <stdio.h>
#include "../include/TCglobals.h"
#include "../include/TClexer.h"
#include <string.h>
int main(int argc, char **argv){
    
    //check if only runner was called 
    if(argc < 2){
        printf("Amount of arguments is not correct");
        exit(EXIT_FAILURE);
    }

    //parse command line flags
    int checker = cmdLineParser(argv);
    FILE *filePointer = fopen(inputFileName, "r");

    if(checker){
        token currentLexeme;
        
        if(filePointer == NULL){
            printf("File does not exist: %s\n", inputFileName);
            exit(EXIT_FAILURE);
        }

        currentLexeme = getLexeme();
        while(currentLexeme == NULL){
            currentLexeme = getLexeme();
        }
        //scanner
        while(strcmp(currentLexeme->lexeme, "EOF")){
            //check if comment
            if(currentLexeme == NULL){
                continue;
            }
            currentLexeme = getLexeme();
            while(currentLexeme == NULL){
                currentLexeme = getLexeme();
            }
        }
    } 
    dumpScannedFile(filePointer);        
        
return(0);
}
//this is the main file
