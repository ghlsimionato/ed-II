#ifndef UTILS_H

#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "io.h"

void cleanStdin();
char * getStringFromUser(int len);
void iterateThroughSpaceList(FILE * outputFile); // debug function

#endif
