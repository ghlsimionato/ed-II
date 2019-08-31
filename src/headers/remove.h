#include <stdio.h>

#include "io.h"
#include "constants.h"
#include "structs.h"

int getRegisterOffset(FILE * outputFile, char * id);
void writeDeleteInformation(FILE * outputFile, int offset);
struct Register * searchForId(FILE * outputFile, FILE * prevLocation, char * id);
void removeRegister(char * id);
