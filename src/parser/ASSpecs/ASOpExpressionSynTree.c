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
    
    if(debug_codeGen){
        printf("[CODE GENERATOR] Generating Op Expression Tree\n");
        fflush(stdout);
    }

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
        fprintf(fptr, "if_icmpeq Label%d\n", CURRENTLABEL);
        generateExpressionTree(oe->exp2, fptr);
        fprintf(fptr, "bipush 1\n");
        fprintf(fptr, "if_icmpeq Label%d\n", CURRENTLABEL);
        fprintf(fptr, "bipush 0\n");
        fprintf(fptr, "goto Label%d\n", CURRENTLABEL+1);
        fprintf(fptr, "Label%d:\n", CURRENTLABEL);
        fprintf(fptr, "bipush 1\n");
        fprintf(fptr, "Label%d:\n", CURRENTLABEL+1); 
        CURRENTLABEL += 2;
    }
    else if(!strcmp(getOperator(oe->op), "&&")){
        int label1 = CURRENTLABEL;
        int label2 = CURRENTLABEL+1;
        int label3 = CURRENTLABEL+2;
        CURRENTLABEL += 3;
        generateExpressionTree(oe->exp1, fptr);
        fprintf(fptr, "bipush 1\n");
        fprintf(fptr, "if_icmpeq Label%d\n", label1);
        fprintf(fptr, "bipush 0\n");
        fprintf(fptr, "goto Label%d\n", label3);

        fprintf(fptr, "Label%d:\n", label1);
        generateExpressionTree(oe->exp2, fptr);
        fprintf(fptr, "bipush 1\n");
        fprintf(fptr, "if_icmpeq Label%d\n", label2);
        fprintf(fptr, "bipush 0\n");
        fprintf(fptr, "goto Label%d\n", label3);
        
        fprintf(fptr, "Label%d:\n", label2);
        fprintf(fptr, "bipush 1\n");
        fprintf(fptr, "goto Label%d\n", label3);

        fprintf(fptr, "Label%d:\n", label3); 

    }
    else if(!strcmp(getOperator(oe->op), "<=")){
        generateExpressionTree(oe->exp1, fptr);
        generateExpressionTree(oe->exp2, fptr);
        fprintf(fptr, "if_icmpgt Label%d\n", CURRENTLABEL);
        fprintf(fptr, "bipush 1\n");
        fprintf(fptr, "goto Label%d\n", CURRENTLABEL+1);
        fprintf(fptr, "Label%d:\n", CURRENTLABEL);
        fprintf(fptr, "bipush 0\n");
        fprintf(fptr, "Label%d:\n", CURRENTLABEL+1);
        CURRENTLABEL += 2;
    }
    else if(!strcmp(getOperator(oe->op), "<")){
        generateExpressionTree(oe->exp1, fptr);
        generateExpressionTree(oe->exp2, fptr);
        fprintf(fptr, "if_icmpge Label%d\n", CURRENTLABEL);
        fprintf(fptr, "bipush 1\n");
        fprintf(fptr, "goto Label%d\n", CURRENTLABEL+1);
        fprintf(fptr, "Label%d:\n", CURRENTLABEL);
        fprintf(fptr, "bipush 0\n");
        fprintf(fptr, "Label%d:\n", CURRENTLABEL+1);
        CURRENTLABEL += 2;
    }
    //ASSIGNMENT OPERATOR
    else if(!strcmp(getOperator(oe->op), "=")){
        //check if left side is an id first
        if(!(getExpressionType(oe->exp1) == ID)){
            printf("ERROR: Left Side of Assignment Is Not ID\n");
            fflush(stdout);
            exit(EXIT_FAILURE);
        }
        int index = getIdIndexFromExpression(oe->exp1);
        generateExpressionTree(oe->exp2, fptr);
        
        if(index > 3){
            fprintf(fptr, "%s%d\n", "istore ", index);
        }
        else{
            fprintf(fptr, "%s%d\n", "istore_", index);
        }
    }
    else if(!strcmp(getOperator(oe->op), ">")){
        generateExpressionTree(oe->exp1, fptr);
        generateExpressionTree(oe->exp2, fptr);
        fprintf(fptr, "if_icmple Label%d\n", CURRENTLABEL);
        fprintf(fptr, "bipush 1\n");
        fprintf(fptr, "goto Label%d\n", CURRENTLABEL+1);
        fprintf(fptr, "Label%d:\n", CURRENTLABEL);
        fprintf(fptr, "bipush 0\n");
        fprintf(fptr, "Label%d:\n", CURRENTLABEL+1);
        CURRENTLABEL += 2;    
    }
    else if(!strcmp(getOperator(oe->op), ">=")){
        generateExpressionTree(oe->exp1, fptr);
        generateExpressionTree(oe->exp2, fptr);
        fprintf(fptr, "if_icmplt Label%d\n", CURRENTLABEL);
        fprintf(fptr, "bipush 1\n");
        fprintf(fptr, "goto Label%d\n", CURRENTLABEL+1);
        fprintf(fptr, "Label%d:\n", CURRENTLABEL);
        fprintf(fptr, "bipush 0\n");
        fprintf(fptr, "Label%d:\n", CURRENTLABEL+1);
        CURRENTLABEL += 2;    
    }
    else if(!strcmp(getOperator(oe->op), "!=")){
        generateExpressionTree(oe->exp1, fptr);
        generateExpressionTree(oe->exp2, fptr);
        fprintf(fptr, "if_icmpeq Label%d\n", CURRENTLABEL);
        fprintf(fptr, "bipush 1\n");
        fprintf(fptr, "goto Label%d\n", CURRENTLABEL+1);
        fprintf(fptr, "Label%d:\n", CURRENTLABEL);
        fprintf(fptr, "bipush 0\n");
        fprintf(fptr, "Label%d:\n", CURRENTLABEL+1);
        CURRENTLABEL += 2;    
    }
    else{
        printf("ERROR: Invalid Operator\n");
        fflush(stdout);
        exit(EXIT_FAILURE);
    }

}
