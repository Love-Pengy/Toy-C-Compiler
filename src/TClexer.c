#ifndef TCLEXER_H
    #include "../include/TClexer.h"
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
#ifndef STRING_H
    #include <string.h>
#endif
#ifndef CTYPE_H
    #include <ctype.h>
#endif

int LEXERDEBUG = 0;

/*
* KEYWORD
* COMMENT
* ID
* NUMBER
* CHARLITERAL
* STRING
* RELOP
* ADDOP
* MULOP
*   *
*   /
*   %
*   &&
* ASSIGNOP
*/
static const char *keywordLUT[] = {
    "int", "char", "return", "if", "else", 
    "for", "do", "while", "switch", "case", 
    "default", "write", "read", "continue", 
    "break", "newline"
};

int checkLUT(char* inString){
    for(int i = 0; i < (sizeof(keywordLUT)/sizeof(keywordLUT[0])); i++){
        if(!strcmp(inString, keywordLUT[i])){
            return(1);
        }
    }
    return(0);
}

//gets raw string
char *getLine(FILE* fptr){
    char *output = malloc(sizeof(char) * 500);
    return(fgets(output, 500, fptr));
}

//get the sequence of characters that we're lookiung for (or error ig)
char *getLexeme(char *sequence){
    if(LEXERDEBUG){
        printf(".%s.\n", sequence);
    }
    if(!strcmp(sequence, ":")){
        return("COLON");
    }
    else if(!strcmp(sequence, "!")){
        return("NOT");
    }
    else if(!strcmp(sequence, ";")){
        return("SEMICOLON");
    }
    else if(!strcmp(sequence, ",")){
        return("COMMA");
    }
    else if(!strcmp(sequence, "]")){
        return("RBRACKET");
    }
    else if(!strcmp(sequence, "[")){
        return("LBRACKET");
    }
    else if(!strcmp(sequence, "}")){
        return("RCURLY");
    }
    else if(!strcmp(sequence, "{")){
        return("LCURLY");
    }
    else if(!strcmp(sequence, ")")){
        return("RPAREN");
    }
    else if(!strcmp(sequence, "/") || !strcmp(sequence, "%") || !strcmp(sequence, "&&")){
        return("MULOP");
    }
    else if(!strcmp(sequence, "/*") || !strcmp(sequence, "*/")){
        return("COMMENT1");
    }
    else if(!strcmp(sequence, "//")){   
        return("COMMENT2");
    }
    else if(isalpha(sequence[0])){
        for(int i = 0; i < strlen(sequence); i++){
            if(!isalnum(sequence[i])){
                printf("Invalid sequence: %s\n", sequence); 
                exit(EXIT_FAILURE);
            }
        }
        if(checkLUT(sequence)){
            return("KEYWORD");
        }
        else{
            return("ID");
        }
    }
    else{
        return("NOT IMPLEMENTED YET");
    }
    


}

int getLineNum();
int getPos();

