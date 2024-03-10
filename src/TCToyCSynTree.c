#ifndef SYNTREE_H
    #include "../include/synTree.h"
#endif
#ifndef STDLIB_H
    #include <stdlib.h>
#endif
#ifndef STDIO_H
    #include <stdio.h>
#endif

struct toyCProgramSynTreeType {
    definitionSynTree definitionTree; 
};

toyCProgramSynTree createToyCProgramSynTree(definitionSynTree dSyn){

    if(debug_parser){
        printf("Entering toyCProgram\n");
    }

    toyCProgramSynTree tcTree = malloc(sizeof(struct toyCProgramSynTreeType));
    tcTree->definitionTree = dSyn;

    if(debug_parser){
        printf("Exiting toyCProgram\n");
    }

    return(tcTree);
}

