#include "./headers/insert.h"

int getRegisterSize(struct Register input) {
  int sizeSum;

  sizeSum = strlen(input.id) + strlen(input.name) + strlen(input.insurance) + strlen(input.insuranceType);
  return sizeSum;
}

void formatData(char * buffer, struct Register dataToFormat) {
  sprintf(buffer, "%s#%s#%s#%s", dataToFormat.id, dataToFormat.name, dataToFormat.insurance, dataToFormat.insuranceType);
}

void insertRegister(struct Register dataToInsert) {
  int sizeToAllocate = getRegisterSize(dataToInsert) + 3*sizeof(char);
  char * buffer = malloc(sizeToAllocate);

  formatData(buffer, dataToInsert);
  
  FILE * outputFile = openFile(OUTPUT_FILE_PATH, READ_WRITE_BIN);

  int registerSize = sizeToAllocate + 1;


  fseek(outputFile, 0 ,SEEK_END);
  fwrite(&registerSize, sizeof (int), 1, outputFile);
  fwrite(buffer, registerSize, 1, outputFile);

  free(buffer);

  fclose(outputFile);
  return;
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

  buffer = malloc(numOfRegsToRead * registerSize);

  fread(buffer, registerSize, numOfRegsToRead, dataFile);
  fclose(dataFile);

  return buffer;
}

/* Not checking if already inserted */
void insertDataFromFile() {
  FILE * inputData = openFile(DATA_FILE_PATH, READ_BIN);
  char input;

  struct Register * dataArray = readDataFile(inputData);
  for (int i = 0; i < 8; i++) {
    printf("\nData to insert: \n");
    printf("\nID: %s", dataArray[i].id);
    printf("\nName: %s", dataArray[i].name);
    printf("\nInsurance: %s", dataArray[i].insurance);
    printf("\nInsurance type: %s", dataArray[i].insuranceType);
    printf("\nInsert this register? [y/n] ");
    scanf(" %c", &input);
  }

  free(dataArray);
}
