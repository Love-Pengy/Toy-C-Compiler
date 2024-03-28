//B. Frazier 3/19/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/ASsynTree.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


struct variableDefinitionTreeType{
    char* type;
    char** id;
    int idAmount;
};


variableDefinitionTree initVariableDefinitionTree(void){
    variableDefinitionTree vdt = malloc(sizeof(struct variableDefinitionTreeType));
    vdt->idAmount = 0;
    return(vdt);
}

variableDefinitionTree createVariableDefinitionTree(char *typeSpec, char**idSpec, int idCount){
    variableDefinitionTree vdt = initVariableDefinitionTree();
    vdt->type = malloc(sizeof(char) * (strlen(typeSpec) + 1));
    strcpy(vdt->type, typeSpec);
    vdt->id = malloc(sizeof(char *) * idCount);
    for(int i = 0; i < idCount; i++){
        vdt->id[i] = malloc(sizeof(char) * (strlen(idSpec[i]) + 1));
        strcpy(vdt->id[i], idSpec[i]);
    }
    vdt->idAmount = idCount;
    return(vdt);
}


list variableDefinitionTreeToString(variableDefinitionTree vdt){
    list string = createList();
    listCat(string, "varDef(");
    listCat(string, vdt->type);    
    for(int i = 0; i < (vdt->idAmount-1); i++){
        listCat(string, vdt->id[i]);
    }

    listCat(string, ")\n");
    return(string);
}

