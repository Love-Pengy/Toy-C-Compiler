//B. Frazier 3/16/24

#include <stdlib.h>
#include "../../include/lexer/TClexer.h"
#include "../../include/cmdLine/TCglobals.h"
#include "../../include/parser/ASsynTree.h"
#include <string.h>


token currentToken;

//make it so that it knows stuff exists
programTree toyCProgram(void);
definitionTree definition(void);
char* type(void);
definitionTree functionDefinition(char *, char*);
void functionHeader(functionDefinitionTree*);
void functionBody(functionDefinitionTree*);
void formalParamList(functionDefinitionTree*);
statementTree statement(void);
expressionStatementTree expressionStatement(void);
breakStatementTree breakStatement(void);
blockStatementTree compoundStatement(void);
ifStatementTree ifStatement(void);
nullStatementTree nullStatement(void);
returnStatementTree returnStatement(void);
whileStatementTree whileStatement(void);
readStatementTree readStatement(void);
writeStatementTree writeStatement(void);
newLineStatementTree newLineStatement(void);
expressionTree expression(void);
expressionTree relopExpression(void);
expressionTree simpleExpression(void);
expressionTree term(void);
expressionTree primary(void);
functionCallTree functionCall(char*);
void actualParameters(enum actualParamType,void*);

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
        if(!strcmp(exiteeLikeSomeTea, "toyCProgram")){
            printf("[PARSER] Parse Has Completed\n");
            printf("[PARSER] exiting %s\n", exiteeLikeSomeTea);    
        }
        printf("[PARSER] exiting %s\n", exiteeLikeSomeTea);
        fflush(stdout);
    }
}

//think of this like A() its the state itself. The leaf is defined elsewhere
programTree toyCProgram(void){
    entering("toyCProgram");
    programTree output = initProgramTree(); 
    getNextToken();    
    definitionTree defHold = initDefinitionTree();    
    while(strcmp(currentToken->lexeme, "EOF")){ 
        defHold = definition();
        addDefinitionProgramTree(&output,&defHold);
    }

    exiting("toyCProgram");
    return(output);
}


definitionTree definition(void){
    entering("definition");
    enum defTypeProd typeProd;

    //char is four letters
    char *typeSpec = malloc(sizeof(char) * 5);
    definitionTree fd = initDefinitionTree();
    variableDefinitionTree vd = initVariableDefinitionTree();
    char *idHold;
    strcpy(typeSpec, type()); 
    if(!strcmp(currentToken->lexeme, "ID")){ 
        char *idHold = malloc(sizeof(char) * (strlen(currentToken->value) + 1));
        strcpy(idHold, currentToken->value);
        getNextToken();
        if(!strcmp(currentToken->lexeme, "SEMICOLON")){
            typeProd = variableDef;
            vd = createVariableDefinitionTree(typeSpec, &idHold, 1);
            accept(';');
        }
        else{
            typeProd = functionDef;
            fd = initDefinitionTree(); 
            fd = functionDefinition(typeSpec, idHold);
            
        }
    }
    else{
        throwStateError("ID");   
    }
    exiting("definition");
    if(typeProd == variableDef){
        return(createDefinitionTree(typeProd, &vd));
    }
    else{
        return(createDefinitionTree(typeProd, &fd));
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

definitionTree functionDefinition(char *type, char* id){
    entering("functionDefinition");  
    functionDefinitionTree fd = initFunctionDefinitionTree();

    functionHeader(&fd);
    functionBody(&fd);

    exiting("functionDefinition");
    return(createDefinitionTree(functionDef, fd));
}

void functionHeader(functionDefinitionTree* d){
    entering("functionHeader"); 
    accept('(');
    if ((!strcmp(currentToken->value, "int")) || (!strcmp(currentToken->value, "char"))){
        formalParamList(d);
    }
    accept(')');
    exiting("functionHeader");
}

void functionBody(functionDefinitionTree* d){
    entering("functionBody");
    blockStatementTree output = compoundStatement();
    statementTree toutput = createStatementTree(blockState, output);
    exiting("functionBody");   
    addStatementFunctionDefinition(*d, toutput);    
}

void formalParamList(functionDefinitionTree*v){
    entering("formalParamList");
    char * typeHold = malloc(sizeof(char) * 5);
    char * idHold;
    int i = 0;
    strcpy(typeHold, type());
    if(!strcmp(currentToken->lexeme, "ID")){
        idHold = malloc(sizeof(char) * (strlen(currentToken->value) + 1));
        strcpy(idHold, currentToken->value);
        addVarDefFunctionDefinition(*v, createVariableDefinitionTree(typeHold, &idHold, 1));
        i++;
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
            idHold = malloc(sizeof(char) * (strlen(currentToken->value) + 1));
            strcpy(idHold, currentToken->value);
            addVarDefFunctionDefinition(*v,createVariableDefinitionTree(typeHold, &idHold, 1));
            i++;
            getNextToken();
        }
        else{
            throwStateError("ID");
        }
    }
    exiting("formalParamList");
}

statementTree statement(void){
    entering("statement");
    statementTree output = initStatementTree();
    if(!strcmp(currentToken->lexeme, "KEYWORD")){
        if(!strcmp(currentToken->value, "break")){
            addBreakStateStatementTree(&output, breakStatement());
        }
        else if(!strcmp(currentToken->value, "if")){
            addIfStateStatementTree(&output, ifStatement());
        }
        else if(!strcmp(currentToken->value, "return")){
            addReturnStateStatementTree(&output, returnStatement());
        }
        else if(!strcmp(currentToken->value, "while")){
            addWhileStateStatementTree(&output, whileStatement());
        }
        else if(!strcmp(currentToken->value, "read")){
            addReadStateStatementTree(&output, readStatement());
        }
        else if(!strcmp(currentToken->value, "write")){
            addWriteStateStatementTree(&output, writeStatement());
        }
        else if(!strcmp(currentToken->value, "newline")){
            addNewlineStateStatementTree(&output, newLineStatement());
        }
        else{
            throwStateError("Statement");
        }
    }
    else if(!strcmp(currentToken->lexeme, "LCURLY")){
        addBlockStateStatementTree(&output,compoundStatement());
    }
    else if(!strcmp(currentToken->lexeme, "SEMICOLON")){
        addNullStateStatementTree(&output, nullStatement());
    }
    else{
        addExprStateStatementTree(&output, expressionStatement());
    }
    exiting("statement");
    return(output);
}

expressionStatementTree expressionStatement(void){
    entering("expressionStatement");
    
    expressionStatementTree et = createExpressionStatementTree(expression());
    accept(';');
    exiting("expressionStatement");
    return(et);
}

breakStatementTree breakStatement(void){
    entering("breakStatement");
    if(!strcmp(currentToken->value, "break")){
        getNextToken();
        accept(';');
    }
    else{
        throwStateError("break");
    }
    exiting("breakStatement");
    return(createBreakStatementTree());
}

//blockstatement
blockStatementTree compoundStatement(void){
    entering("compoundStatement");
    accept('{');
    blockStatementTree bst = initBlockStatementTree();
    char * typeHold = malloc(sizeof(char) * 5);
    char * idHold;
    while(strcmp(currentToken->lexeme, "RCURLY") != 0){
        if(!strcmp(currentToken->value, "int") || !strcmp(currentToken->value, "char")){
            strcpy(typeHold, type());
            if(!strcmp(currentToken->lexeme, "ID")){
                idHold = malloc(sizeof(char) * (strlen(currentToken->value) + 1));
                strcpy(idHold, currentToken->value);
                getNextToken();
                accept(';');
                addVarDefBlockStatementTree(&bst, createVariableDefinitionTree(typeHold, &idHold, 1));
            }
        }
        else{
            addStatementBlockStatementTree(&bst,statement());
        }
    }
    accept('}');
    exiting("compoundStatement");
    return(bst);
}

ifStatementTree ifStatement(void){
    entering("ifStatement");
    expressionTree e = initExpressionTree();
    statementTree st = initStatementTree();
    statementTree st1 = initStatementTree();
    st1 = NULL;
    if(!strcmp(currentToken->value, "if")){
        getNextToken();
        accept('(');
        e = expression();
        accept(')');
        st = statement();
        if(!strcmp(currentToken->value, "else")){
            getNextToken();
            st1 = statement();
        }
    }
    else{
        throwStateError("if");
    }
    exiting("ifStatement");
    return(createIfStatementTree(e, st, st1));
}

nullStatementTree nullStatement(void){
    entering("nullStatement");
    accept(';');
    exiting("nullStatement");
    return(createNullStatementTree());
}

returnStatementTree returnStatement(void){
    entering("returnStatement");  
    returnStatementTree temp = initReturnStatementTree();
    if(!strcmp(currentToken->value, "return")){
        getNextToken();
        if(strcmp(currentToken->lexeme, "SEMICOLON")){
            expressionTree et = expression();  
            temp = createReturnStatementTree(et);
        }
        else{
            temp = createReturnStatementTree(NULL);
        }
        accept(';');
    }
    else{
        throwStateError("return");
    }
    exiting("returnStatement");
    return(temp);
}

whileStatementTree whileStatement(void){
    entering("whileStatement");
    expressionTree eHold = initExpressionTree();
    statementTree sHold = initStatementTree();
    if(!strcmp(currentToken->value, "while")){
        getNextToken();
        accept('(');
        eHold = expression();
        accept(')');
        sHold = statement();
    }
    else{
        throwStateError("while");
    }
    exiting("whileStatement");
    return(createWhileStatementTree(eHold, sHold)); 
}

readStatementTree readStatement(void){
    entering("readStatement");
    readStatementTree output = initReadStatementTree();
    if(!strcmp(currentToken->value, "read")){
        getNextToken();
        accept('(');
        if(!strcmp(currentToken->lexeme, "ID")){
            addIdReadStatement(&output, currentToken->value);
            getNextToken();
        }
        else{
            throwStateError("ID");
        }
        while(!strcmp(currentToken->lexeme, "COMMA")){
            accept(',');
            if(!strcmp(currentToken->lexeme, "ID")){
                addIdReadStatement(&output, currentToken->value);
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
    return(output);
}

writeStatementTree writeStatement(void){
    entering("writeStatement"); 
    writeStatementTree et = initWriteStatementTree();
    if(!strcmp(currentToken->value, "write")){
        getNextToken();
        accept('(');
        actualParameters(writeStatementType, &et);
        accept(')');
        accept(';');
    }
    else{
        throwStateError("write");
    }
    exiting("writeStatement");
    return(et);
}

newLineStatementTree newLineStatement(void){
    entering("newLineStatement");
    if(!strcmp(currentToken->value, "newline")){
        getNextToken();
        accept(';');
    }
    else{
        throwStateError("newline");
    }
    exiting("newLineStatement");
    return(createNewLineStatementTree());
}

expressionTree expression(void){
    //both relops and the operator are going to be part of the opExpressionTree and then the opExpressionTree goes into the expressionTree
    entering("expression");
    expressionTree et1 = relopExpression();
    expressionTree et2 = initExpressionTree(); 
    opExpressionTree currentOp = initOpExpressionTree();
    expressionTree output = initExpressionTree();
    while(!strcmp(currentToken->lexeme, "ASSIGNOP")){
        operatorTree operator = createOperatorTree(currentToken->value);
        //this needs to be recurssion of some sort because the expression can be another expression
        getNextToken();
        et2 = relopExpression();
        currentOp = createOpExpressionTree(operator, et1, et2);
    }
    exiting("expression");
    if(currentOp == NULL){
        output = createExpressionTree(Expr, et1);
    }
    else{
        output = createExpressionTree(Expr, currentOp);
    }
    return(output);
}

expressionTree relopExpression(void){
    entering("relopExpression");
    expressionTree re1 = simpleExpression();
    expressionTree re2 = initExpressionTree();
    opExpressionTree currentOp = initOpExpressionTree();
    expressionTree output = initExpressionTree();
    while(!strcmp(currentToken->lexeme, "RELOP")){
        operatorTree operator = createOperatorTree(currentToken->value);
        getNextToken(); 
        re2 = simpleExpression();
        currentOp = createOpExpressionTree(operator, re1, re2);
    }
    exiting("relopExpression");
    if(currentOp == NULL){
        output = createExpressionTree(Expr, re1);
    }
    else{
        output = createExpressionTree(Expr, re2);
    }
    return(output);
}

expressionTree simpleExpression(void){
    entering("simpleExpression");
    expressionTree et1 = term();
    expressionTree et2 = initExpressionTree();
    opExpressionTree currentOp = initOpExpressionTree();
    expressionTree output = initExpressionTree();
    operatorTree operator = initOperatorTree();
    while(!strcmp(currentToken->lexeme, "ADDOP")){
        operator = createOperatorTree(currentToken->value);
        getNextToken();
        et2 = term();
        currentOp = createOpExpressionTree(operator, et1, et2);
    }
    exiting("simpleExpression");
    if(currentOp == NULL){
        output = createExpressionTree(Expr, et1);
    }
    else{
        output = createExpressionTree(Expr, currentOp);
    }
    return(output);
}

//figure this out before moving on
expressionTree term(void){
    entering("term");
    expressionTree st1 = primary();
    expressionTree st2 = initExpressionTree();
    opExpressionTree currentOP = initOpExpressionTree();
    operatorTree operator = initOperatorTree();
    expressionTree output = initExpressionTree();
    while(!strcmp(currentToken->lexeme, "MULOP")){
        operator = createOperatorTree(currentToken->value);
        getNextToken();
        st2 = primary();
        currentOP = createOpExpressionTree(operator,st1,st2);  
    }
    exiting("term");
    if(currentOP == NULL){
        output = createExpressionTree(Expr, st1);
    }
    else{
        output = createExpressionTree(Expr, currentOP);
    }
    return(output); 
}

//expression
expressionTree primary(void){
    entering("primary");
    enum expressionType type;
    expressionTree output = initExpressionTree();
    functionCallTree holdf = initFunctionCallTree();
    expressionTree holde = initExpressionTree();
    if(!strcmp(currentToken->lexeme, "ID")){
        char * idHold = malloc(sizeof(char) * (strlen(currentToken->value)));
        strcpy(idHold, currentToken->value);
        getNextToken();
        if(!strcmp(currentToken->lexeme, "LPAREN")){
            holdf = functionCall(idHold); 
            type = funcCall;
            output = createExpressionTree(type, holdf);
        } 
    }
    else if(!strcmp(currentToken->lexeme, "NUMBER")){
        type = Number;
        char * hold = malloc(sizeof(char) * (strlen(currentToken->value) + 1));
        strcpy(hold, currentToken->value);
        output = createExpressionTree(type, hold);
        getNextToken();
    }
    else if(!strcmp(currentToken->lexeme, "STRING")){
        type = StringLiteral;
        char * hold = malloc(sizeof(char) * (strlen(currentToken->value) + 1));
        strcpy(hold, currentToken->value);
        output = createExpressionTree(type, hold);
        getNextToken();
    }
    else if(!strcmp(currentToken->lexeme, "CHARLITERAL")){
        type = CharLiteral;
        char * hold = malloc(sizeof(char) * (strlen(currentToken->value) + 1));
        strcpy(hold, currentToken->value);
        output = createExpressionTree(type, hold);
        getNextToken();
    }
    else if(!strcmp(currentToken->lexeme, "LPAREN")){
        accept('(');
        output = expression();
        accept(')'); 
    }
    else if((!strcmp(currentToken->value, "-"))){
        type = Minus;
        getNextToken();
        holde = primary();
        output = createExpressionTree(type, createMinusTree(holde));
    }
    else if(!strcmp(currentToken->lexeme, "NOT")){
        type = Not;
        getNextToken();
        holde = primary();
        output = createExpressionTree(type, createNotTree(holde));
    }
    else{
        throwStateError("ID, NUMBER, STRING, CHARLITERAL, LPAREN, -, or NOT");
    }
    exiting("primary");
    return(output);
}

functionCallTree functionCall(char * id){
    entering("functionCall");
    accept('(');
    expressionTree * et =  malloc(sizeof(expressionTree) * 100);
    int amount = 0;
    if(!strcmp(currentToken->lexeme, "ID")){
         actualParameters(functionCallType, &et);
    }
    else if(!strcmp(currentToken->lexeme, "NUMBER")){
        actualParameters(functionCallType, &et);
    }
    else if(!strcmp(currentToken->lexeme, "STRING")){
        actualParameters(functionCallType, &et);
    }
    else if(!strcmp(currentToken->lexeme, "CHARLITERAL")){
        actualParameters(functionCallType, &et);
    }
    else if(!strcmp(currentToken->lexeme, "LPAREN")){
        actualParameters(functionCallType, &et);
    }
    else if((!strcmp(currentToken->value, "-")) || (!strcmp(currentToken->lexeme, "NOT"))){
        actualParameters(functionCallType, &et);
    }
    accept(')');
    exiting("functionCall");
    return(createFunctionCallTree(id, et, amount)); 
}

void actualParameters(enum actualParamType type, void* input){
    entering("actualParameters");
    if(type == writeStatementType){
        addExpressionTreeWriteStatementTree((writeStatementTree*)input, expression());   
    }
    else{
        addExpressionTreeWriteStatementTree((writeStatementTree*)input, expression());
    }
    while(!strcmp(currentToken->lexeme, "COMMA")){
        getNextToken();     
        if(type == writeStatementType){
            addExpressionTreeWriteStatementTree((writeStatementTree*)input, expression());   
        }
        else{
            addExpressionTreeWriteStatementTree((writeStatementTree*)input, expression());
        }
    }
    exiting("actualParameters");
}



