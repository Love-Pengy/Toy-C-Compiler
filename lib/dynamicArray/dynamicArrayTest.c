#include <stdio.h>
#include <stdlib.h>
#include "./dynamicArray.h"

int main(void){ 
    list tester = createList();
    listCat(tester, "testing something something something something something meow meow meow meow");
    printf("%s\n", listToString(tester));
    freeList(tester);
    exit(EXIT_SUCCESS);
}
