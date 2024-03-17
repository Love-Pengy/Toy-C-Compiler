typedef struct listType *list;    
list createList(void);
void expandList(list);
void listCat(list, char*);
void freeList(list);
