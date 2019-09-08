#include "./headers/insert.h"

struct Register getInputFromUser() {
  struct Register input;
  char * buffer;

  printf("\nRegister new user information\n");

  cleanStdin();
  printf("ID: ");
  buffer = getStringFromUser(4);
  strcpy(input.id, buffer);
  free(buffer);

  printf("Name: ");
  buffer = getStringFromUser(51);
  strcpy(input.name, buffer);
  free(buffer);  

  printf("Insurance: ");
  buffer = getStringFromUser(51);
  strcpy(input.insurance, buffer);
  free(buffer);  

  printf("Insurance type: ");
  buffer = getStringFromUser(31);
  strcpy(input.insuranceType, buffer);
  free(buffer); 

  printf("\n[USER TO INSERT]: %s %s %s %s\n", input.id, input.name, input.insurance, input.insuranceType);

  return input;
}

int handleUserInsert() {
  struct Register input = getInputFromUser();

  insertRegister(input);

  return TRUE;
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
  } else {
    findFirstFit(outputFile, fileHeader.offest, -1, registerSize);
  }

  fwrite(buffer, registerSize, 1, outputFile);

  free(buffer);

  fclose(outputFile);
  return;
}

void findFirstFit(FILE * outputFile, int offset, int prevOffset, int registerSize) {
  if (offset == -1) {
    return;
  }

  char marker;
  int nextOffset;
  int availableSpace;
  // prevOffset = offset;

  fseek(outputFile, offset, SEEK_CUR);
  fread(&availableSpace, sizeof(int), 1, outputFile);
  fread(&marker, sizeof (char), 1, outputFile);

  if (marker != '*') {
    printf("\n[ERR] Offset points to space NOT marked as available\n");
    return;
  }

  fread(&nextOffset, sizeof(int), 1, outputFile);

  // rewind to have file pointer on register size
  int bytesToRewind = -(2*(sizeof (int)) + sizeof (char));
  fseek(outputFile, bytesToRewind, SEEK_CUR);

  if (availableSpace < registerSize) {
    findFirstFit(outputFile, nextOffset, prevOffset, registerSize);

    return;
  }

  return;
}
