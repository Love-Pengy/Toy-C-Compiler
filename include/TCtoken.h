struct tokenStruct{
    char *lexeme;
    char *value;
};
typedef struct tokenStruct *token;
token createToken(char *, char *);
void printToken(token);
