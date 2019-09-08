#include "./headers/utils.h"

/* cleans stdin buffer to avoid newline inputs */
void cleanStdin() {
  char c;
  
  while ((c = getchar()) != '\n' && c != EOF)

  return;
}

char * getStringFromUser(int len) {
  char * input = malloc(len);

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

void iterateThroughSpaceList(FILE * outputFile) {
  struct Header fileHeader = getFileHeader(outputFile);
  int regSize;
  int nextOffset;
  char marker;

  if (fileHeader.offest == -1) {
    printf("\n No spaces marked as available! \n");
  }

  fseek(outputFile, fileHeader.offest, SEEK_SET);
  fread(&regSize, sizeof (int), 1, outputFile);
  printf("\nRegSize = %d", regSize);
  fread(&marker, sizeof (char), 1, outputFile);

  if (marker != '*') {
    printf("\n[ERR] Offset points to space NOT marked as available\n");
    return;
  }

  fread(&nextOffset, sizeof (int), 1, outputFile);
  printf("\nNext Offset = %d", nextOffset);

  while (nextOffset != -1) {
    fseek(outputFile, nextOffset, SEEK_SET);
    fread(&regSize, sizeof (int), 1, outputFile);
    printf("\nRegSize = %d", regSize);
    fread(&marker, sizeof (char), 1, outputFile);

    if (marker != '*') {
      printf("\n[ERR] Offset points to space NOT marked as available\n");
      return;
    }

    fread(&nextOffset, sizeof (int), 1, outputFile);
    printf("\nNext Offset = %d", nextOffset);
  }

  fclose(outputFile);
  return;
}
