//B. Frazier 3/16/24

#ifndef ASSYNTREE 
    #define ASSYNTREE
    #include "../../include/parser/ASsynTree.h"
#endif

programTree toyCProgram(void);
definitionTree definition(void);
char* type(void);
definitionTree functionDefinition(char*, char*);
functionDefinitionTree functionHeader(functionDefintionTree);
blockStatementTree functionBody(functionDefinitionTree);
functionDefinitionTree formalParamList(functionDefinitionTree);
statementTree statement(void);
expressionStatementTree expressionStatement(void);
breakStatementTree breakStatement(void);
statementTree compoundStatement(void);
statementTree ifStatement(void);
statementTree nullStatement(void);
statementTree returnStatement(void);
statementTree whileStatement(void);
statementTree readStatement(void);
statementTree writeStatement(void);
statementTree newLineStatement(void);
expressionTree expression(void);
expressionTree relopExpression(void);
expressionTree simpleExpression(void);
expressionTree term(void);
expressionTree primary(void);
expressionTree functionCall(void);
int actualParameters(expressionTree * input);

