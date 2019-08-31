#include "./headers/remove.h"

int getRegisterOffset(FILE * outputFile, char * id) {

}

void writeDeleteInformation(FILE * outputFile, int offset) {

}

struct Register * searchForId(FILE * outputFile, FILE * prevLocation, char * id) {
  struct Register * fileData;
  prevLocation = outputFile;
  fileData = readFileRegister(outputFile);

  if (fileData == NULL) {
    printf("\nRegister not found\n");
    return NULL;
  }

  if (strcmp(fileData->id, id) == STR_MATCH) {
    return fileData;
  }

  return searchForId(outputFile, prevLocation ,id);
}

void removeRegister(char * id) {
  FILE * outputFile = openFile(OUTPUT_FILE_PATH, READ_WRITE_BIN);
  FILE * prevLocation;
  struct Header header;
  struct Register * fileData;

  header = getFileHeader(outputFile);
  fileData = searchForId(outputFile, prevLocation ,id);
  fseek(outputFile, SEEK_CUR, 5);

  free(fileData);
  free(id);

  return;
}
