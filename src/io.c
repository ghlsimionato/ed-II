#include "./headers/io.h"

FILE * openFile(char * fileName, char * fileMode) {
  FILE * fPointer;

  printf("\n[LOG] filename=%s filemode=%s\n", fileName, fileMode);

  fPointer = fopen(fileName, fileMode);

  if (fPointer == NULL) {
    printf("\n[ERR]: filename=%s not found", fileName);

    if (strcmp(fileMode, READ_WRITE_BIN) == STR_MATCH) {
      printf("\n[LOG] File not found, creating file\n");
      fPointer = fopen(fileName, WRITE_READ_BIN);
      initializeFile(fPointer);

      return fPointer;
    }

    return NULL;
  }

  printf("\nFile %s found for mode %s\n", fileName, fileMode);

  return fPointer;
}

int initializeFile(FILE * outputFile) {
  struct Header headerToSet;
  headerToSet.offest = -1;

  updateFileHeader(headerToSet, outputFile);

  return 0;
}

long getFileSize(FILE * fPointer) {
  fseek(fPointer, 0, SEEK_END);
  int fSize = ftell(fPointer);
  rewind(fPointer);

  return fSize;
}

struct Register * readDataFile(FILE * dataFile) {
  struct Register * buffer;
  long buffSize = getFileSize(dataFile);
  int registerSize = sizeof (struct Register);
  int numOfRegsToRead = buffSize / registerSize;

  buffer = malloc(buffSize);

  fread(buffer, registerSize, numOfRegsToRead, dataFile);
  fclose(dataFile);

  return buffer;
}

void updateFileHeader(struct Header headerData, FILE * outputFile) {
  rewind(outputFile);
  fwrite(&headerData, sizeof (struct Header), 1, outputFile);
}

struct Header getFileHeader(FILE * fPointer) {
  struct Header fileHeader;

  rewind(fPointer);
  fread(&fileHeader, sizeof (struct Header), 1, fPointer);
  return fileHeader;
}

void readFileRegisters() {
  FILE * test = openFile(OUTPUT_FILE_PATH, READ_BIN);
  char buffer[255];
  int sizes, i;

  fread(&sizes, sizeof(int), 1, test);
  for (i = 0; i < 8; i++) {
    fread(&sizes, sizeof(int), 1, test);
    printf("\nSize = %d", sizes);
    fread(buffer, sizes, 1, test);
    printf(" Buffer = %s\n", buffer);
  }

}

