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
static char* currentLine; 
static char* currentToken = "";
/*
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
    if(!fgets(output, 500, fptr)){
        return(NULL);
    }
    if(output[strlen(output) - 1] == '\n'){
        output[strlen(output) - 1] = '\0';
    }
    return(output);
}

//get the sequence of characters that we're lookiung for (or error ig)
char *getLexeme(FILE* fp){
    int count = 0;
    char *lexeme = malloc(sizeof(char) * 550);
    if(strlen(currentToken) == 0){
        currentLine = getLine(fp);
        if(!currentLine){
            return("<EOF>, \"EOF\"");
        }
        else{
            currentToken = strtok(strdup(currentLine), " "); 
        }
    }
    else{
        if(!(currentToken = strtok(NULL, " "))){
            currentLine = malloc(sizeof(char) * 501);
            if(!(currentLine = getLine(fp))){
                return("<EOF>, \"EOF\"");
            }
            currentToken = strtok(strdup(currentLine), " "); 
        }    
    }

    if(LEXERDEBUG){
        printf(".%s.\n", currentToken);
    }
    if(!strcmp(currentToken, ":")){
        strcat(lexeme, "<COLON>, \"");
        strcat(lexeme, currentToken);
        strcat(lexeme, "\"");
        return(lexeme);
    }
    else if(!strcmp(currentToken, "!")){
        strcat(lexeme, "<NOT>, \"");
        strcat(lexeme, currentToken);
        strcat(lexeme, "\"");
        return(lexeme);
    }
    else if(!strcmp(currentToken, ";")){
        strcat(lexeme, "<SEMICOLON>, \"");
        strcat(lexeme, currentToken);
        strcat(lexeme, "\"");
        return(lexeme);
    }
    else if(!strcmp(currentToken, ",")){
        strcat(lexeme, "<COMMA>, \"");
        strcat(lexeme, currentToken);
        strcat(lexeme, "\"");
        return(lexeme);
    }
    else if(!strcmp(currentToken, "]")){
        strcat(lexeme, "<RBRACKET>, \"");
        strcat(lexeme, currentToken);
        strcat(lexeme, "\"");
        return(lexeme);
    }
    else if(!strcmp(currentToken, "[")){
        strcat(lexeme, "<LBRACKET>, \"");
        strcat(lexeme, currentToken);
        strcat(lexeme, "\"");
        return(lexeme);
    }
    else if(!strcmp(currentToken, "}")){
        strcat(lexeme, "<RCURLY>, \"");
        strcat(lexeme, currentToken);
        strcat(lexeme, "\"");
        return(lexeme);
    }
    else if(!strcmp(currentToken, "{")){
        strcat(lexeme, "<LCURLY>, \"");
        strcat(lexeme, currentToken);
        strcat(lexeme, "\"");
        return(lexeme);
    }
    else if(!strcmp(currentToken, ")")){
        strcat(lexeme, "<RPAREN>, \"");
        strcat(lexeme, currentToken);
        strcat(lexeme, "\"");
        return(lexeme);
    }
    else if(!strcmp(currentToken, "/") || !strcmp(currentToken, "%") || !strcmp(currentToken, "&&")){
        strcat(lexeme, "<MULOP>, \"");
        strcat(lexeme, currentToken);
        strcat(lexeme, "\"");
        return(lexeme);
    }
    else if(!strcmp(currentToken, "/*") || !strcmp(currentToken, "*/")){
        if(!strcmp(currentToken, "*/")){
            printf("ERROR: Invalid Start To Group Comment %s\n", currentLine);
            exit(EXIT_FAILURE);
        }

        //0 == out of comment, positive == more /* than */ and negative == error
        int count = 1; 
        while(count){
            if(!(currentToken = strtok(NULL, " "))){ 
                //got to EOF
                if(!(currentLine = getLine(fp))){
                    printf("ERROR: Group Comment Not Closed: %d\n", count);
                    exit(EXIT_FAILURE);
                }
                currentToken = strtok(strdup(currentLine), " ");
            }
            if((!strcmp(currentToken, "/*")) || (!strcmp(currentToken, "/*\n"))){
                count++;
            }
            else if(!strcmp(currentToken, "*/") || (!strcmp(currentToken, "*/\n"))){
                count--;
            }
        }
        return(" ");
    }

    else if(!strcmp(currentToken, "//")){   
        currentLine = getLine(fp);
        currentToken = ""; 
        return(" ");
    }
    //KEYWOD & ID
    else if(isalpha(currentToken[0])){
        for(int i = 0; i < strlen(currentToken); i++){
            if(!isalnum(currentToken[i])){
                printf("Invalid currentToken: %s at: .%c.\n", currentToken, currentToken[i]); 
                exit(EXIT_FAILURE);
            }
        }
        if(checkLUT(currentToken)){
            strcat(lexeme, "<KEYWORD>, \"");
            strcat(lexeme, currentToken);
            strcat(lexeme, "\"");
            return(lexeme);
        }
        else{
            strcat(lexeme, "<ID>, \"");
            strcat(lexeme, currentToken);
            strcat(lexeme, "\"");
            return(lexeme);
        }
    }
    //NUMBER
    else if(isdigit(currentToken[0])){
        int fraction = 0; 
        int exponent = 0;
        for(int i = 0; i < strlen(currentToken); i++){
            if(isdigit(currentToken[i])){
                continue;
            }
            else{
                if((currentToken[i] == '+') || (currentToken[i] == '-')){
                    if(!exponent){
                        printf("+ or - without exponent specifier");
                        exit(EXIT_FAILURE);
                    }
                }
                if(currentToken[i] == '.'){
                    if((!fraction) && (!exponent)){
                        fraction = 1;
                    }
                    else{
                        printf("Invalid Number of Float Identifiers\n");
                        exit(EXIT_FAILURE);
                    }
                }
                if(currentToken[i] == 'E'){
                    if(!exponent){
                        exponent = 1;
                    }
                    else{
                        printf("Invalid Number of Exponent Identifiers\n");
                        exit(EXIT_FAILURE);
                    }
                }
            }
        }
        strcat(lexeme, "<NUMBER>, \"");
        strcat(lexeme, currentToken);
        strcat(lexeme, "\"");
        return(lexeme);
    }
    //CHARLITERAL
    else if(currentToken[0] == '\''){
        if(currentToken[1] == '\''){
            strcat(lexeme, "<CHARLITERAL>, \"");
            strcat(lexeme, currentToken);
            strcat(lexeme, "\"");
            return(lexeme);
        }
        if(isalpha(currentToken[1])){
            if(currentToken[2] == '\''){
                strcat(lexeme, "<CHARLITERAL>, \"");
                strcat(lexeme, currentToken);
                strcat(lexeme, "\"");
                return(lexeme);
            }
        }
        printf("Invalid Char Specification");
        exit(EXIT_FAILURE);
    }

    //STRING
    else if(currentToken[0] == '\"'){
        char *hold = malloc(sizeof(char) * 501);
        strcat(hold, currentToken);
        int found = 0;
        while(!found){
            for(int i = 1; i < strlen(currentToken); i++){
                if(currentToken[i] == '\"'){
                    strcat(lexeme, "<STRING>, \"");
                    strncat(lexeme, hold, (strlen(hold) - 2));
                    strcat(lexeme, "\"");
                    return(lexeme);
                }
                else if((!(currentToken[i] == '\n')) && (!(currentToken[i] == '\"'))){
                    hold[i - 1] = currentToken[i];
                    continue;
                }
                else{
                    printf("ERROR: Invalid String\n");
                    exit(EXIT_FAILURE);
                }
            }
            if(!(currentToken = strtok(NULL, " "))){
                printf("ERROR: Invalid String\n");
                exit(EXIT_FAILURE);
            }
            else{
                strcat(hold, currentToken);
            }
        }
    }

    else if((!(strcmp(currentToken, "=="))) || (!(strcmp(currentToken, "!="))) || (!(strcmp(currentToken, "<"))) || (!(strcmp(currentToken, "<="))) || (!(strcmp(currentToken, ">="))) || (!(strcmp(currentToken, ">")))){
        strcat(lexeme, "<RELOP>, \"");
        strcat(lexeme, currentToken);
        strcat(lexeme, "\"");
        return(lexeme);        
    }

    else if((!(strcmp(currentToken, "+"))) || (!strcmp(currentToken, "-")) || (!(strcmp(currentToken, "||")))){        
        strcat(lexeme, "<ADDOP>, \"");
        strcat(lexeme, currentToken);
        strcat(lexeme, "\"");
        return(lexeme);

    }
    else if((!strcmp(currentToken, "*"))){
        strcat(lexeme, "<MULOP>, \"");
        strcat(lexeme, currentToken);
        strcat(lexeme, "\"");
        return(lexeme);        
    }
    else if((!strcmp(currentToken, "="))){
        strcat(lexeme, "<ASSIGNOP>, \"");
        strcat(lexeme, currentToken);
        strcat(lexeme, "\"");
        return(lexeme);
    }

    else{
        return("NOT IMPLEMENTED YET");
    }

}

int getLineNum();
int getPos();

