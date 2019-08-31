#include "./headers/utils.h"

void cleanStdin() {
  char c;
  
  while ((c = getchar()) != '\n' && c != EOF)

  return;
}

char * getStringFromUser(int len) {
  char * input = malloc(len);

  cleanStdin();

  if (fgets(input, len, stdin)) {
    if (input[strlen(input) - 1] == '\n') {
      input[strlen(input) - 1] = '\0';
    } else {
      while ((getchar()) != '\n');
    }

    return input;
  }

  return NULL;
}
