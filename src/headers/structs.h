#ifndef STRUCTS_H

#include "constants.h"

#define STRUCTS_H
struct Header {
  int offest;
};

struct Register {
  char id[4], name[51], insurance[51], insuranceType[31];
};

struct DeleteRegister {
  struct Register data;
  int regSize;
};

#endif
