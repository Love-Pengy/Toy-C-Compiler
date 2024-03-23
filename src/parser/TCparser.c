//B. Frazier 3/16/24

#ifndef STDLIB
    #define STDLIB
    #include <stdlib.h>
#endif 

#ifndef TCLEXER
    #define TCLEXER
    #include "../../include/lexer/TClexer.h"
#endif

#ifndef STRING
    #define STRING
    #include <string.h>
#endif

#ifndef TCGLOBALS
    #define TCGLOBALS
    #include "../../include/cmdLine/TCglobals.h"
#endif

#ifndef ASSYNTREE
    #define ASSYNTREE
    #include "../../include/parser/ASsynTree.h"
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
    freeToken(currentToken);
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
programTree toyCProgram(void){
    entering("toyCProgram");
    //this needs to be dynamic if I keep running in to the threshold but theoretically I should not 
    definitionTree* dtt = malloc(sizeof(struct definitionTreetType) * 500);
    getNextToken();    
    int counter = 0;
    while(strcmp(currentToken->lexeme, "EOF")){ 
        dtt[counter] = definition();
        counter++;
    }
    exiting("toyCProgram");
    return(createProgramTree(dtt));
    printf("parse has been completed\n");
}


definitionTree definition(void){
    entering("definition");
    enum defTypeProd type;

    //char is four letters
    char *typeSpec = malloc(sizeof(char) * 5);
    strcpy(typeSpec, type()); 
    if(!strcmp(currentToken->lexeme, "ID")){ 
        char *idHold = malloc(sizeof(char) * (strlen(currentToken->value) + 1));
        strcpy(idHold, currentToken->value);
        getNextToken();
        if(!strcmp(currentToken->lexeme, "SEMICOLON")){
            type = variableDef;
            accept(';');
        }
        else{
            type = functionDef;
            functionDefinitionTree fd = malloc(sizeof(struct functionDefinitionTreeType)); 
            fd = functionDefinition(typeSpec, idHold);
            
        }
    }
    else{
        throwStateError("ID");   
    }
    exiting("definition");
    if(type == functionDef){
        return(createDefinitionTree(type, &fd));
    }
    else{
        return(createDefinitionTree(type, &idHold);
    }
}


char* type(void){
    entering("type"); 
    char* t = malloc(sizeof(char) * 5);
    if(!strcmp(currentToken->value, "int")){
        strcpy(t, currentToken->value);
        getNextToken();    
    }
    else if(!strcmp(currentToken->value, "char")){
        strcpy(t, currentToken->value);
        getNextToken();
    }
    else{
        throwStateError("Int Or Char"); 
    }
    exiting("type");
    return(t);
}

functionDefinitionTree functionDefinition(char *type, char* id){
    entering("functionDefinition");  
    functionDefinitionTree fdt = malloc(sizeof(struct functionDefinitionTreeTYpe));

    fdt->type = malloc(sizeof(char) * (strlen(type) + 1));
    strcpy(fdt->type, type); 

    fdt->id = malloc(sizeof(char) * (strlen(id) + 1));
    strcpy(fdt->id, id);

    functionHeader(fdt);
    functionBody(fdt);
    exiting("functionDefinition");
    return(fdt);
}

functionDefinitionTree functionHeader(functionDefinitionTree f){
    entering("functionHeader"); 
    accept('(');
    if ((!strcmp(currentToken->value, "int")) || (!strcmp(currentToken->value, "char"))){
        f = formalParamList(f);
    }
    accept(')');
    exiting("functionHeader");
}

void functionBody(void){
    entering("functionBody");
    statementTree output = malloc(sizeof(struct statementTreeType));
    output = compoundStatement();
    exiting("functionBody");
    return(output);
}

functionDefinitionTree formalParamList(functionDefinitionTree f){
    entering("formalParamList");
    variableDefinitionTree *v = malloc(sizeof(struct variableDefinitionTreeType) * 500);
    char * typeHold = malloc(sizeof(char) * 5);
    char * idHold;
    int i = 0;
    strcpy(typeHold, type());
    if(!strcmp(currentToken->lexeme, "ID")){
        idHold = malloc(sizeof(char) * (strlen(currentLexeme->value) + 1));
        strcpy(idHold, currentLexeme->value);
        v[i] = createVariableDefinitionTree(typeHold, idHold, 1);
        getNextToken();
    }
    else{
        throwStateError("ID");
    }
    while(!strcmp(currentToken->lexeme, "COMMA")){
        accept(',');
        typeHold = malloc(sizeof(char) * 5);
        strcpy(typeHold, type()); 
        if(!strcmp(currentToken->lexeme, "ID")){
            idHold = malloc(sizeof(char) * (strlen(currentLexeme->value) + 1));
            strcpy(idHold, currentLexeme->value);
            v[i] = createVariableDefinitionTree(typeHold, idHold, 1);
            getNextToken();
        }
        else{
            throwStateError("ID");
        }
    }
    exiting("formalParamList");
    f->vDef = v;
    f->varAmount = i+1;
    return(f);
}

statementTree statement(void){
    entering("statement");
    statementTree output = malloc(sizeof(struct statementTreeType));
    if(!strcmp(currentToken->lexeme, "KEYWORD")){
        if(!strcmp(currentToken->value, "break")){
            output->type = breakState;
            output->bst = breakStatement();
        }
        else if(!strcmp(currentToken->value, "if")){
            output->type = ifState;
            output->ist = ifStatement();
        }
        else if(!strcmp(currentToken->value, "return")){
            output->type = returnState;
            output->rst =  returnStatement();
        }
        else if(!strcmp(currentToken->value, "while")){
            output->type = whileState;
            output->wst = whileStatement();
        }
        else if(!strcmp(currentToken->value, "read")){
            output->type = readState;
            output->rst = readStatement();
        }
        else if(!strcmp(currentToken->value, "write")){
            output->type = writeState;
            output->author = writeStatement();
        }
        else if(!strcmp(currentToken->value, "newline")){
            output->type = newLineState; 
            output->nlst = newLineStatement();
        }
        else{
            throwStateError("Statement");
        }
    }
    else if(!strcmp(currentToken->lexeme, "LCURLY")){
        output = compoundStatement();
    }
    else if(!strcmp(currentToken->lexeme, "SEMICOLON")){
        output->type = nullState;
        output->nst = nullStatement();
    }
    else{
        output->type = exprState;
        output->exp = expressionStatement();
    }
    exiting("statement");
    return(output);
}

expressionStatementTree expressionStatement(void){
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

expressionStatementTree expression(void){
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



