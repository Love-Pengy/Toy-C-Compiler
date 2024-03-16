//B. Frazier 3/16/24
#include <stdlib.h>
#ifndef TCLEXER_H
    #include "../include/TClexer.h"
#endif
#ifndef STRING_H
    #include <string.h>
#endif
#ifndef TCGLOBALS_H
    #include "../include/TCglobals.h"
#endif

token currentToken;

//make it so that it knows stuff exists
void toyCProgram(void);
void definition(void);
void type(void);
void functionDefinition(void);
void functionHeader(void);
void functionBody(void);
void formalParamList(void);
void statement(void);
void expressionStatement(void);
void breakStatement(void);
void compoundStatement(void);
void ifStatement(void);
void nullStatement(void);
void returnStatement(void);
void whileStatement(void);
void readStatement(void);
void writeStatement(void);
void newLineStatement(void);
void expression(void);
void relopExpression(void);
void simpleExpression(void);
void term(void);
void primary(void);
void functionCall(void);
void actualParameters(void);

void throwError(char expected){
    printf("%d :", getLineNum());
    printf("%s\n", getCurrentLine());

    for(int i = 0; i < getPos(); i++){
        printf(" ");
    }
    
    printf("^ '%c' expected\n", expected); 
    fflush(stdout);
    exit(EXIT_FAILURE);
}

void throwStateError(char *expected){
    printf("%d: ", getLineNum());
    printf("%s\n", getCurrentLine());

    for(int i = 0; i < getPos(); i++){
        printf(" ");
    }

    printf("^ '%s' expected\n", expected); 
    fflush(stdout);
    exit(EXIT_FAILURE);
}

void getNextToken(void){
    currentToken = getLexeme();
    //lexer returns NULL if token is a comment
    while(currentToken == NULL){
        currentToken = getLexeme();
    }
}

void accept(char terminal){
    if(terminal == currentToken->value[0]){
        getNextToken();
    }
    else{
        throwError(terminal);
    }

}


void entering(char *entereeLikeABee){
    if(debug_parser){
        printf("[PARSER] entering %s\n", entereeLikeABee);
        fflush(stdout);
    }
}

void exiting(char *exiteeLikeSomeTea){
    if(debug_parser){
        printf("[PARSER] exiting %s\n", exiteeLikeSomeTea);
        fflush(stdout);
    }
}

//think of this like A() its the state itself. The leaf is defined elsewhere
void toyCProgram(void){
    entering("toyCProgram");
    getNextToken();    
    while(strcmp(currentToken->lexeme, "EOF")){ 
        definition();
    }
    exiting("toyCProgram");
    printf("parse has been completed\n");
}


void definition(void){
    entering("definition");
    type(); 
    if(!strcmp(currentToken->lexeme, "ID")){
        getNextToken();
        if(!strcmp(currentToken->lexeme, "SEMICOLON")){
            accept(';');
        }
        else{
            functionDefinition();
        }
    }
    else{
        throwStateError("ID");   
    }
    exiting("definition");
}

void type(void){
    entering("type"); 
    if(!strcmp(currentToken->value, "int")){
        getNextToken();    
    }
    else if(!strcmp(currentToken->value, "char")){
        getNextToken();
    }
    else{
        throwStateError("Int Or Char"); 
    }
    exiting("type");
}

void functionDefinition(void){
    entering("functionDefinition");  
    functionHeader();
    functionBody();
    exiting("functionDefinition");
}

void functionHeader(void){
    entering("functionHeader"); 
    accept('(');
    if ((!strcmp(currentToken->value, "int")) || (!strcmp(currentToken->value, "char"))){
        formalParamList();
    }
    accept(')');
    exiting("functionHeader");
}

void functionBody(void){
    entering("functionBody");
    compoundStatement();
    exiting("functionBody");
}

void formalParamList(void){
    entering("formalParamList");
    type();
    if(!strcmp(currentToken->lexeme, "ID")){
        getNextToken();
    }
    else{
        throwStateError("ID");
    }
    while(!strcmp(currentToken->lexeme, "COMMA")){
        accept(',');
        type();
        if(!strcmp(currentToken->lexeme, "ID")){
            getNextToken();
        }
    }
    exiting("formalParamList");
}

void statement(void){
    entering("statement");
    if(!strcmp(currentToken->lexeme, "KEYWORD")){
        if(!strcmp(currentToken->value, "break")){
            breakStatement();
        }
        else if(!strcmp(currentToken->value, "if")){
            ifStatement();
        }
        else if(!strcmp(currentToken->value, "return")){
            returnStatement();
        }
        else if(!strcmp(currentToken->value, "while")){
            whileStatement();
        }
        else if(!strcmp(currentToken->value, "read")){
            readStatement();
        }
        else if(!strcmp(currentToken->value, "write")){
            writeStatement();
        }
        else if(!strcmp(currentToken->value, "newline")){
            newLineStatement();
        }
        else{
            throwStateError("Statement");
        }
    }
    else if(!strcmp(currentToken->lexeme, "LCURLY")){
        compoundStatement();
    }
    else if(!strcmp(currentToken->lexeme, "SEMICOLON")){
        nullStatement();
    }
    else{
        expressionStatement();
    }
    exiting("statement");
}

void expressionStatement(void){
    entering("expressionStatement");
    expression();
    accept(';');
    exiting("expressionStatement");
}

void breakStatement(void){
    entering("breakStatement");
    if(!strcmp(currentToken->value, "break")){
        getNextToken();
        accept(';');
    }
    else{
        throwStateError("break");
    }
    exiting("breakStatement");
}

void compoundStatement(void){
    entering("compoundStatement");
    accept('{');
    while(strcmp(currentToken->lexeme, "RCURLY") != 0){
        if(!strcmp(currentToken->value, "int") || !strcmp(currentToken->value, "char")){
            type();
            if(!strcmp(currentToken->lexeme, "ID")){
                getNextToken();
                accept(';');
            }
        }
        else{
            statement();
        }
    }
    accept('}');
    exiting("compoundStatement");
}

void ifStatement(void){
    entering("ifStatement");
    if(!strcmp(currentToken->value, "if")){
        getNextToken();
        accept('(');
        expression();
        accept(')');
        statement();
        if(!strcmp(currentToken->value, "else")){
            getNextToken();
            statement();
        }
    }
    else{
        throwStateError("if");
    }
    exiting("ifStatement");
}

void nullStatement(void){
    entering("nullStatement");
    accept(';');
    exiting("nullStatement");
}

void returnStatement(void){
    entering("returnStatement");  
    if(!strcmp(currentToken->value, "return")){
        getNextToken();
        if(strcmp(currentToken->lexeme, "SEMICOLON")){
            expression();  
        }
        accept(';');
    }
    else{
        throwStateError("return");
    }
    exiting("returnStatement");
}

void whileStatement(void){
    entering("whileStatement");
    if(!strcmp(currentToken->value, "while")){
        getNextToken();
        accept('(');
        expression();
        accept(')');
        statement();
    }
    else{
        throwStateError("while");
    }
    exiting("whileStatement");
}

void readStatement(void){
    entering("readStatement");
    if(!strcmp(currentToken->value, "read")){
        getNextToken();
        accept('(');
        if(!strcmp(currentToken->lexeme, "ID")){
            getNextToken();
        }
        else{
            throwStateError("ID");
        }
        while(!strcmp(currentToken->lexeme, "COMMA")){
            accept(',');
            if(!strcmp(currentToken->lexeme, "ID")){
                getNextToken();
            }
            else{
                throwStateError("ID");     
            }
        }
        accept(')');
        accept(';');
    }
    else{
        throwStateError("read");
    }
    exiting("readStatement");
}

void writeStatement(void){
    entering("writeStatement"); 
    if(!strcmp(currentToken->value, "write")){
        getNextToken();
        accept('(');
        actualParameters();
        accept(')');
        accept(';');
    }
    else{
        throwStateError("write");
    }
    exiting("writeStatement");
}

void newLineStatement(void){
    entering("newLineStatement");
    if(!strcmp(currentToken->value, "newline")){
        getNextToken();
        accept(';');
    }
    else{
        throwStateError("newline");
    }
    exiting("newLineStatement");
}

void expression(void){
    entering("expression");
    relopExpression();
    while(!strcmp(currentToken->lexeme, "ASSIGNOP")){
        getNextToken();
        relopExpression();
    }
    exiting("expression");
}

void relopExpression(void){
    entering("relopExpression");
    simpleExpression();
    while(!strcmp(currentToken->lexeme, "RELOP")){
        getNextToken(); 
        simpleExpression();
    }
    exiting("relopExpression");
}

void simpleExpression(void){
    entering("simpleExpression");
    term();
    while(!strcmp(currentToken->lexeme, "ADDOP")){
        getNextToken();
        term();
    }
    exiting("simpleExpression");
}

void term(void){
    entering("term");
    primary();
    while(!strcmp(currentToken->lexeme, "MULOP")){
        getNextToken();
        primary();
    }
    exiting("term");
}

void primary(void){
    entering("primary");
    if(!strcmp(currentToken->lexeme, "ID")){
        getNextToken();
        if(!strcmp(currentToken->lexeme, "LPAREN")){
            functionCall(); 
        } 
    }
    else if(!strcmp(currentToken->lexeme, "NUMBER")){
        getNextToken();
    }
    else if(!strcmp(currentToken->lexeme, "STRING")){
        getNextToken();
    }
    else if(!strcmp(currentToken->lexeme, "CHARLITERAL")){
        getNextToken();
    }
    else if(!strcmp(currentToken->lexeme, "LPAREN")){
        accept('(');
        expression();
        accept(')'); 
    }
    else if((!strcmp(currentToken->value, "-")) || (!strcmp(currentToken->lexeme, "NOT"))){
        getNextToken();
        primary();
    }
    else{
        throwStateError("ID, NUMBER, STRING, CHARLITERAL, LPAREN, -, or NOT");
    }
    exiting("primary");
}

void functionCall(void){
    entering("functionCall");
    accept('(');
    if(!strcmp(currentToken->lexeme, "ID")){
        actualParameters();
    }
    else if(!strcmp(currentToken->lexeme, "NUMBER")){
        actualParameters();
    }
    else if(!strcmp(currentToken->lexeme, "STRING")){
        actualParameters();
    }
    else if(!strcmp(currentToken->lexeme, "CHARLITERAL")){
        actualParameters();
    }
    else if(!strcmp(currentToken->lexeme, "LPAREN")){
        actualParameters();
    }
    else if((!strcmp(currentToken->value, "-")) || (!strcmp(currentToken->lexeme, "NOT"))){
        actualParameters();
    }
    accept(')');
    exiting("functionCall");
}

void actualParameters(void){
    entering("actualParameters");
    expression();
    while(!strcmp(currentToken->lexeme, "COMMA")){
        getNextToken(); 
        expression();
    }
    exiting("actualParameters");
}



