#include <stdio.h>
#include "../../include/symbols/TCsymbol.h"


int main(void){
    symbol s1 = createSymbol();     
    freeSymbol(&(s1));
    s1 = createSymbol();
    printf("uninitialized s1: %s", symbolToString(s1));
    setId(&s1, "Meow");
    printf("s1 ID: %s\n", getId(s1));
    setType(&s1, OFFSET);
    printf("s1 type: %d\n",getType(s1)); 
    printf("full symbol: %s\n", symbolToString(s1));
    freeSymbol(&(s1));
    return(0);
}
