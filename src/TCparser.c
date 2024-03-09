#ifndef TCLEXER_H
    #include "../include/TClexer.h"
#endif

token currentToken;

void throwError(char expected){
    printf("%d :", getLineNum());
    printf("%s\n", getCurrentLine());

    for(int i = 0; i < getPos(); i++){
        printf(" ");
    }

    printf("^ '%c' expected\n", expected); 
}

void accept(char terminal){
    if(currentToken == currentToken->value){
        getLexeme();
    }
    else{
        throwError(terminal);
    }

}




toyCProgramSynTree getSynTree(FILE* fp){
    currentToken = getLexeme();    
    toyCProgramSynTree tree = toyCProgram();
    return(tree);
}
