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
functionDefinitionTree functionDefinition(char *, char*);
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
        defHold = initDefinitionTree();    
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
    void * ptr = malloc(sizeof(void*));
    char *idHold;
    variableDefinitionTree vdHold = initVariableDefinitionTree();
    functionDefinitionTree fsHold = initFunctionDefinitionTree();
    strcpy(typeSpec, type()); 
    if(!strcmp(currentToken->lexeme, "ID")){ 
        idHold = malloc(sizeof(char) * (strlen(currentToken->value) + 1));
        strcpy(idHold, currentToken->value);
        getNextToken();
        if(!strcmp(currentToken->lexeme, "SEMICOLON")){
            typeProd = variableDef;
            vdHold = createVariableDefinitionTree(typeSpec, &idHold, 1);
            ptr = &vdHold;
            accept(';');
        }
        else{
            typeProd = functionDef;
            fsHold = functionDefinition(typeSpec, idHold);
            ptr = &fsHold;
        }
    }
    else{
        throwStateError("ID");   
    }
    exiting("definition");
    if(typeProd == variableDef){
        return(createDefinitionTree(typeProd, ptr));
    }
    else{
        return(createDefinitionTree(typeProd, ptr));
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
    functionDefinitionTree fd = initFunctionDefinitionTree();
    addIdFunctionDefinition(&fd, id); 
    addTypeFunctionDefinition(&fd, type);
    functionHeader(&fd);
    functionBody(&fd);
    exiting("functionDefinition");
    return(fd);
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
    blockStatementTree output = initBlockStatementTree(); 
    output = compoundStatement();
    statementTree toutput = initStatementTree();
    toutput = createStatementTree(blockState, &output);
    exiting("functionBody");   
    addStatementFunctionDefinition(d, &toutput);    
}

void formalParamList(functionDefinitionTree*v){
    entering("formalParamList");
    char * typeHold = malloc(sizeof(char) * 5);
    char * idHold;
    variableDefinitionTree varDefHold = malloc(sizeof(variableDefinitionTree));
    int i = 0;
    strcpy(typeHold, type());
    if(!strcmp(currentToken->lexeme, "ID")){
        idHold = malloc(sizeof(char) * (strlen(currentToken->value) + 1));
        strcpy(idHold, currentToken->value);
        varDefHold = createVariableDefinitionTree(typeHold, &idHold, 1);
        addVarDefFunctionDefinition(v, &varDefHold);
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
            varDefHold = createVariableDefinitionTree(typeHold, &idHold, 1);
            addVarDefFunctionDefinition(v, &varDefHold);
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
            breakStatementTree hold = initBreakStatementTree();
            hold = breakStatement();
            addBreakStateStatementTree(&output, &hold);
        }
        else if(!strcmp(currentToken->value, "if")){
            ifStatementTree hold = initIfStatementTree();
            hold = ifStatement();
            addIfStateStatementTree(&output, &hold);
        }
        else if(!strcmp(currentToken->value, "return")){
            returnStatementTree hold = initReturnStatementTree();
            hold = returnStatement();
            addReturnStateStatementTree(&output, &hold);
        }
        else if(!strcmp(currentToken->value, "while")){
            whileStatementTree hold = initWhileStatementTree();
            hold = whileStatement();
            addWhileStateStatementTree(&output, &hold);
        }
        else if(!strcmp(currentToken->value, "read")){
            readStatementTree hold = initReadStatementTree();
            hold = readStatement();
            addReadStateStatementTree(&output, &hold);
        }
        else if(!strcmp(currentToken->value, "write")){
            writeStatementTree hold = initWriteStatementTree();
            hold = writeStatement();
            addWriteStateStatementTree(&output, &hold);
        }
        else if(!strcmp(currentToken->value, "newline")){
            newLineStatementTree hold = initNewLineStatementTree();
            hold = newLineStatement();
            addNewlineStateStatementTree(&output, &hold);
        }
        else{
            throwStateError("Statement");
        }
    }
    else if(!strcmp(currentToken->lexeme, "LCURLY")){
        blockStatementTree hold = initBlockStatementTree();
        hold = compoundStatement();
        addBlockStateStatementTree(&output,&hold);
    }
    else if(!strcmp(currentToken->lexeme, "SEMICOLON")){
        nullStatementTree hold = initNullStatementTree();
        hold = nullStatement();
        addNullStateStatementTree(&output, &hold);
    }
    else{
        expressionStatementTree hold = initExpressionStatementTree();
        hold = expressionStatement();
        addExprStateStatementTree(&output, &hold);
    }
    exiting("statement");
    return(output);
}

expressionStatementTree expressionStatement(void){
    entering("expressionStatement");
    expressionTree hold = initExpressionTree();
    hold = expression();
    expressionStatementTree et = createExpressionStatementTree(&hold);
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
    statementTree sHold = initStatementTree();
    variableDefinitionTree vHold = initVariableDefinitionTree();
    while(strcmp(currentToken->lexeme, "RCURLY") != 0){
        if(!strcmp(currentToken->value, "int") || !strcmp(currentToken->value, "char")){
            strcpy(typeHold, type());
            if(!strcmp(currentToken->lexeme, "ID")){
                idHold = malloc(sizeof(char) * (strlen(currentToken->value) + 1));
                strcpy(idHold, currentToken->value);
                getNextToken();
                accept(';');
                vHold = createVariableDefinitionTree(typeHold, &idHold, 1);
                addVarDefBlockStatementTree(&bst, &vHold);
            }
        }
        else{
            sHold = statement();
            addStatementBlockStatementTree(&bst,&sHold);
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
    return(createIfStatementTree(&e, &st, &st1));
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
            temp = createReturnStatementTree(&et);
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
    return(createWhileStatementTree(&eHold, &sHold)); 
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
    expressionTree et1  = initExpressionTree();
    et1 = relopExpression();
    expressionTree et2 = initExpressionTree(); 
    opExpressionTree currentOp = initOpExpressionTree();
    expressionTree output = initExpressionTree();
    currentOp = NULL;
    while(!strcmp(currentToken->lexeme, "ASSIGNOP")){
        operatorTree operator = createOperatorTree(currentToken->value);
        //this needs to be recurssion of some sort because the expression can be another expression
        getNextToken();
        et2 = relopExpression();
        currentOp = createOpExpressionTree(&operator, &et1, &et2);
    }
    exiting("expression");
    if(currentOp == NULL){
        output = et1;
    }
    else{
        output = createExpressionTree(Expr, &currentOp);
    }
    return(output);
}

expressionTree relopExpression(void){
    entering("relopExpression");
    expressionTree re1 = initExpressionTree();
    re1 = simpleExpression();
    expressionTree re2 = initExpressionTree();
    opExpressionTree currentOp = initOpExpressionTree();
    expressionTree output = initExpressionTree();
    operatorTree operator = initOperatorTree();
    currentOp = NULL;
    while(!strcmp(currentToken->lexeme, "RELOP")){
        operator = createOperatorTree(currentToken->value);
        getNextToken(); 
        re2 = simpleExpression();
        currentOp = createOpExpressionTree(&operator, &re1, &re2);
    }
    exiting("relopExpression");
    if(currentOp == NULL){
        output = re1;
    }
    else{
        output = createExpressionTree(Expr, &currentOp);
    }
    return(output);
}

expressionTree simpleExpression(void){
    entering("simpleExpression");
    expressionTree et1 = initExpressionTree();
    et1 = term();
    expressionTree et2 = initExpressionTree();
    opExpressionTree currentOp = initOpExpressionTree();
    expressionTree output = initExpressionTree();
    operatorTree operator = initOperatorTree();
    currentOp = NULL;
    while(!strcmp(currentToken->lexeme, "ADDOP")){
        operator = createOperatorTree(currentToken->value);
        getNextToken();
        et2 = term();
        currentOp = createOpExpressionTree(&operator, &et1, &et2);
    }
    exiting("simpleExpression");
    if(currentOp == NULL){
        output = et1;
    }
    else{
        output = createExpressionTree(Expr, &currentOp);
    }
    return(output);
}

//figure this out before moving on
expressionTree term(void){
    entering("term");
    expressionTree st1 = initExpressionTree();
    st1 = primary();
    expressionTree st2 = initExpressionTree();
    opExpressionTree currentOP = initOpExpressionTree();
    operatorTree operator = initOperatorTree();
    expressionTree output = initExpressionTree();
    currentOP = NULL;
    while(!strcmp(currentToken->lexeme, "MULOP")){
        operator = createOperatorTree(currentToken->value);
        getNextToken();
        st2 = primary();
        currentOP = createOpExpressionTree(&operator,&st1,&st2);  
    }
    exiting("term");
    if(currentOP == NULL){
        output = st1;
    }
    else{
        output = createExpressionTree(Expr, &currentOP);
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
        char * idHold = malloc(sizeof(char) * (strlen(currentToken->value) + 1));
        strcpy(idHold, currentToken->value);
        getNextToken();
        type = ID;
        output = createExpressionTree(type, &idHold);
        if(!strcmp(currentToken->lexeme, "LPAREN")){
            holdf = functionCall(idHold); 
            type = funcCall;
            output = createExpressionTree(type, &holdf);
        } 
    }
    else if(!strcmp(currentToken->lexeme, "NUMBER")){
        type = Number;
        char * hold = malloc(sizeof(char) * (strlen(currentToken->value) + 1));
        strcpy(hold, currentToken->value);
        output = createExpressionTree(type, &hold);
        getNextToken();
    }
    else if(!strcmp(currentToken->lexeme, "STRING")){
        type = StringLiteral;
        char * hold = malloc(sizeof(char) * (strlen(currentToken->value) + 1));
        strcpy(hold, currentToken->value);
        output = createExpressionTree(type, &hold);
        getNextToken();
    }
    else if(!strcmp(currentToken->lexeme, "CHARLITERAL")){
        type = CharLiteral;
        char* hold = malloc(sizeof(char) * (strlen(currentToken->value) + 1));
        hold[0] = '\0';
        strcpy(hold, currentToken->value);
        output = createExpressionTree(type, &hold);
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
        minusTree m = initMinusTree();
        m = createMinusTree(&holde);
        output = createExpressionTree(type, &m);
    }
    else if(!strcmp(currentToken->lexeme, "NOT")){
        type = Not;
        getNextToken();
        holde = primary();
        notTree n = initNotTree();
        n = createNotTree(&holde);
        output = createExpressionTree(type, &n);
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
    //expressionTree * et =  malloc(sizeof(expressionTree) * 100);
    functionCallTree et = initFunctionCallTree();
    addIdFunctionCallTree(&et, id);

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
    return(et); 
}

//this void input is the address of an array of these types
void actualParameters(enum actualParamType type, void* input){
    entering("actualParameters");
    expressionTree hold = initExpressionTree();
    //this should be a bunch of hte other expression types cause its just a general expression
    if(type == writeStatementType){
        hold = expression();
        addExpressionTreeWriteStatementTree((writeStatementTree*)input, &hold);   
    }
    else{
        hold = expression();
        addExpressionTreeFunctionCallTree((functionCallTree*)input, &hold);
    }

    while(!strcmp(currentToken->lexeme, "COMMA")){
        getNextToken();     
        hold = initExpressionTree();
        if(type == writeStatementType){
            hold = expression();
            addExpressionTreeWriteStatementTree((writeStatementTree*)input, &hold);   
        }
        else{
            hold = expression();
            addExpressionTreeFunctionCallTree((functionCallTree*)input, &hold);
        }
    }
    exiting("actualParameters");
}



