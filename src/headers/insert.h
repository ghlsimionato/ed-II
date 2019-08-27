#include <stdio.h>
#include <stdlib.h>

#include "io.h"
#include "constants.h"
#include "structs.h"

void testFunction();
int getRegisterSize(struct Register input);
void formatData(char * buffer, struct Register dataToFormat);
void insertRegister(struct Register dataToInsert);
