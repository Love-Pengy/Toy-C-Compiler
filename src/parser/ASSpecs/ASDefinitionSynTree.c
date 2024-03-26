//B. Frazier 3/18/24

#ifndef DYNAMICARRAY
    #define DYNAMICARRAY
    #include "../../lib/dynamicArray/dynamicArray.h"
#endif

#ifndef ASSYNTREE
    #define ASSYNTREE
    #include "../../include/parser/ASsynTree.h"
#endif

#ifndef STDLIB
    #define STDLIB
    #include <stdlib.h>
#endif

#ifndef STDIO
    #define STDIO
    #include <stdio.h>
#endif

#ifndef DYNAMICARRAY_H
    #define DYNAMICARRAY
    #include "../../lib/dynamicArray/dynamicArray.h"
#endif


//defTypeProd = {functionDef, variableDef}
struct definitionTreeType{
    enum defTypeProd type;
    union {
        functionDefinitionTree fDef;
        variableDefinitionTree vDef;
    };
};


definitionTree createDefinitionTree(enum defTypeProd prodType, void* prod){
    definitionTree dst = malloc(sizeof(struct definitionTreeType));
    switch(prodType){
        case functionDef: 
            dst->type = prodType;
            dst->fDef = *prod;
            break;
        case variableDef:
            dst->type = prodType;
            dst->vDef = *prod;
            break; 
        default:
            printf("internal error\n");
            fflush(stdout);
            exit(EXIT_FAILURE);
    }
    return(dst);
}


char *definitionTreeToString(definitionTree dst){
    list string = createList();
    listCat(string, "definition(\n");
    switch(dst->type){
        case functionDef: 
            llistCat(string, functionDefinitionTreeToString(dst->fDef));
            break;
        case variableDef:
            llistCat(string, variableDefinitionTreeToString(dst->vDef));
            break;
        default:
            listCat(string, "[error]\n");
            break; 
    }
    listCat(string, ")\n");
}

