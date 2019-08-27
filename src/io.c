#include "./headers/io.h"

FILE * openFile(char * fileName, char * fileMode) {
  FILE * fPointer;

  fPointer = fopen(fileName, fileMode);

  if (fPointer == NULL) {
    printf("\n[ERR]: filename=%s not found", fileName);
    return NULL;
  }

  // printf("\nFile %s found for mode %s\n", fileName, fileMode);

  return fPointer;
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

  buffer = malloc(buffSize);

  fread(buffer, sizeof (struct Register), 5, dataFile);
  fclose(dataFile);

  return buffer;
}

void updateHeader(struct Header headerData, FILE * outputFile) {
  rewind(outputFile);
  fwrite(&headerData, sizeof (struct Header), 1, outputFile);
}

struct Header getFileHeader(FILE * fPointer) {
  struct Header fileHeader;

  fread(&fileHeader, sizeof (struct Header), 1, fPointer);
  return fileHeader;
}
