//B. Frazier 3/16/24

#ifndef DYNAMICARRAY
    #define DYNAMICARRAY
    #include "../../lib/dynamicArray/dynamicArray.h"
#endif

typedef struct programTreeType *programTree; 
typedef struct definitionTreeType *definitionTree;

//definition 
definitionTree createDefinitionTree(enum defTypeProd, void*);
char *definitionTreeToString(definitionTree);
enum defTypeProd {functionDef, variableDef};

//Program 
programTree createProgramTree(definitionTree*);
list programTreeToString(programTree);


//funcdef 
typedef struct functionDefinitionTreeType *functionDefinitionTree;  
//Type 
typedef struct typeTreeType *typeDefinitionTree;
//Statement 
typedef struct statementTreeType *statementDefinitionTree;
//varDef 
typedef struct variableDefinitionTreeType *variableDefinitionTree;
//exprState 
typedef struct expressionStatementTreeType *expressionStatementTree;
//breakState 
typedef struct breakStatementTreeType *breakStatementTree;
//blockState 
typedef struct blockStatementTreeType *blockStatementTree;
//ifState 
typedef struct ifStatementTreeType *ifStatementTree;
//nullState
typedef struct nullStatementTreeType *nullStatementTree;
//returnState
typedef struct returnStatementTreeType *returnStatementTree;
//whileState
typedef struct whileStatementTreeType *whileStatementTree;
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


