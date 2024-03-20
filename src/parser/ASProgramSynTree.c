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
    int numDefs;
};


programTree createProgramTree(definitionTree *definitions, int amount){
    programTree pst = malloc(sizeof(struct programTreeType));
    pst->dTrees = malloc(sizeof(definitions));
    pst->dTrees = definitions;
    pst->numDefs = amount;
    return(pst);
}

list programTreeToString(programTree pst){  
    list string = createList(); 
    listCat(string, "prog("); 

    for(int i = 0; i < pst->numDefs; i++){
        listCat(string, definitionTreeToString(pst->dTrees[i]));
    }

    listCat(string, ")\n");
    return(string);
}
