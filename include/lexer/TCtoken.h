//B. Frazier 3/16/24
struct tokenStruct{
    char *lexeme;
    char *value;
};

typedef struct tokenStruct *token;
token createToken(char *, char *);
void printToken(token);
void freeToken(token);
