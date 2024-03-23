//B. Frazier 3/16/24

#ifndef DYNAMICARRAY
    #define DYNAMICARRAY
    #include "../../lib/dynamicArray/dynamicArray.h"
#endif

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

//definition 
definitionTree createDefinitionTree(enum defTypeProd, void*);
char *definitionTreeToString(definitionTree);
enum defTypeProd {functionDef, variableDef};

//Program 
programTree createProgramTree(definitionTree*, int);
list programTreeToString(programTree);

//funcdef 
functionDefinitionTree createFunctionDefinitionTree(char*, char*, variableDefinitionTree*, int, char*);
list functionDefinitionTreeToString(functionDefinitionTree);

//varDef 
variableDefinitionTree createVariableDefinitionTree(char *, char**, int);
list variableDefinitionTreeToString(variableDefinitionTree);

//exprState 
expressionStatementTree createExpressionStatementTree(expressionTree );
list expressionStatementTreeToString(expressionStatementTree);

//breakState 
breakStatementTree createBreakStatementTree(void);
list breakStatementTreeToString(breakStatementTree);

//blockState 
blockStatementTree createBlockStatementTree(variableDefinitionTree *, int, statementTree *, int);
list blockStatementTreeToString(blockStatementTree);

//ifState 
list ifStatementTreeToString(ifStatementTree);
ifStatementTree createIfStatementTree(enum expressionTypeEnum, void*, char*, char*);

//nullState
nullStatementTree createNullStatementTree(void);
list nullStatementTreeToString(nullStatementTree);

//returnState
returnStatementTree createReturnStatementTree(expressionTree);
list returnStatementTreeToString(returnStatementTree);

//whileState
whileStatementTree createWhileStatementTree(expressionTree, statementTree);
list whileStatementTreeToString(whileStatementTree);


//readState
list readStatementToString(readStatementTree);
readStatementTree createReadStatementTree(char**, int);


//writeState
list writeStatementTreeToString(writeStatementTree);
writeStatementTree createWriteStatementTree(expressionTree*,int);

//newLineState
list newLineStatementTreeToString(newLineStatementTree);
newLineStatementTree createNewLineStatementTreeType(void);

//statement
enum statementType {exprState, breakState, blockState, ifState, nullState, returnState, whileState, readState, writeState, newLineState};
list statementTreeToString(statementTree);
statementTree createStatementTree(enum statementType,  void*);

//Expression
enum expressionType {Number, ID, CharLiteral, StringLiteral, funcCall, Expr, Minus, Not};
expressionStatementTree createExpressionStatementTree(enum expressionType, void*);
list expressionTreeToString(expressionTree);

//funcCall
list functionCallTreeToString(functionCallTree);
functionCallTree createFunctionCallTree(char *, expressionTree*, int);

//expr
list opExpressionTreeToString(opExpressionTree);
opExpressionTree createOpExpressionTree(operatorTree, expressionTree, expressionTree);

//minus
typedef struct minusTreeType *minusTree;
//not
typedef struct notTreeType *notTree;
//Operator
typedef struct operatorTreeType *operatorTree;


