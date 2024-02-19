#include "../include/TCCMDLineReader.h"
#include <stdlib.h>
#include <stdio.h>
#include "../include/TCglobals.h"
#include "../include/TClexer.h"
#include <ctype.h>
#include <string.h>
int main(int argc, char **argv){

    if(argc < 2){
        printf("Amount of arguments is not correct");
        exit(EXIT_FAILURE);
    }
    cmdLineParser(argv);
    char *currentLine = malloc(sizeof(char) * 501);
    FILE *fp = fopen(inputFileName, "r");
    printf("%s\n", inputFileName);
    if(fp == NULL){
        printf("file does not exist");
        exit(EXIT_FAILURE);
    }
    while((currentLine = getLine(fp))){
        char *buffer = malloc(sizeof(char) * 500);
        for(int i = 0; i < strlen(currentLine); i++){

            if(isspace(currentLine[i])){
                printf("[SCANNER] (<%s>, \"%s\")\n", getLexeme(buffer), buffer);    
                buffer = malloc(sizeof(char) * 500);
            }
            else{
                buffer[strlen(buffer)] = currentLine[i];
            }

            }
        }
    
return(0);
}
//this is the main file
