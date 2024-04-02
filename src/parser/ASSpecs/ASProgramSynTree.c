//B. Frazier 3/17/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/ASsynTree.h"
#include <stdlib.h>
#include "../../../include/parser/prettyPrinting.h"
//this can hold 0 or more definitions
struct programTreeType{
    //array that holds all of the definitions
    definitionTree * dTrees; 
    int numDefs;
};


programTree initProgramTree(void){
    programTree pst = malloc(sizeof(struct programTreeType));
    pst->dTrees = malloc(sizeof(definitionTree) * 100);
    pst->numDefs = 0;
    return(pst);
}

void addDefinitionProgramTree(programTree* pt, definitionTree* d){
    (*pt)->dTrees[(*pt)->numDefs] = malloc(sizeof(definitionTree));
    (*pt)->dTrees[(*pt)->numDefs] = (*d);
    (*pt)->numDefs++;
}

programTree createProgramTree(definitionTree *definitions, int amount){
    programTree pst = initProgramTree();
    pst->dTrees = malloc(sizeof(definitions));
    pst->dTrees = definitions;
    pst->numDefs = amount;
    return(pst);
}

list programTreeToString(programTree pst){  
    list string = createList(); 
    listCat(&string, spaces());
    listCat(&string, "prog(\n"); 
    indent();
    for(int i = 0; i < pst->numDefs; i++){
        llistCat(&string, definitionTreeToString(pst->dTrees[i]));
    }
    outdent();
    listCat(&string, spaces());
    listCat(&string, ")\n");
    return(string);
}
