//B. Frazier 3/16/24

#include "../../include/parser/ASsynTree.h"
programTree toyCProgram(void);
definitionTree definition(void);
char* type(void);
definitionTree functionDefinition(char*, char*);
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
expressionTree functionCall(char *);
int actualParameters(expressionTree**);

