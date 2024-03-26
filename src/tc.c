//B. Frazier 3/16/24
#include "../include/cmdLine/TCCMDLineReader.h"
#include <stdlib.h>
#include <stdio.h>
#include "../include/cmdLine/TCglobals.h"
#include "../include/lexer/TClexer.h"
#include <string.h>
#include "../include/parser/TCparser.h"
#include "../include/parser/ASsynTree.h"

int main(int argc, char **argv){
    
    //check if only runner was called 
    if(argc < 2){
        printf("Amount of arguments is not correct");
        exit(EXIT_FAILURE);
    }

    //parse command line flags
    cmdLineParser(argv);
    filePointer = fopen(inputFileName, "r");

    
    if(filePointer == NULL){
        printf("File does not exist: %s\n", inputFileName);
        exit(EXIT_FAILURE);
    }

    programTree program = toyCProgram();

    /* just scanner
    token currentLexeme;
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
    */
    return(0);
}
