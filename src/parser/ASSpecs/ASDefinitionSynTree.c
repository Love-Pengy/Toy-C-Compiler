//B. Frazier 3/18/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/ASsynTree.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../../include/parser/prettyPrinting.h"


//defTypeProd = {functionDef, variableDef}
struct definitionTreeType{
    enum defTypeProd type;
    union {
        functionDefinitionTree fDef;
        variableDefinitionTree vDef;
    };
};


definitionTree initDefinitionTree(void){
    definitionTree dst = malloc(sizeof(struct definitionTreeType));
    dst->type = undefinedType; 
    return(dst);
}

definitionTree createDefinitionTree(enum defTypeProd prodType, void* prod){
    definitionTree dst = initDefinitionTree();  
    switch(prodType){
        case functionDef: 
            dst->type = prodType;
            dst->fDef = *(functionDefinitionTree*)prod;
            break;
        case variableDef:
            dst->type = prodType;
            dst->vDef = *(variableDefinitionTree*)prod;
            break; 
        default:
            printf("internal error\n");
            fflush(stdout);
            exit(EXIT_FAILURE);
    }
    return(dst);
}


list definitionTreeToString(definitionTree dst){
    list string = createList();
    listCat(&string, spaces());
    listCat(&string, "definition(\n");
    indent();
    switch(dst->type){
        case functionDef: 
            llistCat(&string, functionDefinitionTreeToString(dst->fDef));
            break;
        case variableDef:
            llistCat(&string, variableDefinitionTreeToString(dst->vDef));
            break;
        default:
            listCat(&string, "[error]\n");
            break; 
    }
    outdent();
    listCat(&string, spaces());
    listCat(&string, ")\n");
    return(string);
}


