#include "../../include/parser/ASsynTree.h"
#include <stdlib.h>
#include <string.h>
#include "../../include/cmdLine/TCglobals.h"

//traverse the AST and convert each part to its respective instructions
//for each tree implement a "generate code" function the implements its respective template
void generateJasminCode(programTree program){ 
    char* cut = strtok(inputFileName, ".");
    char* last = NULL;
    while(cut != NULL){
        last = cut;
        cut = strtok(NULL, ".");
    }       
    
    char* newInputFile = NULL;
    if(strlen(last) == strlen(inputFileName)){
        newInputFile = malloc(sizeof(char) * (strlen(inputFileName) + 2));
        newInputFile[0] = '\0';
        strcpy(newInputFile, inputFileName);
        strcat(newInputFile, ".j");
    }
    else{
        int extSize = strlen(last); 
        newInputFile = malloc(sizeof(char) * ((strlen(inputFileName) - extSize) + 2));
        newInputFile[0] = '\0';
        
        for(int i = 0; i < (strlen(inputFileName) - extSize); i++){
            newInputFile[i] = inputFileName[i];
            newInputFile[i+1] = '\0';
        }
        strcat(newInputFile, ".j");
    }

    FILE* fptr = fopen(newInputFile, "w");


    generateProgramTree(fptr);
}
