#ifndef ENV_H
#define ENV_H

#include <string.h>
#include <stdio.h>

#include "constants.h"

extern int debug;

void setEnvVars(int argc, char ** argv);

#endif
