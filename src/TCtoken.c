#ifndef STRING_H
    #include <string.h>
#endif
#ifndef TCTOKEN_H
    #include "../include/TCtoken.h"
#endif
#ifndef STDLIB_H
    #include <stdlib.h>
#endif 

#ifndef STDIO_H
    #include <stdio.h>
#endif

struct tokenStruct;

typedef struct tokenStruct *token;

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

