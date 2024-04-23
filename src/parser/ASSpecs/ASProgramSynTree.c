//B. Frazier 3/17/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/ASsynTree.h"
#include "../../../include/parser/prettyPrinting.h"
#include "../../../include/cmdLine/TCglobals.h"
#include "../../../include/symbols/TCSymbolTable.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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


void generateProgramTree(programTree pst, FILE *fptr){

    if(debug_codeGen){
        printf("[Generating Program Tree]\n");
        fflush(stdout);
    }

    for(int i = 0; i < strlen(javaClassname); i++){
        javaClassname[i] = tolower(javaClassname[i]);
    }

    fprintf(fptr, ".class  public %s\n", javaClassname); 
    fprintf(fptr, ".super  java/lang/Object\n");
    fprintf(fptr, ".method public static main([Ljava/lang/String;)V\n");  
    fprintf(fptr, ".limit stack %d\n", STACKSIZE);

    //+1 for the scanner object
    fprintf(fptr, ".limit locals %d\n", (getSymbolTableSize(symTable)+1)); 
    
    for(int i = 0; i < pst->numDefs; i++){
        generateDefinitionTree(pst->dTrees[i], fptr);
    }
    
    fprintf(fptr, "return\n"); 
    fprintf(fptr, ".end method"); 

}
