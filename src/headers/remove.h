#include <stdio.h>

#include "io.h"
#include "constants.h"
#include "structs.h"

struct DeleteRegister * searchForId(FILE * outputFile, char * id);
void removeRegister(char * id);
