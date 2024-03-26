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

definitionTree functionDefinition(char *type, char* id){
    entering("functionDefinition");  
    functionDefinitionTree fdt = malloc(sizeof(struct functionDefinitionTreeTYpe));

    fdt->type = malloc(sizeof(char) * (strlen(type) + 1));
    strcpy(fdt->type, type); 

    fdt->id = malloc(sizeof(char) * (strlen(id) + 1));
    strcpy(fdt->id, id);

    functionHeader(fdt);
    functionBody(fdt);
    exiting("functionDefinition");
    return(createDefinitionTree(functionDef, fdt));
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

blockStatementTree functionBody(functionDefinitionTree f){
    entering("functionBody");
    //create a statement tree with the blockStatement
    blockStatementTree output = compoundStatement();
    exiting("functionBody");
    return(output);
}

functionDefinitionTree formalParamList(functionDefinitionTree f){
    entering("formalParamList");
    variableDefinitionTree *v = malloc(sizeof(struct variableDefinitionTreeType));
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
    expressionStatementTree et = expression();
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
    return(createStatementTree(breakState, createBreakStatementTree()));
}

//blockstatement
statementTree compoundStatement(void){
    entering("compoundStatement");
    accept('{');
    char * typeHold = malloc(sizeof(char) * 5);
    char * idHold;
    variableDefinitionTree * vHold = malloc(sizeof(struct variableDefinitionTreeType));
    int numDef = 0;
    statementTree * sHold = malloc(sizeof(struct statementTreeType));
    int numStat = 0;
    while(strcmp(currentToken->lexeme, "RCURLY") != 0){
        if(!strcmp(currentToken->value, "int") || !strcmp(currentToken->value, "char")){
            strcpy(typeHold, type());
            if(!strcmp(currentToken->lexeme, "ID")){
                idHold = malloc(sizeof(char) * (strlen(currentToken->value) + 1));
                strcpy(idHold, currentToken->value);
                getNextToken();
                accept(';');
                vHold[numDef] = createVariableDefinitionTree(typeHold, idHold, 1);
                numDef++;
            }
        }
        else{
            statementTree[numStat] = statement();
            numStat++;
        }
    }
    accept('}');
    exiting("compoundStatement");
    return(createStatementTree(blockState, createBlockStatementTree(vHold, numDef, sHold, numStat)));
}

statementTree ifStatement(void){
    entering("ifStatement");
    expressionTree e = malloc(sizeof(struct expressionTreeType));
    statementTree st = malloc(sizeof(struct statementTreeType));
    statementTree st1 = malloc(sizeof(struct statementTreeType));
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
    return(createStatementTree(ifState, createIfStatementTree(e, st, st1)));
}

statementTree nullStatement(void){
    entering("nullStatement");
    accept(';');
    exiting("nullStatement");
    return(createStatementTree(nullState, createNullStatementTree()));
}

statementTree returnStatement(void){
    entering("returnStatement");  
    enum statementType type;
    if(!strcmp(currentToken->value, "return")){
        getNextToken();
        if(strcmp(currentToken->lexeme, "SEMICOLON")){
            expressionTree et = expression();  
            type = returnState;
            returnStatementTree temp = createReturnStatementTree(et);
        }
        else{
            type = returnState;
            returnStatementTree temp = createReturnStatementTree(NULL);
        }
        accept(';');
    }
    else{
        throwStateError("return");
    }
    exiting("returnStatement");
    return(createStatementTree(type, temp));
}

statementTree whileStatement(void){
    entering("whileStatement");
    expressionTree eHold = malloc(sizeof(struct expressionTreeType));
    statementTree sHold = malloc(sizeof(struct statementTreeType));
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
    return(createStatementTree(whileState, createWhileStatementTree(eHold, sHold))); 
}

statementTree readStatement(void){
    entering("readStatement");
    char ** idHold;
    int numHold = 0;
    if(!strcmp(currentToken->value, "read")){
        getNextToken();
        accept('(');
        if(!strcmp(currentToken->lexeme, "ID")){
            idHold[numHold] = malloc(sizeof(char) * (strlen(currentToken->value) + 1));
            strcpy(idHold[numHold], currentToken->value);
            numHold++;
            getNextToken();
        }
        else{
            throwStateError("ID");
        }
        while(!strcmp(currentToken->lexeme, "COMMA")){
            accept(',');
            if(!strcmp(currentToken->lexeme, "ID")){
                idHold[numHold] = malloc(sizeof(char) * (strlen(currentToken->value) + 1));
                strcpy(idHold[numHold], currentToken->value);
                numHold++;
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
    return(createStatementTree(readState, createReadStatementTree(idHold, numHold)));
}

statementTree writeStatement(void){
    entering("writeStatement"); 
    expressionTree *et = malloc(sizeof(struct expressionTreeType));
    if(!strcmp(currentToken->value, "write")){
        getNextToken();
        accept('(');
        int size = actualParameters(et);
        accept(')');
        accept(';');
    }
    else{
        throwStateError("write");
    }
    exiting("writeStatement");
    return(createStatementTree(writeState, (createWriteStatementTree(et, size))));
}

statementTree newLineStatement(void){
    entering("newLineStatement");
    if(!strcmp(currentToken->value, "newline")){
        getNextToken();
        accept(';');
    }
    else{
        throwStateError("newline");
    }
    exiting("newLineStatement");
    return(createStatementTree(newLineState(createNewLineStatementTree())));
}

expressionTree expression(void){
    //both relops and the operator are going to be part of the opExpressionTree and then the opExpressionTree goes into the expressionTree
    entering("expression");
    expressionTree et1 = relopExpression();
    expressionTree et2; 
    opExpressionTree currentOp = NULL;
    while(!strcmp(currentToken->lexeme, "ASSIGNOP")){
        operatorTree operator = createOperatorTree(currentToken->value);
        //this needs to be recurssion of some sort because the expression can be another expression
        getNextToken();
        expressionTree et2 = relopExpression();
        currentOp = createOpExpressionTree(operator, et1, et2);
    }
    exiting("expression");
    if(currentOp == NULL){
        expressionTree output = createExpressionTree(Expr, et1);
    }
    else{
        expressionTree output = createExpressionTree(Expr, currentOp);
    }
}

expressionTree relopExpression(void){
    entering("relopExpression");
    expressionTree re1 = simpleExpression();
    expressionTree re2;
    opExpessionTree currentOp = NULL;

    while(!strcmp(currentToken->lexeme, "RELOP")){
        operatorTree operator = createOperatorTree(currentToken->value);
        getNextToken(); 
        re2 = simpleExpression();
        currentOp = createOpExpressionTree(operator, re1, re2);
    }
    exiting("relopExpression");
    if(currentOp == NULL){
        expressionTree output = createExpressionTree(Expr, re1);
    }
    else{
        expressionTree output = createExpressionTree(Expr, re2);
    }
    return(output);
}

expressionTree simpleExpression(void){
    entering("simpleExpression");
    expressionTree et1 = term();
    exressionTree et2 = NULL;
    opExpressionTree currentOp = NULL;
    while(!strcmp(currentToken->lexeme, "ADDOP")){
        operatorTree operator = createOperatorTree(currentToken->value);
        getNextToken();
        expressionTree et2 = term();
        currentOp = createOpExpressionTree(operator, et1, et2);
    }
    exiting("simpleExpression");
    if(currentOP == NULL){
        exprerssion output = createExpressionTree(Expr, et1);
    }
    else{
        expressionTree output = createExpressionTree(Expr, currentOp);
    }
    return(output);
}

//figure this out before moving on
expessionTree term(void){
    entering("term");
    expressionTree st1 = primary();
    expressionTree st2;
    opExpressionTree currentOP = NULL;
    //what I'm going to do here is keep expanding the right statement until the end 
    //expression can hold and op expression
    while(!strcmp(currentToken->lexeme, "MULOP")){
        operatorTree operator = createOperatorTree(currentToken->value);
        getNextToken();
        expressionTree st2 = primary();
        currentOP = createOpExpressionTree(operator,st1,st2);  
    }
    exiting("term");
    if(currentOP == NULL){
        expressionTree output = createExpressionTree(Expr, st1);
    }
    else{
        expressionTree output = createExpressionTree(Expr, currentOP);
    }
    return(output); 
}

//expression
expressionTree primary(void){
    entering("primary");
    enum expressionType type;
    expressionTree output;
    if(!strcmp(currentToken->lexeme, "ID")){
        char * idHold = malloc(sizeof(char) * (strlen(currentToken->value));
        strcpy(idHold, currentToken->value);
        getNextToken();
        if(!strcmp(currentToken->lexeme, "LPAREN")){
            functionCallTree hold = functionCall(idHold); 
            type = funcCall;
            output = createExpressionTree(type, hold);
        } 
    }
    else if(!strcmp(currentToken->lexeme, "NUMBER")){
        type = Number;
        char * hold = malloc(sizeof(char) * (strlen(currentToken->value) + 1)):
        strcpy(hold, currentToken->value);
        output = createExpressionTree(type, hold);
        getNextToken();
    }
    else if(!strcmp(currentToken->lexeme, "STRING")){
        type = StringLiteral;
        char * hold = malloc(sizeof(char) * (strlen(currentToken->value) + 1)):
        strcpy(hold, currentToken->value);
        output = createExpressionTree(type, hold);
        getNextToken();
    }
    else if(!strcmp(currentToken->lexeme, "CHARLITERAL")){
        type = CharLiteral;
        char * hold = malloc(sizeof(char) * (strlen(currentToken->value) + 1)):
        strcpy(hold, currentToken->value);
        output = createExpressionTree(type, hold);
        getNextToken();
    }
    else if(!strcmp(currentToken->lexeme, "LPAREN")){
        accept('(');
        expressionTree hold = expression();
        char * hold = malloc(sizeof(char) * (strlen(currentToken->value) + 1)):
        strcpy(hold, currentToken->value);
        output = createExpressionTree(type, hold);
        accept(')'); 
    }
    else if((!strcmp(currentToken->value, "-")) || (!strcmp(currentToken->lexeme, "NOT"))){
        getNextToken();
        expressionTree hold = primary();
        char * hold = malloc(sizeof(char) * (strlen(currentToken->value) + 1)):
        strcpy(hold, currentToken->value);
        output = createExpressionTree(type, hold);
    }
    else{
        throwStateError("ID, NUMBER, STRING, CHARLITERAL, LPAREN, -, or NOT");
    }
    exiting("primary");
    return(createExpressionTree(type, hold));
}

expressionTree functionCall(char * id){
    entering("functionCall");
    accept('(');
    expressionTree * et = malloc(sizeof(struct expressionTreeType));
    int amount = 0;
    if(!strcmp(currentToken->lexeme, "ID")){
        amount = actualParameters(et);
    }
    else if(!strcmp(currentToken->lexeme, "NUMBER")){
        amount = actualParameters(et);
    }
    else if(!strcmp(currentToken->lexeme, "STRING")){
        amount = actualParameters(et);
    }
    else if(!strcmp(currentToken->lexeme, "CHARLITERAL")){
        amount = actualParameters(et);
    }
    else if(!strcmp(currentToken->lexeme, "LPAREN")){
        amount = actualParameters(et);
    }
    else if((!strcmp(currentToken->value, "-")) || (!strcmp(currentToken->lexeme, "NOT"))){
        amount = actualParameters(et);
    }
    accept(')');
    exiting("functionCall");
    return(createExpressionTree(funcCall, createFunctionCallTree(id, et, amount))); 
}

int actualParameters(expressionTree * input){
    entering("actualParameters");
    int i = 0;
    input[i] = expression();
    i++;
    while(!strcmp(currentToken->lexeme, "COMMA")){
        getNextToken(); 
        input[i] = expression();
    }
    exiting("actualParameters");
    return(i);
}



