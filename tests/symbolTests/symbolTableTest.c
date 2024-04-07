#include <stdio.h>
#include "../../include/symbols/TCsymbol.h"
#include "../../include/symbols/TCSymbolTable.h"

int main(void){
         
    symbol s1 = createSymbol();     
    setId(&s1, "a");
    setType(&s1, OFFSET);
    symbol s2 = createSymbol();     
    setId(&s2, "b");
    setType(&s2, VAR);
    symbol s3 = createSymbol();     
    setId(&s3, "c");
    setType(&s3, LABEL);
    

    symbolTable table = createSymbolTable();
    addSymbol(&table,&s1);
    addSymbol(&table,&s2);
    addSymbol(&table,&s3);
    
    //this should return false
    printf("DOUBLE SYMBOL TEST: %d\n", addSymbol(&table, &s1));
    printf("%s\n", symbolTableToString(table));    
    
    //this should return true
    printf("EXISTS: %d\n", symbolExists(&table, "c"));

    //this should return false
    printf("DOES NOT EXIST: %d\n", symbolExists(&table, "banana"));
    
    //this should return false
    printf("DOES NOT EXIST: %d\n", symbolExists(&table, ""));
    printf("DOES NOT EXIST: %d\n", symbolExists(&table, NULL));
    
    return(0);

}
