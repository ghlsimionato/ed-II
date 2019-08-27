#ifndef IO_H

#define IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "constants.h"

#define REG_SIZE 137

FILE * openFile(char * fileName, char * fileMode);
struct Register * readDataFile(FILE * dataFile);
void updateFileHeader(struct Header headerData, FILE * outputFile);
struct Header getFileHeader(FILE * fPointer);

#endif
