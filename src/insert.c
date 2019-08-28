#include "./headers/insert.h"

struct Register getInputFromUser() {
  struct Register input;
  char buffer[60];

  printf("\nRegister new user information\n");

  cleanStdin();
  printf("ID: ");
  if (fgets(buffer, 4, stdin)) {
    strtok(buffer, '\n');
    strcpy(input.id, buffer);
  }

  printf("Name: ");
  fgets(input.name, 50, stdin);

  printf("Insurance: ");
  fgets(input.insurance, 50, stdin);

  printf("Insurance type: ");
  fgets(input.insuranceType, 30, stdin);

  printf("\nUSER TO INSERT: %s %s %s %s\n", input.id, input.name, input.insurance, input.insuranceType);

  return input;
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
