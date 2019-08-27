#include "./headers/env.h"

int debug = FALSE;

void setEnvVars(int argc, char ** argv) {
  if (argc < 2) {
    return;
  }

  if (strcmp(argv[2],"debug") == STR_MATCH) {
    debug = TRUE;
  }

  return;
}
