//B. Frazier 3/27/24
//this file was a sanity check. I am in fact not insane C is just a little silly
#include <stdio.h>
#include <stdlib.h>


struct test{
    int something;
};

typedef struct test * struc;

void access(struc** teste){
    (*teste)[0]->something = 11;
}

int main(void){
    struc *something = malloc(sizeof(struc) * 100);

    for(int i = 0; i < 100; i++){
        something[i] = malloc(sizeof(struc));
        something[i]->something = 10;
    }

    access(&something);

    for(int i = 0; i < 100; i++){
        printf("%d\n", something[i]->something);
    }
    
    return 0;
}
