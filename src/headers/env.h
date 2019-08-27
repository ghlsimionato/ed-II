#ifndef ENV_H
#define ENV_H

#include "constants.h"

#include <string.h>
#include <stdio.h>

extern int debug;

void setEnvVars(int argc, char ** argv);

#endif
