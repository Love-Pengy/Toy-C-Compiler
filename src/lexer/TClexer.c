//B. Frazier 3/16/24

#include "../../include/lexer/TClexer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../../include/cmdLine/TCglobals.h"


int LEXERDEBUG = 0;
static char* currentLine = ""; 
static int currentIndex = -1;
static int currentLineIndex = 0;



void throwLexerError(char *problem){
    printf("%d: ERROR: %s\n", getLineNum(), problem);
    fflush(stdout);
    exit(EXIT_FAILURE);
}

void dumpScannedFile(void){
    rewind(filePointer);
    char *hold = malloc(sizeof(char) * 501);
    hold[0] = '\0';
    while(fgets(hold, 500, filePointer)){   
        printf("%s", hold); 
    }
}

void charConcat(char *string, char character){
    char charToStr[5] = "";
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
char *getLine(void){
    currentLineIndex++;
    char *output = malloc(sizeof(char) * 500);
    output[0] = '\0';
    if(!fgets(output, 500, filePointer)){
        return(NULL);
    }
    if(output[strlen(output) - 1] == '\n'){
        output[strlen(output) - 1] = '\0';
    }
    return(output);
}


//get char from line, will return 0xFE if its the eol will return 0xFF if its eof 
unsigned char getChar(void){
    if(currentLine == NULL){
        return((char)0xFF);
    }
    if(strlen(currentLine) == 0){
        currentLine = getLine();
        if(currentLine == NULL){
            return((char)0xFF);
        }
        else{
            return(0xFE);
        }
    }
    else if(strlen(currentLine) > (currentIndex + 1)){
        currentIndex++;
        if(LEXERDEBUG){
            printf("CURRENTCHAR: %c\n", currentLine[currentIndex]);
        }
        return(currentLine[currentIndex]);
    }
    else{
        currentLine = getLine();
        if(currentLine == NULL){
            return((char)0xFF);
        }
        else{
            currentIndex = -1;
            return(0xFE);
        }
    }
    
}

//get the sequence of characters that we're lookiung for (or error ig)
token getLexeme(void){
    token lexeme = initToken(); 
    char currentChar = ' ';
    while(((currentChar = getChar())) != ((char)0xFF)){
        if(currentChar == ':'){
            lexeme = createToken("COLON", ":");
            if(debug_scanner){
                printToken(lexeme);
            }
            return(lexeme);
        }
        else if(currentChar == ';'){
            lexeme = createToken("SEMICOLON", ";");
            if(debug_scanner){
                printToken(lexeme);
            }
            return(lexeme);
        }
        else if(currentChar == ','){
            lexeme = createToken("COMMA", ",");
            if(debug_scanner){
                printToken(lexeme);
            }
            return(lexeme);
        }
        else if(currentChar == ']'){
            lexeme = createToken("RBRACKET", "]");
            if(debug_scanner){
                printToken(lexeme);
            }
            return(lexeme);
        }
        else if(currentChar == '['){
            lexeme = createToken("LBRACKET", "[");
            if(debug_scanner){
                printToken(lexeme);
            }
            return(lexeme);
        }
        else if(currentChar == '}'){
            lexeme = createToken("RCURLY", "}");
            if(debug_scanner){
                printToken(lexeme);
            }
            return(lexeme);
        }
        else if(currentChar == '{'){
            lexeme = createToken("LCURLY", "{");
            if(debug_scanner){
                printToken(lexeme);
            }
            return(lexeme);
        }
        else if(currentChar == ')'){
            lexeme = createToken("RPAREN", ")");
            if(debug_scanner){
                printToken(lexeme);
            }
            return(lexeme);
        }
        else if(currentChar == '('){
            lexeme = createToken("LPAREN", "(");
            if(debug_scanner){
                printToken(lexeme);
            }
            return(lexeme);
            
        } 
        //COMMENTS
        else if(currentChar == '/'){
            if((strlen(currentLine) > (currentIndex + 1)) && (currentLine[currentIndex + 1]) == '/'){
                while(1){
                    currentChar = getChar();
                    if((currentChar == (char)0xFE) || (currentChar == (char)0xFF)){
                        break;
                    }
                }
                return(NULL);
            }
            else if((strlen(currentLine) > (currentIndex + 1)) &&(currentLine[currentIndex + 1]) == '*'){
                //overall count of begginners
                int count = 0;
                //start of group comments
                int start = 1;
                //end of the comments
                int end = 0;
                
                int first = 1;

                while(count || first){
                    first = 0;
                    currentChar = getChar();
                    if((int)currentChar == (char)0xFF){
                        throwLexerError("Comment Not Ended");
                    }
                    if((int)currentChar == (char)0xFE){
                        continue;
                    }        
                    if((currentChar == '/') && (!start)){
                        if(end){
                            count--;
                            end = 0;
                        }
                        else{
                            start = 1;
                        }
                    }
                    else if((currentChar == '*') && (!end)){
                        if(start){
                            count++;
                            start = 0;
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
                return(NULL);
            }
            else{
                lexeme = createToken("MULOP", "/");
                if(debug_scanner){
                    printToken(lexeme);
                }
                return(lexeme);        
            }
        }
        else if((currentChar == '%') || (currentChar == '&')){
            if(currentChar == '%'){
                lexeme = createToken("MULOP", "%");
                if(debug_scanner){
                    printToken(lexeme);
                }
                return(lexeme);
            }
            currentChar = getChar();
            if(currentChar == '&'){
                lexeme = createToken("MULOP", "&&");
                if(debug_scanner){
                    printToken(lexeme);
                }
                return(lexeme);        
            }
            printf("INVALID SEQUENCE\n");
            exit(EXIT_FAILURE);
        } 

        //KEYWORD & ID
        else if(isalpha(currentChar)){
            char* string = malloc(sizeof(char) * 500);
            string[0] = '\0';
            while((((int)currentChar) != (char)0xFE) && ((int)currentChar != (char)0xFF) && (currentChar != ' ')){
                if(!isalnum(currentChar)){
                    break;
                }
                else{
                    charConcat(string, currentChar);
                    if((strlen(currentLine) > (currentIndex + 1))){
                        if(isalnum(currentLine[currentIndex + 1])){
                            currentChar = getChar();
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        break;
                    }
                }
            }
            if(checkLUT(string)){
                lexeme = createToken("KEYWORD", string);
                if(debug_scanner){
                    printToken(lexeme);
                }
                return(lexeme);
                }
            else{
                lexeme = createToken("ID", string);
                if(debug_scanner){
                    printToken(lexeme);
                }
                return(lexeme);
                }
        }
        //NUMBER
        else if(isdigit(currentChar)){
            int fraction = 0; 
            int exponent = 0;
            char*output = malloc(sizeof(char) * 100);
            output[0] = '\0';
            charConcat(output, currentChar);
            while(1){
                if(strlen(currentLine) > (currentIndex + 1)){
                    char next = currentLine[currentIndex + 1];
                    if((next == '+') || (next == '-') || (next == 'E') || (next == '.') || isdigit(next)){
                        
                    }
                    else{
                        break;
                    }
                }
                else{
                    break; 
                }
                currentChar = getChar();
                if(((int)currentChar == (char)0xFE) || (currentChar == (char)0xFF)){
                    break;
                }
                if(isdigit(currentChar)){
                    charConcat(output, currentChar);
                    continue;
                }
                else{
                    if((currentChar == '+') || (currentChar == '-')){
                        if(!exponent){
                            throwLexerError("+ Or - Without Exponent Specifier");
                        }
                        else if(output[strlen(output) - 1] == 'E'){
                            charConcat(output, currentChar);
                            continue;
                        }
                        else{
                            throwLexerError("Invalid Number Specification");
                        }
                    }
                    else if(currentChar == '.'){
                        if((!fraction) && (!exponent)){
                            fraction = 1;
                            charConcat(output, currentChar);
                        }
                        else{
                            throwLexerError("Invalid Number of Float Identifiers");
                        }
                    }
                    else if(currentChar == 'E'){
                        if(!exponent){
                            exponent = 1;
                            charConcat(output, currentChar);
                        }
                        else{
                            throwLexerError("Invalid Number Of Exponent Identifiers");
                        }
                    }
                    else{
                        break;
                    }
                }
            }
            lexeme = createToken("NUMBER", output);
            if(debug_scanner){
                printToken(lexeme);
            }
            return(lexeme);
        }
        //CHARLITERAL
        else if(currentChar == '\''){
            char * output = malloc(sizeof(char) * 10);
            output[0] = '\0';
            charConcat(output, currentChar);
            currentChar = getChar();
            if(currentChar == '\''){
                charConcat(output, currentChar);
                lexeme = createToken("CHARLITERAL", output);
                if(debug_scanner){
                    printToken(lexeme);
                }
                return(lexeme);
            }
            else{
                charConcat(output, currentChar);
                currentChar = getChar();
                if(currentChar == '\''){
                    charConcat(output, currentChar);    
                    lexeme = createToken("CHARLITERAL", output);
                    if(debug_scanner){
                        printToken(lexeme);
                    }
                    return(lexeme);
                }
            }
            throwLexerError("Invalid Char Specification");
        }

        //STRING
        else if(currentChar == '\"'){
            char* hold = malloc(sizeof(char) * 501);
            hold[0] = '\0';
            charConcat(hold, currentChar);
            while(1){
                currentChar = getChar();
                if(((int)currentChar == (char)0xFF) && ((int)currentChar == (char)0xFE)){
                    lexeme = createToken("STRING", hold);
                    if(debug_scanner){
                        printToken(lexeme);
                    }
                    return(lexeme);
                }
                if(currentChar == '\"'){
                    charConcat(hold, currentChar);
                    lexeme = createToken("STRING", hold);
                    if(debug_scanner){
                        printToken(lexeme);
                    }
                    return(lexeme);
                }
                else if((!(currentChar == '\n'))){ 
                    charConcat(hold, currentChar);
                    continue;
                }
                else{
                    throwLexerError("Invalid String");
                }
            }
            throwLexerError("Invalid String");
        }

        else if((currentChar == '=') || (currentChar == '!') || (currentChar == '<') || (currentChar == '>')){
            char* holdString = malloc(sizeof(char) * 20);
            holdString[0] = '\0';
            charConcat(holdString, currentChar);
            //assignop is here too
            if(currentChar == '='){
                if((strlen(currentLine) > (currentIndex + 1))){
                    if(currentLine[currentIndex+1] == '='){
                        currentChar = getChar();
                        lexeme = createToken("RELOP","==");
                        if(debug_scanner){
                            printToken(lexeme);
                        }             
                        return(lexeme);       
                    }
                    else{
                        lexeme = createToken("ASSIGNOP", holdString);
                        if(debug_scanner){
                            printToken(lexeme);
                        }
                        return(lexeme);        
                    }
                }
            }
            else if(currentChar == '!'){
                if((strlen(currentLine) > (currentIndex + 1))){
                    if(currentLine[currentIndex+1] == '='){
                        currentChar = getChar();
                        lexeme = createToken("RELOP", "!=");
                        if(debug_scanner){
                            printToken(lexeme);
                        }
                        return(lexeme);       
                    }
                    else{
                        charConcat(holdString, currentChar);
                        lexeme = createToken("NOT", holdString);
                        if(debug_scanner){
                            printToken(lexeme);
                        }
                        return(lexeme);       
                    }
                }
                else{
                    charConcat(holdString, currentChar);
                    lexeme = createToken("NOT", holdString);
                    if(debug_scanner){
                        printToken(lexeme);
                    }
                    return(lexeme);       
                }
            }
            else if(currentChar == '<'){
                if((strlen(currentLine) > (currentIndex + 1))){
                    if(currentLine[currentIndex+1] == '='){
                        currentChar = getChar();
                        charConcat(holdString, currentChar);
                        lexeme = createToken("RELOP", holdString);
                        if(debug_scanner){
                            printToken(lexeme);
                        }
                        return(lexeme);       
                    }
                    else{
                        lexeme = createToken("RELOP", holdString);
                        if(debug_scanner){
                            printToken(lexeme);
                        }
                        return(lexeme);       
                    }
                }
                else{
                    lexeme = createToken("RELOP", holdString);
                    if(debug_scanner){
                        printToken(lexeme);
                    }
                    return(lexeme);       
                }
            }
            else if(currentChar == '>'){
                if((strlen(currentLine) > (currentIndex + 1))){
                    if(currentLine[currentIndex+1] == '='){
                        currentChar = getChar();
                        lexeme = createToken("RELOP", ">=");
                        if(debug_scanner){
                            printToken(lexeme);
                        }
                        return(lexeme);       
                    }
                    else{
                        lexeme = createToken("RELOP", holdString);
                        if(debug_scanner){
                            printToken(lexeme);
                        }
                        return(lexeme);       
                    }
                }
                else{
                    lexeme = createToken("RELOP", holdString);
                    if(debug_scanner){
                        printToken(lexeme);
                    }
                    return(lexeme);       
                }
            }
        }

        else if((currentChar == '+') || (currentChar == '-') || (currentChar == '|')){        
            char * holdString = malloc(sizeof(char) * 20);
            holdString[0] = '\0';
            charConcat(holdString, currentChar);
            if(currentChar == '+'){
                lexeme = createToken("ADDOP", holdString);
                if(debug_scanner){
                    printToken(lexeme);
                }
                return(lexeme);
            }
            else if(currentChar == '-'){
                lexeme = createToken("ADDOP", holdString);
                if(debug_scanner){
                    printToken(lexeme);
                }
                return(lexeme);

            }
            else if(currentChar == '|'){
                if((strlen(currentLine) > (currentIndex + 1))){
                    if(currentLine[currentIndex + 1] == '|'){  
                        currentChar = getChar();
                        charConcat(holdString, currentChar);
                        lexeme = createToken("ADDOP", holdString);
                        if(debug_scanner){
                            printToken(lexeme);
                        }
                        return(lexeme);
                    }
                }
            }
        }
        else if(currentChar == '*'){
            char *holdString = malloc(sizeof(char) * 5);
            holdString[0] = '\0';
            if((strlen(currentLine) < (currentIndex + 1))){
                if(currentLine[currentIndex + 1] == '/'){
                    exit(EXIT_FAILURE);
                }
            }
            charConcat(holdString, currentChar);
            lexeme = createToken("MULOP", holdString);
            if(debug_scanner){
                printToken(lexeme);
            }
            return(lexeme);        
        }
        else {
            if(((int)currentChar == (char)0xFF) || ((int)currentChar == (char)0xFE) || (currentChar == ' ')){
                continue;
            }
            throwLexerError("Invalid Character");
        }
    }
    lexeme = createToken("EOF", "EOF");
    return(lexeme);
    }


//will return the current line index starting at 1
int getLineNum(void){
    return(currentLineIndex);
}
//will return the current index starting at 0
int getPos(void) {
    return(currentIndex);
}

// will return the current line
char *getCurrentLine(void) {
    if (currentLine == NULL) {
        return(" ");
    }
    return(currentLine);
}
