//B. Frazier 3/17/24
#ifndef DYNAMICARRAY
    #define DYNAMICARRAY
    #include "./dynamicArray.h"
#endif

#ifndef STDLIB
    #define STDLIB
    #include <stdlib.h>
#endif 

#ifndef STRING
    #define STRING
    #include <string.h>
#endif

#define CHUNK_SIZE 50

struct listType{
    char *string;
    int size;
    int buffSize;
};

list createList(void){
    list output = malloc(sizeof(struct listType));
    output->string = malloc(sizeof(char) * (CHUNK_SIZE + 1));
    output->string[51] = '\0';
    output->size = 0;
    output->buffSize = 50;
    return(output);
}

void expandList(list expandee){
    char *newList = malloc(sizeof(char) * (expandee->buffSize + CHUNK_SIZE));
    strcpy(newList, expandee->string);
    free(expandee->string);
    expandee->string = newList;
}

void llistCat(list dest, list source){
    while(dest->buffSize < (dest->size + source->size + 1)){
        expandList(dest);
    }
    strcat(dest->string, source->string);
    dest->size = (dest->size + strlen(source->size));
}

void listCat(list dest, char *source){
    if((strlen(source) + dest->size) > dest->buffSize){
        while((strlen(source) + dest->size) > dest->buffSize){
            expandList(dest);
        }
        strcat(dest->string, source);
        dest->size = (dest->size + strlen(source));
    }
    else{
        dest->size = (dest->size + strlen(source));
        strcat(dest->string, source);
    }
}

char *listToString(list printee){
    return(printee->string);       
}

list stringToList(char *string){
    list output = createList();
    listCat(output, string);
    return(output);
}

void freeList(list goodbye){
    free(goodbye->string);
    free(goodbye);
}
