//B. Frazier 3/22/24

#include "../../../lib/dynamicArray/dynamicArray.h"
#include "../../../include/parser/prettyPrinting.h"
#include "../../../include/parser/ASsynTree.h"
#include "../../../include/cmdLine/TCglobals.h"
#include <string.h>
#include <stdlib.h>


struct opExpressionTreeType{
    operatorTree op;
    expressionTree exp1;
    expressionTree exp2;
};

char* getOperatorFromTree(opExpressionTree opTree){
    return(getOperator(opTree->op));  
}

opExpressionTree initOpExpressionTree(void){
    opExpressionTree oet = malloc(sizeof(struct opExpressionTreeType));
    return(oet);
}

opExpressionTree createOpExpressionTree(operatorTree* oper, expressionTree* ex1, expressionTree* ex2){
    opExpressionTree oet = initOpExpressionTree();
    oet->op = (*oper);
    oet->exp1 = (*ex1);
    oet->exp2 = (*ex2);
    return(oet);
}

list opExpressionTreeToString(opExpressionTree oe){
    list string = createList();
    listCat(&string, spaces());
    listCat(&string, "expr(\n");
    indent();
    llistCat(&string, expressionTreeToString(oe->exp1)); 
    llistCat(&string, operatorTreeToString(oe->op));
    llistCat(&string, expressionTreeToString(oe->exp2)); 
    outdent();
    listCat(&string, spaces());
    listCat(&string, ")\n");
    return(string);
}

//possible operators + - * / % || && <= < = > >= != 
void generateOpExpressionTree(opExpressionTree oe, FILE* fptr){
    if(!strcmp(getOperator(oe->op), "+")){
        generateExpressionTree(oe->exp1, fptr);
        generateExpressionTree(oe->exp2, fptr);
        fprintf(fptr, "iadd\n");
    }
    else if(!strcmp(getOperator(oe->op), "-")){
        generateExpressionTree(oe->exp1, fptr);
        generateExpressionTree(oe->exp2, fptr);
        fprintf(fptr, "isub\n");
    }
    else if(!strcmp(getOperator(oe->op), "*")){
        generateExpressionTree(oe->exp1, fptr);
        generateExpressionTree(oe->exp2, fptr);
        fprintf(fptr, "imul\n");
    }
    else if(!strcmp(getOperator(oe->op), "/")){
        generateExpressionTree(oe->exp1, fptr);
        generateExpressionTree(oe->exp2, fptr);
        fprintf(fptr, "idiv\n");
    }
    else if(!strcmp(getOperator(oe->op), "%")){
        generateExpressionTree(oe->exp1, fptr);
        generateExpressionTree(oe->exp2, fptr);
        fprintf(fptr, "irem\n");
    }
    else if(!strcmp(getOperator(oe->op), "||")){
        generateExpressionTree(oe->exp1, fptr);
        fprintf(fptr, "bipush 1\n");
        fprintf(fptr, "if_cmpeq Label%d\n", CURRENTLABEL);
        generateExpressionTree(oe->exp2, fptr);
        fprintf(fptr, "bipush 1\n");
        fprintf(fptr, "if_cmpeq Label%d\n", CURRENTLABEL);
        fprintf(fptr, "bipush 0\n");
        fprintf(fptr, "goto Label%d\n", CURRENTLABEL+1);
        fprintf(fptr, "Label%d:\n", CURRENTLABEL);
        fprintf(fptr, "bipush 1\n");
        fprintf(fptr, "Label%d:\n", CURRENTLABEL+1); 
    }
    else if(!strcmp(getOperator(oe->op), "&&")){
        generateExpressionTree(oe->exp1, fptr);
        fprintf(fptr, "bipush 1\n");
        fprintf(fptr, "if_cmpeq Label%d\n", CURRENTLABEL);
        fprintf(fptr, "bipush 0\n");
        fprintf(fptr, "goto Label%d\n", CURRENTLABEL+2);

        fprintf(fptr, "Label%d:\n", CURRENTLABEL);
        generateExpressionTree(oe->exp2, fptr);
        fprintf(fptr, "bipush 1\n");
        fprintf(fptr, "if_cmpeq Label%d\n", CURRENTLABEL+1);
        fprintf(fptr, "bipush 0\n");
        fprintf(fptr, "goto Label%d\n", CURRENTLABEL+2);
        
        fprintf(fptr, "Label%d:\n", CURRENTLABEL+1);
        fprintf(fptr, "bipush 1\n");

        fprintf(fptr, "goto Label%d\n", CURRENTLABEL+2);

        fprintf(fptr, "Label%d:\n", CURRENTLABEL+2); 
    }
    else if(!strcmp(getOperator(oe->op), "<=")){
    }
    else if(!strcmp(getOperator(oe->op), "<")){
    }
    //ASSIGNMENT OPERATOR
    else if(!strcmp(getOperator(oe->op), "=")){
    }
    else if(!strcmp(getOperator(oe->op), ">")){
    }
    else if(!strcmp(getOperator(oe->op), ">=")){
    }
    else if(!strcmp(getOperator(oe->op), "!=")){
    }
    else{
        //throw error
    }

}
