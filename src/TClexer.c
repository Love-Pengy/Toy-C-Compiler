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
static char* currentLine = ""; 
static char* currentToken = "";
static int currentIndex = -1;

void charConcat(char *string, char character){
    char charToStr[2] = "";
    charToStr[1] = '\0';
    charToStr[0] = character;    
    strcat(string, charToStr);
}
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


//get char from line, will return 0xFE if its the eol will return 0xFF if its eof 
unsigned char getChar(FILE *fp){
    if(strlen(currentLine) == 0){
        currentLine = getLine(fp);
        if(currentLine == NULL){
            return(0xFF);
        }
        else{
            return(0xFE);
        }
    }
    else if(strlen(currentLine) > (currentIndex + 1)){
        currentIndex++;
        return(currentLine[currentIndex]);
    }
    else{
        currentLine = getLine(fp);
        if(currentLine == NULL){
            return(0xFF);
        }
        else{
            currentIndex = 0;
            return(0xFE);
        }
    }
    
}

//get the sequence of characters that we're lookiung for (or error ig)
char *getLexeme(FILE* fp){
    char *lexeme = malloc(sizeof(char) * 550); 
    char currentChar = ' ';
    while(((int)(currentChar = getChar(fp))) != 0xFF){
        if(currentChar == ':'){
            strcat(lexeme, "<COLON>, \"");
            strcat(lexeme, &currentChar);
            strcat(lexeme, "\"");
            return(lexeme);
        }
        else if(currentChar == ';'){
            strcat(lexeme, "<SEMICOLON>, \"");
            strcat(lexeme, &currentChar);
            strcat(lexeme, "\"");
            return(lexeme);
        }
        else if(currentChar == ','){
            strcat(lexeme, "<COMMA>, \"");
            strcat(lexeme, &currentChar);
            strcat(lexeme, "\"");
            return(lexeme);
        }
        else if(currentChar == ']'){
            strcat(lexeme, "<RBRACKET>, \"");
            strcat(lexeme, &currentChar);
            strcat(lexeme, "\"");
            return(lexeme);
        }
        else if(currentChar == '['){
            strcat(lexeme, "<LBRACKET>, \"");
            strcat(lexeme, &currentChar);
            strcat(lexeme, "\"");
            return(lexeme);
        }
        else if(currentChar == '}'){
            strcat(lexeme, "<RCURLY>, \"");
            strcat(lexeme, &currentChar);
            strcat(lexeme, "\"");
            return(lexeme);
        }
        else if(currentChar == '{'){
            strcat(lexeme, "<LCURLY>, \"");
            strcat(lexeme, &currentChar);
            strcat(lexeme, "\"");
            return(lexeme);
        }
        else if(currentChar == ')'){
            strcat(lexeme, "<RPAREN>, \"");
            strcat(lexeme, &currentChar);
            strcat(lexeme, "\"");
            return(lexeme);
        }
        else if(currentChar == '('){
            strcat(lexeme, "<RPAREN>, \"");
            strcat(lexeme, &currentChar);
            strcat(lexeme, "\"");
            return(lexeme);
            
        }
        else if((currentChar == '/') || (currentChar == '%') || (currentChar == '&')){
            if(currentChar == '%'){
                strcat(lexeme, "<MULOP>, \"");
                strcat(lexeme, &currentChar);
                strcat(lexeme, "\"");
                return(lexeme);
            }
            if(currentChar == '&'){
                currentChar = getChar(fp);
                if(currentChar == '&'){
                    strcat(lexeme, "<MULOP>, \"");
                    strcat(lexeme, "&&");
                    strcat(lexeme, "\"");
                    return(lexeme);        
                }
            }
        }
        
            //COMMENTS
        else if(currentChar == '/'){
            if((strlen(currentLine) < (currentIndex + 1)) && (currentLine[currentIndex + 1]) == '/'){
                while((int)getChar(fp) != -2){
                }
                return(" ");
            }
            else if((strlen(currentLine) < (currentIndex + 1)) &&(currentLine[currentIndex + 1]) == '*'){
                int count = 1;
                int start = 0;
                int end = 0;

                while(count){
                    currentChar = getChar(fp);
                    if((int)currentChar == 0xFF){
                        printf("ERROR: Comment Not Ended");
                        exit(EXIT_FAILURE);
                    }
                    if((int)currentChar == -2){
                        continue;
                    }        
                    if((currentChar == '/') && (!start)){
                        if(end){
                            count--;
                        }
                        else{
                            start = 1;
                        }
                    }
                    else if((currentChar == '*') && (!end)){
                        if(start){
                            count++;
                        }
                        else{
                            end = 1;
                        }
                    }
                    else{
                        if(start){
                            start = 0;
                        }
                        if(end){
                            end = 0;
                        }
                    }


                }
                return(" ");
            }
            else{
                strcat(lexeme, "<MULOP>, \"");
                strcat(lexeme, &currentChar);
                strcat(lexeme, "\"");
                return(lexeme);        
            }
        }
        //KEYWORD & ID
        else if(isalpha(currentChar)){
            char* string = malloc(sizeof(char) * 500);
            string[0] = '\0';
            while((((int)currentChar) != -2) && ((int)currentChar != 0xFF) && (currentChar != ' ')){
                if(!isalnum(currentChar)){
                    printf("ERROR: Invalid ID\n");
                    exit(EXIT_FAILURE);
                }
                else{
                    if((strlen(string) == 0)){
                        string[0] = currentChar;
                    }
                    else{
                        charConcat(string, currentChar);
                    }
                    currentChar = getChar(fp);
                }
            }
            if(checkLUT(string)){
                strcat(lexeme, "<KEYWORD>, \"");
                strcat(lexeme, string);
                strcat(lexeme, "\"");
                return(lexeme);
                }
            else{
                strcat(lexeme, "<ID>, \"");
                strcat(lexeme, string);
                strcat(lexeme, "\"");
                return(lexeme);
                }
        }
        //NUMBER
        else if(isdigit(currentChar)){
            int fraction = 0; 
            int exponent = 0;
            char*output = malloc(sizeof(char) * 100);
            strcat(output, &currentChar);
            while(((currentChar = getChar(fp) != -2)) && (currentChar = getChar(fp) != 0xFF)){
                if(isdigit(currentChar)){
                    strcat(output, &currentChar);
                    continue;
                }
                else{
                    if((currentChar == '+') || (currentChar == '-')){
                        if(!exponent){
                            printf("ERROR: + or - without exponent specifier\n");
                            exit(EXIT_FAILURE);
                        }
                        else if(output[strlen(output) - 1] == 'E'){
                            strcat(output, &currentChar);
                            continue;
                        }
                        else{
                            printf("ERROR: Invalid Number Specification\n");
                            exit(EXIT_FAILURE);
                        }
                    }
                    if(currentChar == '.'){
                        if((!fraction) && (!exponent)){
                            fraction = 1;
                            strcat(output, &currentChar);
                        }
                        else{
                            printf("Invalid Number of Float Identifiers\n");
                            exit(EXIT_FAILURE);
                        }
                    }
                    if(currentChar == 'E'){
                        if(!exponent){
                            exponent = 1;
                            strcat(output, &currentChar);
                        }
                        else{
                            printf("Invalid Number of Exponent Identifiers\n");
                            exit(EXIT_FAILURE);
                        }
                    }
                }
            }
            strcat(lexeme, "<NUMBER>, \"");
            strcat(lexeme, output);
            strcat(lexeme, "\"");
            return(lexeme);
        }
        //CHARLITERAL
        else if(currentChar == '\''){
            char * output = malloc(sizeof(char) * 10);
            strcat(output, &currentChar);
            currentChar = getChar(fp);
            if(currentChar == '\''){
                strcat(output, &currentChar);
                strcat(lexeme, "<CHARLITERAL>, \"");
                strcat(lexeme, output);
                strcat(lexeme, "\"");
                return(lexeme);
            }
            if(isalpha(currentChar)){
                currentChar = getChar(fp);
                if(currentChar == '\''){
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
        else if(currentChar == '\"'){
            char *hold = malloc(sizeof(char) * 501);
            strcat(hold, &currentChar);
            while(((int)(currentChar = getChar(fp)) != 0xFF) && ((int)(currentChar = getChar(fp)) != -2)){
                if(currentChar == '\"'){
                    strcat(lexeme, "<STRING>, \"");
                    strcat(lexeme, hold);
                    strcat(lexeme, "\"");
                    return(lexeme);
                }
                else if((!(currentChar == '\n'))){ 
                    strcat(hold, &currentChar);
                    continue;
                }
                else{
                    printf("ERROR: Invalid String\n");
                    exit(EXIT_FAILURE);
                }
            }
            printf("ERROR: Invalid String\n");
            exit(EXIT_FAILURE);
        }

        else if((currentChar == '=') || (currentChar == '!') || (currentChar == '<') || (currentChar == '>')){
            //assignop is here too
            if(currentChar == '='){
                if((strlen(currentLine) < (currentIndex + 1))){
                    if(currentLine[currentIndex+1] == '='){
                        currentChar = getChar(fp);
                        strcat(lexeme, "<RELOP>, \"");
                        strcat(lexeme, "==");
                        strcat(lexeme, "\"");
                        return(lexeme);       
                    }
                    else{
                        strcat(lexeme, "<ASSIGNOP>, \"");
                        strcat(lexeme, &currentChar);
                        strcat(lexeme, "\"");
                        return(lexeme);        
                }
            }
            }
            else if(currentChar == '!'){
                if((strlen(currentLine) < (currentIndex + 1))){
                    if(currentLine[currentIndex+1] == '='){
                        currentChar = getChar(fp);
                        strcat(lexeme, "<RELOP>, \"");
                        strcat(lexeme, "!=");
                        strcat(lexeme, "\"");
                        return(lexeme);       
                    }
                }
                else{
                    strcat(lexeme, "<NOT>, \"");
                    strcat(lexeme, &currentChar);
                    strcat(lexeme, "\"");
                    return(lexeme);       
                }
            }
            else if(currentChar == '<'){
                if((strlen(currentLine) < (currentIndex + 1))){
                    if(currentLine[currentIndex+1] == '='){
                        currentChar = getChar(fp);
                        strcat(lexeme, "<RELOP>, \"");
                        strcat(lexeme, "<=");
                        strcat(lexeme, "\"");
                        return(lexeme);       
                    }
                }
                else{
                    strcat(lexeme, "<RELOP>, \"");
                    strcat(lexeme, &currentChar);
                    strcat(lexeme, "\"");
                    return(lexeme);       
                }
            }
            else if(currentChar == '>'){
                if((strlen(currentLine) < (currentIndex + 1))){
                    if(currentLine[currentIndex+1] == '='){
                        currentChar = getChar(fp);
                        strcat(lexeme, "<RELOP>, \"");
                        strcat(lexeme, ">=");
                        strcat(lexeme, "\"");
                        return(lexeme);       
                    }
                }
                else{
                    strcat(lexeme, "<RELOP>, \"");
                    strcat(lexeme, &currentChar);
                    strcat(lexeme, "\"");
                    return(lexeme);       
                }
            }
        }

        else if((currentChar == '+') || (currentChar == '-') || (currentChar == '|')){        
            if(currentChar == '+'){
                strcat(lexeme, "<ADDOP>, \"");
                strcat(lexeme, &currentChar);
                strcat(lexeme, "\"");
                return(lexeme);
            }
            else if(currentChar == '-'){
                strcat(lexeme, "<ADDOP>, \"");
                strcat(lexeme, &currentChar);
                strcat(lexeme, "\"");
                return(lexeme);

            }
            else if(currentChar == '|'){
                if((strlen(currentLine) < (currentIndex + 1))){
                    if(currentLine[currentIndex + 1] == '|'){  
                        currentChar = getChar(fp);
                        strcat(lexeme, "<ADDOP>, \"");
                        strcat(lexeme, &currentChar);
                        strcat(lexeme, "\"");
                        return(lexeme);
                    }
                }
            }
        }
        else if(currentChar == '*'){
            if((strlen(currentLine) < (currentIndex + 1))){
                if(currentLine[currentIndex + 1] == '/'){
                    printf("INVALID GROUP COMMENT\n");
                    exit(EXIT_FAILURE);
                }
            }
            strcat(lexeme, "<MULOP>, \"");
            strcat(lexeme, &currentChar);
            strcat(lexeme, "\"");
            return(lexeme);        
        }
        else{
            if(((int)currentChar == 0xFF) || ((int)currentChar == -2)){
                continue;
            }
            printf("ERROR: INVALID CHARACTER .%d.\n", currentChar);
            exit(EXIT_FAILURE);
        }
    }

    }

int getLineNum();
int getPos();

