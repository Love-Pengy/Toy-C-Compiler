//B. Frazier 3/18/24

#ifndef DYNAMICARRAY
    #define DYNAMICARRAY
    #include "../../lib/dynamicArray/dynamicArray.h"
#endif

#ifndef ASSYNTREE
    #define ASSYNTREE
    #include "../../include/parser/ASsynTree.h"
#endif

#ifndef STRING
    #define STRING
    #include <string.h>
#endif

#ifndef STDLIB
    #define STDLIB
    #include <stdlib.h>
#endif

//function definition consists of an id, a type, 0 or moer variable definitions, or a statement 
struct functionDefinitionTreeType{
    char *type;
    char* id;
    //array of variable definitions
    variableDefinitionTree* vDef;
    int varAmount;
    char* sDef;
};


//if there aren't any variable definitions then the var definitions passed will be NULL
functionDefinitionTree createFunctionDefinitionTree(char *identifier, char *type, variableDefinitionTree* v, int amount, char* s){
    functionDefinitionTree output = malloc(sizeof(struct functionDefinitionTreeType));
    output->id = malloc(sizeof(char) * (strlen(identifier) + 1));
    strcpy(output->id, identifier);
    output->type = malloc(sizeof(char) * (strlen(type) + 1));
    strcpy(output->type, type);
    output->vDef = malloc(sizeof(v) + 1);
    output->vDef = v;
    output->sDef = malloc(sizeof(char) * (strlen(s) + 1));
    strcpy(output->sDef, s);
    output->varAmount = amount;
    return(output);
}


list functionDefinitionTreeToString(functionDefinitionTree fst){
    list string = createList();
    listCat(string, "funcDef(");
    listCat(string, fst->type);    
    listCat(string, fst->id);
    for(int i = 0; i < fst->varAmount; i++){
        listCat(string, variableDefinitionTreeToString(fst->vDef[i]));
    }
    listCat(string, fst->sDef);
    listCat(string, ")\n");
    return(string);
}

