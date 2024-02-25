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
    FILE *fp = fopen(inputFileName, "r");

    if(checker){
        token currentLexeme;
        
        if(fp == NULL){
            printf("File does not exist: %s\n", inputFileName);
            exit(EXIT_FAILURE);
        }

        currentLexeme = getLexeme(fp);
        while(currentLexeme == NULL){
            currentLexeme = getLexeme(fp);
        }
        //scanner
        while(strcmp(currentLexeme->lexeme, "EOF")){
            //check if comment
            if(currentLexeme == NULL){
                continue;
            }
            currentLexeme = getLexeme(fp);
            while(currentLexeme == NULL){
                currentLexeme = getLexeme(fp);
            }
        }
    } 
    dumpScannedFile(fp);        
        
return(0);
}
//this is the main file
