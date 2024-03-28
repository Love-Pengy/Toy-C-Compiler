#ifndef DYNAMICARRAY
#define DYNAMICARRAY

typedef struct listType *list;    
list createList(void);
void expandList(list*);
void listCat(list*, char*);
void freeList(list);
char* listToString(list);
void llistCat(list*, list);

#endif
