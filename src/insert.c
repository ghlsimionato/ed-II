#include "./headers/insert.h"

void testFunction() {
  printf("\nTesting\n");
  FILE * fPointer = openFile(OUTPUT_FILE_PATH, READ_WRITE_BIN);

  initializeFile(fPointer);
  fclose(fPointer);
}

int initializeFile(FILE * outputFile) {
  struct Header headerToSet;
  headerToSet.offest = -1;

  updateFileHeader(headerToSet, outputFile);

  return 0;
}
