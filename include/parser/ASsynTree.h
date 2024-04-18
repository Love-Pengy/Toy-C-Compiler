//B. Frazier 3/16/24

#include "../../lib/dynamicArray/dynamicArray.h"
#include <stdio.h>

#ifndef ASSYNTREE
#define ASSYNTREE

enum actualParamType {writeStatementType, functionCallType};
typedef struct programTreeType *programTree; 
typedef struct definitionTreeType *definitionTree;
typedef struct functionDefinitionTreeType *functionDefinitionTree;  
typedef struct variableDefinitionTreeType *variableDefinitionTree;
typedef struct expressionStatementTreeType *expressionStatementTree;
typedef struct breakStatementTreeType *breakStatementTree;
typedef struct blockStatementTreeType *blockStatementTree;
typedef struct ifStatementTreeType *ifStatementTree;
typedef struct nullStatementTreeType *nullStatementTree;
typedef struct returnStatementTreeType *returnStatementTree;
typedef struct whileStatementTreeType *whileStatementTree;
typedef struct readStatementTreeType *readStatementTree;
typedef struct writeStatementTreeType *writeStatementTree;
typedef struct newLineStatementTreeType *newLineStatementTree;
typedef struct statementTreeType *statementTree;
typedef struct expressionTreeType *expressionTree;
typedef struct functionCallTreeType *functionCallTree;
typedef struct opExpressionTreeType *opExpressionTree;
typedef struct minusTreeType *minusTree;
typedef struct notTreeType *notTree;
typedef struct operatorTreeType *operatorTree;


//definition 
enum defTypeProd {functionDef, variableDef, undefinedType};
definitionTree initDefinitionTree(void);
definitionTree createDefinitionTree(enum defTypeProd, void*);
list definitionTreeToString(definitionTree);
void generateDefinitionTree(definitionTree, FILE*);

//Program 
programTree initProgramTree(void);
void addDefinitionProgramTree(programTree *, definitionTree*);
programTree createProgramTree(definitionTree*, int);
list programTreeToString(programTree);
void generateProgramTree(programTree, FILE*);

//funcdef 
functionDefinitionTree initFunctionDefinitionTree(void);
void addTypeFunctionDefinition(functionDefinitionTree*,char *);
void addIdFunctionDefinition(functionDefinitionTree*, char *);
void addVarDefFunctionDefinition(functionDefinitionTree*, variableDefinitionTree*);
void addStatementFunctionDefinition(functionDefinitionTree*, statementTree*);
void generateFunctionDefinitionTree(functionDefinitionTree, FILE*);


functionDefinitionTree createFunctionDefinitionTree(char*, char*, variableDefinitionTree*, int, statementTree*);
list functionDefinitionTreeToString(functionDefinitionTree);

//varDef 
variableDefinitionTree initVariableDefinitionTree(void);
variableDefinitionTree createVariableDefinitionTree(char *, char**, int);
list variableDefinitionTreeToString(variableDefinitionTree);
void generateVariableDefinitionTree(variableDefinitionTree, FILE*);


//exprState 
expressionStatementTree initExpressionStatementTree(void);
expressionStatementTree createExpressionStatementTree(expressionTree*);
list expressionStatementTreeToString(expressionStatementTree);

//breakState 
breakStatementTree initBreakStatementTree(void);
breakStatementTree createBreakStatementTree(void);
list breakStatementTreeToString(breakStatementTree);

//blockState 
void addStatementBlockStatementTree(blockStatementTree*, statementTree*);
void addVarDefBlockStatementTree(blockStatementTree*, variableDefinitionTree*);
blockStatementTree initBlockStatementTree(void);
blockStatementTree createBlockStatementTree(variableDefinitionTree *, int, statementTree *, int);
list blockStatementTreeToString(blockStatementTree);
void generateBlockStatementTree(blockStatementTree, FILE*);

//ifState 
ifStatementTree initIfStatementTree(void);
list ifStatementTreeToString(ifStatementTree);
ifStatementTree createIfStatementTree(expressionTree*, statementTree*, statementTree*);
void generateIfStatementTree(ifStatementTree, FILE*);

//nullState
nullStatementTree initNullStatementTree(void);
nullStatementTree createNullStatementTree(void);
list nullStatementTreeToString(nullStatementTree);
void generateNullStatementTree(nullStatementTree, FILE*);

//returnState
returnStatementTree initReturnStatementTree(void);
returnStatementTree createReturnStatementTree(expressionTree*);
list returnStatementTreeToString(returnStatementTree);

//whileState
whileStatementTree initWhileStatementTree(void);
whileStatementTree createWhileStatementTree(expressionTree*, statementTree*);
list whileStatementTreeToString(whileStatementTree);


//readState
readStatementTree initReadStatementTree(void);
void addIdReadStatement(readStatementTree *, char *);
list readStatementTreeToString(readStatementTree);
readStatementTree createReadStatementTree(char**, int);
void generateReadStatement(readStatementTree, FILE*);


//writeState
writeStatementTree initWriteStatementTree(void);
void addExpressionTreeWriteStatementTree(writeStatementTree*, expressionTree*);
list writeStatementTreeToString(writeStatementTree);
writeStatementTree createWriteStatementTree(expressionTree*,int);

//newLineState
newLineStatementTree initNewLineStatementTree(void);
list newLineStatementTreeToString(newLineStatementTree);
newLineStatementTree createNewLineStatementTree(void);

//statement
enum statementType {exprState, breakState, blockState, ifState, nullState, returnState, whileState, readState, writeState, newLineState, undefined};
statementTree initStatementTree(void);
void addExprStateStatementTree(statementTree*, expressionStatementTree*);
void addBreakStateStatementTree(statementTree*, breakStatementTree*);
void addBlockStateStatementTree(statementTree*, blockStatementTree*);
void addIfStateStatementTree(statementTree*, ifStatementTree*);
void addNullStateStatementTree(statementTree*, nullStatementTree*);
void addReturnStateStatementTree(statementTree*, returnStatementTree*);
void addWhileStateStatementTree(statementTree*, whileStatementTree*);
void addWriteStateStatementTree(statementTree*, writeStatementTree*);
void addNewlineStateStatementTree(statementTree*, newLineStatementTree*);
void addReadStateStatementTree(statementTree*, readStatementTree*);
list statementTreeToString(statementTree);
statementTree createStatementTree(enum statementType,  void*);
void generateStatementTree(statementTree, FILE*);

//expression
expressionStatementTree createExpressionStatementTree(expressionTree*);
list expressionStatementTreeToString(expressionStatementTree);
void generateExpressionStatementTree(expressionStatementTree, FILE*);

//funcCall
functionCallTree initFunctionCallTree(void);
list functionCallTreeToString(functionCallTree);
functionCallTree createFunctionCallTree(char *, expressionTree*, int);
void addIdFunctionCallTree(functionCallTree*, char*);
void addExpressionTreeFunctionCallTree(functionCallTree*, expressionTree*);
void generateFunctionCallTree(functionCallTree, FILE*);

//expr
opExpressionTree initOpExpressionTree(void);
list opExpressionTreeToString(opExpressionTree);
opExpressionTree createOpExpressionTree(operatorTree*, expressionTree*, expressionTree*);
char* getOperatorFromTree(opExpressionTree);

//minus
minusTree initMinusTree(void);
list minusTreeToString(minusTree);
minusTree createMinusTree(expressionTree*);
expressionTree getMinusExpression(minusTree);
void generateMinusTree(minusTree, FILE*);


//not
notTree initNotTree(void);
list notTreeToString(notTree);
notTree createNotTree(expressionTree*);
void generateNotTree(notTree, FILE*);
//Operator
operatorTree initOperatorTree(void);
list operatorTreeToString(operatorTree);
operatorTree createOperatorTree(char*);
char* getOperator(operatorTree);

//expression
enum expressionType {Number, ID, CharLiteral, StringLiteral, funcCall, Expr, Minus, Not, undefinedExpression};
enum expressionType getExpressionType(expressionTree);
expressionTree initExpressionTree(void);
expressionTree createExpressionTree(enum expressionType, void*);
list expressionTreeToString(expressionTree);
void generateExpressionTree(expressionTree, FILE*);

#endif
