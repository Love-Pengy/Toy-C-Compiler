//B. Frazier 3/16/24

#include "../../lib/dynamicArray/dynamicArray.h"

#ifndef ASSYNTREE
#define ASSYNTREE

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
enum defTypeProd {functionDef, variableDef};
definitionTree initDefinitionTree(void);
definitionTree createDefinitionTree(enum defTypeProd, void*);
list definitionTreeToString(definitionTree);

//Program 
programTree initProgramTree(void);
void addDefinitionProgramTree(programTree *, definitionTree);
programTree createProgramTree(definitionTree*, int);
list programTreeToString(programTree);

//funcdef 
functionDefinitionTree initFunctionDefinitionTree(void);
void addTypeFunctionDefinition(functionDefinitionTree,char *);
void addIdFunctionDefinition(functionDefinitionTree, char *);
void addVarDefFunctionDefinition(functionDefinitionTree, variableDefinitionTree);
void addStatementFunctionDefinition(functionDefinitionTree, statementTree);

functionDefinitionTree createFunctionDefinitionTree(char*, char*, variableDefinitionTree*, int, statementTree);
list functionDefinitionTreeToString(functionDefinitionTree);

//varDef 
variableDefinitionTree createVariableDefinitionTree(char *, char**, int);
list variableDefinitionTreeToString(variableDefinitionTree);

//exprState 
expressionStatementTree createExpressionStatementTree(expressionTree);
list expressionStatementTreeToString(expressionStatementTree);

//breakState 
breakStatementTree createBreakStatementTree(void);
list breakStatementTreeToString(breakStatementTree);

//blockState 
void addStatementBlockStatementTree(blockStatementTree*, statementTree);
void addVarDefBlockStatementTree(blockStatementTree*, variableDefinitionTree);
blockStatementTree initBlockStatementTree(void);
blockStatementTree createBlockStatementTree(variableDefinitionTree *, int, statementTree *, int);
list blockStatementTreeToString(blockStatementTree);

//ifState 
list ifStatementTreeToString(ifStatementTree);
ifStatementTree createIfStatementTree(expressionTree, statementTree, statementTree);

//nullState
nullStatementTree createNullStatementTree(void);
list nullStatementTreeToString(nullStatementTree);

//returnState
returnStatementTree initReturnStatementTree(void);
returnStatementTree createReturnStatementTree(expressionTree);
list returnStatementTreeToString(returnStatementTree);

//whileState
whileStatementTree createWhileStatementTree(expressionTree, statementTree);
list whileStatementTreeToString(whileStatementTree);


//readState
readStatementTree initReadStatementTree(void);
void addIdReadStatement(readStatementTree *, char *);
list readStatementTreeToString(readStatementTree);
readStatementTree createReadStatementTree(char**, int);


//writeState
list writeStatementTreeToString(writeStatementTree);
writeStatementTree createWriteStatementTree(expressionTree*,int);

//newLineState
list newLineStatementTreeToString(newLineStatementTree);
newLineStatementTree createNewLineStatementTree(void);

//statement
enum statementType {exprState, breakState, blockState, ifState, nullState, returnState, whileState, readState, writeState, newLineState};
statementTree initStatementTree(void);
void addExprStateStatementTree(statementTree*, expressionStatementTree);
void addBreakStateStatementTree(statementTree*, breakStatementTree);
void addBlockStateStatementTree(statementTree*, blockStatementTree);
void addIfStateStatementTree(statementTree*, ifStatementTree);
void addNullStateStatementTree(statementTree*, nullStatementTree);
void addReturnStateStatementTree(statementTree*, returnStatementTree);
void addWhileStateStatementTree(statementTree*, whileStatementTree);
void addWriteStateStatementTree(statementTree*, writeStatementTree);
void addNewlineStateStatementTree(statementTree*, newLineStatementTree);
void addReadStateStatementTree(statementTree*, readStatementTree);
list statementTreeToString(statementTree);
statementTree createStatementTree(enum statementType,  void*);

//expression
expressionStatementTree createExpressionStatementTree(expressionTree);
list expressionStatementTreeToString(expressionStatementTree);

//funcCall
functionCallTree initFunctionCallTree(void);
list functionCallTreeToString(functionCallTree);
functionCallTree createFunctionCallTree(char *, expressionTree*, int);

//expr
opExpressionTree initOpExpressionTree(void);
list opExpressionTreeToString(opExpressionTree);
opExpressionTree createOpExpressionTree(operatorTree, expressionTree, expressionTree);

//minus
list minusTreeToString(minusTree);
minusTree createMinusTree(expressionTree);

//not
list notTreeToString(notTree);
notTree createNotTree(expressionTree);

//Operator
operatorTree initOperatorTree(void);
list operatorTreeToString(operatorTree);
operatorTree createOperatorTree(char*);

//expression
enum expressionType {Number, ID, CharLiteral, StringLiteral, funcCall, Expr, Minus, Not};
expressionTree initExpressionTree(void);
expressionTree createExpressionTree(enum expressionType, void*);
list expressionTreeToString(expressionTree);

#endif
