//B. Frazier 3/17/24

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


//this can hold 0 or more definitions
struct programTreeType{
    //array that holds all of the definitions
    definitionTree * dTrees; 
};


programTree createProgramTree(definitionTree *definitions){
    programTree pst = malloc(sizeof(struct programTreeType));
    pst->dTrees = malloc(sizeof(definitions));
    pst->dTrees = definitions;
    return(pst);
}

list programTreeToString(programTree pst){  
    int defSize = sizeof(pst->dTrees)/sizeof(definitionTree);
    list string = createList(); 
    listCat(string, "prog("); 

    for(int i = 0; i < defSize; i++){
        listCat(string, definitionTreeToString(&(pst->dTrees[i])));
    }

    listCat(string, ")\n");
    return(string);
}
