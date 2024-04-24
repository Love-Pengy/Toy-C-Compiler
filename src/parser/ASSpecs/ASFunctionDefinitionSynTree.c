//B. Frazier 3/18/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/prettyPrinting.h"
#include "../../../include/parser/ASsynTree.h"
#include "../../../include/cmdLine/TCglobals.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//function definition consists of an id, a type, 0 or moer variable definitions, or a statement 
struct functionDefinitionTreeType{
    char *type;
    char* id;
    //array of variable definitions
    variableDefinitionTree* vDef;
    int varAmount;
    statementTree sDef;
};

functionDefinitionTree initFunctionDefinitionTree(void){
    functionDefinitionTree output = malloc(sizeof(struct functionDefinitionTreeType));
    output->vDef = malloc(sizeof(variableDefinitionTree) * 100);
    output->varAmount = 0;
    return(output);
}

void addTypeFunctionDefinition(functionDefinitionTree *f,char *add){
    (*f)->type = malloc(sizeof(char) * (strlen(add) + 1));
    strcpy((*f)->type, add);
}

void addIdFunctionDefinition(functionDefinitionTree *f, char *add){
    (*f)->id = malloc(sizeof(char) * (strlen(add) + 1));
    strcpy((*f)->id, add);
}

void addVarDefFunctionDefinition(functionDefinitionTree *f, variableDefinitionTree *add){
    (*f)->vDef[(*f)->varAmount] = malloc(sizeof(variableDefinitionTree));
    (*f)->vDef[(*f)->varAmount] = (*add);
    (*f)->varAmount++;
}

void addStatementFunctionDefinition(functionDefinitionTree *f, statementTree *add){
    (*f)->sDef = (*add);
}

//if there aren't any variable definitions then the var definitions passed will be NULL
functionDefinitionTree createFunctionDefinitionTree(char *identifier, char *type, variableDefinitionTree* v, int amount, statementTree* s){
    functionDefinitionTree output = initFunctionDefinitionTree();
    output->id = malloc(sizeof(char) * (strlen(identifier) + 1));
    strcpy(output->id, identifier);
    output->type = malloc(sizeof(char) * (strlen(type) + 1));
    strcpy(output->type, type);
    output->vDef = v;
    if(output->vDef == NULL){
        output->varAmount = 0;
    }
    output->sDef = (*s);
    output->varAmount = amount;
    return(output);
}


list functionDefinitionTreeToString(functionDefinitionTree fst){
    list string = createList();
    listCat(&string, spaces());
    listCat(&string, "funcDef(\n");
    indent();
    listCat(&string, spaces());
    listCat(&string, (fst)->type);    
    listCat(&string, " ");
    listCat(&string, (fst)->id);
    listCat(&string, " \n");
    indent();
    if((fst)->varAmount){
        for(int i = 0; i < (fst)->varAmount; i++){
            llistCat(&string, variableDefinitionTreeToString(((fst)->vDef[i])));
        }
    }
    llistCat(&string, statementTreeToString((fst)->sDef));
    outdent();
    listCat(&string, spaces());
    listCat(&string, ")\n");
    return(string);
}

void generateFunctionDefinitionTree(functionDefinitionTree fst, FILE* fptr){
    //header variables go in the symbol table therefore we don't need to do anything here 
    if(debug_codeGen){
        printf("[CODE GENERATOR] Generating Function Definition\n");
        fflush(stdout);
    }
    generateStatementTree(fst->sDef, fptr);
}
