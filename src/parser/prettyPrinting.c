//B. Frazier 4/1/24

#include <stdlib.h>
#include <string.h>
#include "../../include/parser/prettyPrinting.h"

static int pos = 0;
static int INDENTSIZE = 2;

char *spaces() {
  char *s = malloc(pos+1);
  strcpy(s,"");
  for (int i = 1; i <= pos; i++)
    strcat(s," ");
  return s;
} 

void indent() { 
    pos += INDENTSIZE;
}
void outdent() {
  pos -= INDENTSIZE;
  if(pos < 0) {
    printf("[Internal Error] illegal position in outdent\n");
    exit(EXIT_FAILURE);
  }
}



