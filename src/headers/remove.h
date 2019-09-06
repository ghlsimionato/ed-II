#include <stdio.h>

#include "io.h"
#include "constants.h"
#include "structs.h"

int getRegisterOffset(FILE * outputFile, char * id);
void writeDeleteInformation(FILE * outputFile, int offset);
struct DeleteRegister * searchForId(FILE * outputFile, char * id);
void removeRegister(char * id);
