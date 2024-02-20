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
    cmdLineParser(argv);



    char *currentLine = malloc(sizeof(char) * 501);
    FILE *fp = fopen(inputFileName, "r");
    

    if(fp == NULL){
        printf("file does not exist");
        exit(EXIT_FAILURE);
    }


    //scanner
    while(1){
        currentLine = getLine(fp);
        if(currentLine == NULL){
            if(debug_scanner){
                printf("[SCANNER] (<EOF>, \"EOF\")\n");    
            }
            break;
        }
        char *buffer = malloc(sizeof(char) * 500);
        char *lexeme = malloc(sizeof(char) * 500);
        for(int i = 0; i < strlen(currentLine); i++){
            if(isspace(currentLine[i])){
                strcpy(lexeme, getLexeme(buffer));
                if(debug_scanner){
                    printf("[SCANNER] (<%s>, \"%s\")\n",lexeme , buffer);    
                }
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
