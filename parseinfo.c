#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *parsetext(char *text, char *pattern) {
  char *parsedtext = malloc(sizeof(char) * 50);
  parsedtext = "";

  sscanf(text, pattern, parsedtext);

  return parsedtext;
}

int checktext(char *text) {
    if (!(strcmp(text, ""))) {
      return 1;
    } else {
      return 0;
    }
}

int main () {

  // printf("%d", checktext(parsetext("TEST=hello", "TEST=%s")));
  char a[] = "hello=test";
  char b[] = "hello=%s";

  char *t = parsetext(a, b);
  
   return(0);
}