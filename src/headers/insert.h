#include <stdio.h>
#include <stdlib.h>

#include "io.h"
#include "constants.h"
#include "utils.h"
#include "structs.h"

struct Register getInputFromUser();
int handleUserInsert();
int getRegisterSize(struct Register input);
void formatData(char * buffer, struct Register dataToFormat);
void insertRegister(struct Register dataToInsert);
void findFirstFit(FILE * outputFile, int offset, int prevOffset, int registerSize);
long getFileSize(FILE * fPointer);
struct Register * readDataFile(FILE * dataFile);
void insertDataFromFile();
