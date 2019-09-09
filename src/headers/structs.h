#ifndef STRUCTS_H

#include "constants.h"

#define STRUCTS_H

// Struct for the file Header
struct Header {
  int offest;
};

struct Register {
  char id[4], name[50], insurance[50], insuranceType[30];
};

struct DeleteRegister {
  struct Register data;
  int regSize;
};

#endif
