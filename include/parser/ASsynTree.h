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
expressionStatementTree createExpressionStatementTree(char *);
list expressionStatementTreeToString(expressionStatementTree);

//breakState 
breakStatementTree createBreakStatementTree(void);
list breakStatementTreeToString(breakStatementTree);

//blockState 
blockStatementTree createBlockStatementTree(variableDefinitionTree *, int, char **, int);
list blockStatementTreeToString(blockStatementTree);

//ifState 
//specifier = number | id | charLiteral | stringLiteral
enum expressionTypeEnum {Specifier, FuncCall, Expr, Minus, Not}; 
list ifStatementTreeToString(ifStatementTree ist);
ifStatementTree createIfStatementTree(enum expressionTypeEnum, void*, char*, char*);

//nullState
nullStatementTree createNullStatementTree(void);
list nullStatementTreeToString(nullStatementTree);

//returnState
returnStatementTree createReturnStatementTree(expressionTree);
list returnStatementTreeToString(returnStatementTree);

//whileState
whileStatementTree createWhileStatementTree(expressionTree expr, statementTree stt);
list whileStatementTreeToString(whileStatementTree ws);

//readState
typedef struct readStatementTreeType *readStatementTree;
//writeState
typedef struct writeStatementTreeType *writeStatementTree;
//newLineState
typedef struct newLineStatementTreeType *newLineTree;
//Expression
typedef struct expressionTreeType *expressionTree;
//funcCall
typedef struct functionCallTreeType *functionCallTree;
//expr
typedef struct opExpressionTreeType *opExpressionTree;
//minus
typedef struct minusTreeType *minusTree;
//not
typedef struct notTreeType *notTree;
//Operator
typedef struct operatorTreeType *operatorTree;


