//B. Frazier 3/16/24

#ifndef STRING
    #define STRING
    #include <string.h>
#endif

#ifndef TCTOKEN
    #define TCTOKEN
    #include "../../include/lexer/TCtoken.h"
#endif

#ifndef STDLIB
    #define STDLIB
    #include <stdlib.h>
#endif 

#ifndef STDIO
    #define STDIO
    #include <stdio.h>
#endif

struct tokenStruct;

typedef struct tokenStruct *token;

token initToken(void){
    token output = malloc(sizeof(struct tokenStruct));
    return(output);
}
token createToken(char * tokenName, char *string){
    token new = malloc(sizeof(struct tokenStruct));
    new->lexeme = malloc(sizeof(char) * (strlen(tokenName) + 1));
    new->value = malloc(sizeof(char) * (strlen(string) + 1));
    strcpy(new->lexeme, tokenName);
    strcpy(new->value, string);
    return(new);
}

void printToken(token input){
    printf("[SCANNER] (<%s>,\"%s\")\n", input->lexeme, input->value);
}

void freeToken(token f){
    free(f);
}

