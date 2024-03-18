#ifndef DYNAMICARRAY_H
    #include "../../lib/dynamicArray/dynamicArray.h"
#endif

#ifndef ASSYNTREE_H
    #include "../../include/parser/ASsynTree.h"
#endif

#ifndef STDLIB_H
    #include <stdlib.h>
#endif

#ifndef DYNAMICARRAY_H
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


definitionTree createDefinitionTree(enum defTypeProd, void* prod){
    definitionTree dst = malloc(sizeof(struct definitionTreeType));
    switch(defTypeProd){
        case functionDef: 
            dst->type = defTypeProd;
            dst->fDef = &prod;
            break;
        case variableDef:
            dst->type = defTypeProd;
            dst->vDef = &prod;
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
            listCat(string, functionDefinitionTreeToString(dst->fDef));
            break;
        case variableDef:
            listCat(string, variableDefinitionTreeToString(dst->vDef));
            break;
        default:
            listCat(string, "[error]\n");
            break; 
    }
    strcat(string, ")\n");
}


