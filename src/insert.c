#include "./headers/insert.h"

void testFunction() {
  printf("\nTesting\n");
  FILE * fPointer = openFile(OUTPUT_FILE_PATH, READ_WRITE_BIN);

  initializeFile(fPointer);
  fclose(fPointer);
}

int getRegisterSize(struct Register input) {
  int sizeSum;

  sizeSum = strlen(input.id) + strlen(input.name) + strlen(input.insurance) + strlen(input.insuranceType);
  return sizeSum;
}

void formatData(char * buffer, struct Register dataToFormat) {
  sprintf(buffer, "%s#%s#%s#%s", dataToFormat.id, dataToFormat.name, dataToFormat.insurance, dataToFormat.insuranceType);
}

void insertRegister(struct Register dataToInsert) {
  struct Header fileHeader;
  int sizeToAllocate = getRegisterSize(dataToInsert) + 3*sizeof(char);
  char * buffer = malloc(sizeToAllocate);
  formatData(buffer, dataToInsert);
  
  FILE * outputFile = openFile(OUTPUT_FILE_PATH, READ_WRITE_BIN);
  fileHeader = getFileHeader(outputFile);

  int registerSize = sizeToAllocate + 1;

  if (fileHeader.offest == -1) {
    fseek(outputFile, 0 ,SEEK_END);
    fwrite(&registerSize, sizeof (int), 1, outputFile);
    fwrite(buffer, registerSize, 1, outputFile);

    fclose(outputFile);

    return;
  }
}
