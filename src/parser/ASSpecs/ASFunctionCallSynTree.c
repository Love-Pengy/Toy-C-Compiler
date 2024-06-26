//B. Frazier 3/22/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/prettyPrinting.h"
#include "../../../include/parser/ASsynTree.h"
#include "../../../include/cmdLine/TCglobals.h"
#include <stdlib.h>
#include <string.h>


struct functionCallTreeType{
    char* id;
    expressionTree* exprs;
    int numExprs;
};


functionCallTree initFunctionCallTree(void){
    functionCallTree fct = malloc(sizeof(struct functionCallTreeType));
    fct->exprs = malloc(sizeof(expressionTree) * 100);
    fct->exprs[0] = initExpressionTree();
    fct->numExprs = 0;
    return(fct);
}

void addIdFunctionCallTree(functionCallTree* f, char* id){
    (*f)->id = malloc(sizeof(char) * (strlen(id) + 1));
    strcpy((*f)->id, id);
}

void addExpressionTreeFunctionCallTree(functionCallTree* f, expressionTree* input){
    (*f)->exprs[(*f)->numExprs] = malloc(sizeof(expressionTree));
    (*f)->exprs[(*f)->numExprs] = (*input);
    (*f)->numExprs += 1;
}

functionCallTree createFunctionCallTree(char *ident, expressionTree* exp, int amt){
    functionCallTree fct = initFunctionCallTree();
    fct->id = malloc(sizeof(char) * (strlen(ident) + 1));
    strcpy(fct->id, ident);
    fct->exprs = exp;
    fct->numExprs = amt;
    return(fct);
}

list functionCallTreeToString(functionCallTree fct){
    list string = createList();
    listCat(&string, spaces());
    listCat(&string, "funcCall(\n");
    indent();
    listCat(&string, spaces());
    listCat(&string, fct->id);
    indent();
    listCat(&string, "\n");
    listCat(&string, spaces());
    listCat(&string, "[\n");
    for(int i = 0; i < fct->numExprs; i++){
        llistCat(&string, expressionTreeToString(fct->exprs[i]));
    } 

    listCat(&string, spaces());
    listCat(&string, "]\n");
    outdent();
    outdent();
    listCat(&string, spaces());
    listCat(&string, ")\n");
    return(string);
}

void generateFunctionCallTree(functionCallTree fct, FILE* fptr){

    if(debug_codeGen){
        printf("[CODE GENERATOR] Debugging Function Call\n");
        fflush(stdout);
    }
    //nothing in here unless decide to do EC
}
