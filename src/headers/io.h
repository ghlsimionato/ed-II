#ifndef IO_H

#define IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "constants.h"

FILE * openFile(char * fileName, char * fileMode);
int initializeFile(FILE * outputFile);
struct Register * readDataFile(FILE * dataFile);
void updateFileHeader(struct Header headerData, FILE * outputFile);
struct Header getFileHeader(FILE * fPointer);
struct DeleteRegister * readFileRegister(FILE * outputFile);
void readFileRegisters();
void dumpFile(char * fileName, char * fileMode);

#endif
