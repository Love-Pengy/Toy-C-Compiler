//B. Frazier 3/19/24

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


struct variableDefinitionTreeType{
    char* type;
    char** id;
    int idAmount;
};


variableDefinitionTree createVariableDefinitionTree(char *typeSpec, char**idSpec, int idCount){
    variableDefinitionTree vdt = malloc(sizeof(struct variableDefinitionTreeType));
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
    for(int i = 0; i < vdt->idAmount; i++){
        listCat(string, vdt->id[i]);
    }
    listCat(string, ")\n");
    return(string);
}

