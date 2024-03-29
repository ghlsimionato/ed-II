#include "./headers/remove.h"

struct DeleteRegister * searchForId(FILE * outputFile, char * id) {
  struct DeleteRegister * fileData;
  fileData = readFileRegister(outputFile);

  if (fileData == NULL) {
    return NULL;
  }

  // if regSize is 0, the data is marked for removal

  if (fileData->regSize != 0 && strcmp(fileData->data.id, id) == STR_MATCH) {
    return fileData;
  }

  return searchForId(outputFile, id);
}

void removeRegister(char * id) {
  FILE * outputFile = openFile(OUTPUT_FILE_PATH, READ_WRITE_BIN);
  struct Header header;
  struct Header headerToWrite;
  struct DeleteRegister * fileData;

  header = getFileHeader(outputFile); /* reads the header to advance file pointer and get offset */
  fileData = searchForId(outputFile, id);

  if (fileData == NULL) {
    printf("\nRegister id = %s not found\n", id);
    return;
  }

  int offsetToReturn = -(fileData->regSize + 4);

  fseek(outputFile, offsetToReturn, SEEK_CUR);
  headerToWrite.offest = ftell(outputFile);
  fseek(outputFile, 4, SEEK_CUR);
  fputc('*', outputFile);
  fwrite(&(header.offest), sizeof(int), 1, outputFile);
  updateFileHeader(headerToWrite, outputFile);

  free(fileData);
  free(id);

  fclose(outputFile);

  return;
}
