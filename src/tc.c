//B. Frazier 3/16/24

#include "../include/cmdLine/TCCMDLineReader.h"
#include <stdlib.h>
#include <stdio.h>
#include "../include/cmdLine/TCglobals.h"
#include "../include/lexer/TClexer.h"
#include <string.h>
#include "../include/parser/TCparser.h"
#include "../include/parser/ASsynTree.h"
#include "../include/codeGeneration/CGCodeGenerator.h"

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

    if(dump_abstractCode){
        printf("%s\n", listToString(programTreeToString(program)));
    }

    if(dump_symbolTable){
        printf("%s\n", symbolTableToString(symTable)); 
    }

    generateJasminCode(program);
    
    if(dump_objectCode){
        FILE* fptr = fopen(outputFileName, "r");
        while(!feof(fptr)){
            printf("%c", fgetc(fptr));  
        }
        fclose(fptr);
    }

    return(0);
}
