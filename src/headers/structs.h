#ifndef STRUCTS_H

#include "constants.h"

#define STRUCTS_H
struct Header {
  int offest;
};

struct Register {
  char id[4], name[50], insurance[50], insuranceType[30];
};

struct FormatedRegister {
  int regSize;
  char * buffer;
};

#endif
