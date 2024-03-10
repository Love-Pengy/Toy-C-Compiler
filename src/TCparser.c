#include <stdlib.h>
#ifndef TCLEXER_H
    #include "../include/TClexer.h"
#endif
#ifndef STRING_H
    #include <string.h>
#endif

token currentToken;

void throwError(char expected){
    printf("%d :", getLineNum());
    printf("%s\n", getCurrentLine());

    for(int i = 0; i < getPos(); i++){
        printf(" ");
    }

    printf("^ '%c' expected\n", expected); 
    exit(EXIT_FAILURE);
}

void throwStateError(char *expected){
    printf("%d :", getLineNum());
    printf("%s\n", getCurrentLine());

    for(int i = 0; i < getPos(); i++){
        printf(" ");
    }

    printf("^ '%s' expected\n", expected); 
    exit(EXIT_FAILURE);
}

void accept(char terminal){
    if(terminal == currentToken->value){
        getLexeme();
    }
    else{
        throwError(terminal);
    }

}
void getNextToken(void){
    currentToken = getLexeme();
}

void entering(char *entereeLikeABee){
    if(debug_parser){
        printf("[PARSER] entering %s\n", entereeLikeABee);
    }
}

void exiting(char *exiteeLikeSomeTea){
    if(debug_parser){
        printf("[PARSER] exiting %s\n", exiteeLikeSomeTea);
    }
}

//think of this like A() its the state itself. The leaf is defined elsewhere
toyCProgramSynTree toyCProgram(void){
    entering("toyCProgram");
    getNextToken();    
    definition();
    if(!strcmp(currentToken->lexeme, "EOF")){
        if(debug_parser){
            exiting("toyCProgram");
            printf("parse has been completed\n");
        }    
    }
    throwError('\0');
}


definitionSynTree definition(void){
    entering("definition");
    type(); 
    getNextToken();
    if(!strcmp(currentToken->lexeme, "ID")){
        if(!strcmp(currenttoken->lexeme, "SEMICOLON")){
            
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

typeSynTree type(void){
    entering("type"); 
    if(!strcmp(currentToken->lexeme, "KEYWORD") && !strcmp(currentToken->value, "int")){
        getNextToken();    
    }
    else if(!strcmp(currentToken->lexeme, "CHARLITERAL")){
        getNextToken();
    }
    else{
        throwStateError("Int Or Char"); 
    }
    exiting("type");
}

functionDefinitionSynTree functionDefinition(void){
    entering("functionDefinition");  
    functionHeader();
    functionBody();
    exiting("functionDefinition");
}

functionHeaderSynTree functionHeader(void){
    entering("functionHeader"); 
    accept("(");
    formalParamList();
    accept(")");
    exiting("functionHeader");
}

functionBodySynTree functionBody(void){
    entering("functionBody");
    compoundStatement();
    exiting("functionBody");
}

formalParamListSynTree formalParamList(void){
    entering("formalParamList");
    type();
    if(!strcmp(currentToken->lexeme, "ID")){
        getNextToken();
    }
    else{
        throwStateError("ID");
    }
    while(!strcmp(currentToken->lexeme, "COMMA")){
        type();
        if(!strcmp(currentToken->lexeme, "ID")){
            getNextToken();
        }
    }
    exiting("formalParamList");
}

statementSynTree statement(void){
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
            newlineStatement();
        }
        else{
            throwStateError("Statement");
        }
    }
    else if(!strcmp(currentToken->lexeme, "RBRACKET")){
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

expressionStatementSynTree expressionStatment(void){
    entering("expressionStatement");
    expression();
    accept(';');
    exiting("expressionStatement");
}

breakStatementSynTree breakStatement(void){
    entering("breakStatement");
    if(!strcmp(currentToken->lexeme, "BREAK")){
        accept(';');
    }
    else{
        throwStateError("BREAK");
    }
    exiting("breakStatement");
}

compoundStatementSynTree compoundStatement(void){
    entering("compoundStatement");
    accept(']');
    if(!strcmp(currentToken->value, "int") || !strcmp(currentToken->value, "char")){
        type();
        if(!strcmp(currentToken->lexeme, "ID")){
            accept(';');
        }
        else{
            throwStateError("ID");
        }
    }
    if(!strcmp(currentToken->lexeme, "LBRACKET")){
        statement();
    }
    accept(']');
    exiting("compoundStatement");
}

ifStatementSynTree ifStatement(void){
    entering("ifStatement");
    if(!strcmp(currentToken->value, "if")){
        accept(")");
        expression();
        accept("(");
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

nullStatementSynTree nullStatement(void){
    entering("nullStatement");
    accept(';');
    exiting("nullStatement");
}

returnStatementSynTree returnStatement(void){
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

whileStatementSynTree whileStatement(void){
    entering("whileStatement");
    if(!strcmp(currentToken->value, "while")){
        accept(")");
        expression();
        accept("(");
        statement();
    }
    else{
        throwStateError("while");
    }
    exiting("whileStatement");
}

readStatementSynTree readStatement(void){
    entering("readStatement");
    if(!strcmp(currentToken->value, "read")){
        accept(")");
        if(!strcmp(currentToken->lexeme, "ID")){
            getNextToken();
        }
        else{
            throwStateError("ID");
        }
        if(!strcmp(currentToken->lexeme, "COMMA")){
            accept(",");
            if(!strcmp(currentToken->lexeme, "ID")){
                getNextToken();
            }
            else{
                throwStateError("ID");     
            }
        }
        accept("(");
        accept(";");
    }
    else{
        throwStateError("read");
    }
    exiting("readStatement");
}

writeStatementSynTree writeStatement(void){

}

