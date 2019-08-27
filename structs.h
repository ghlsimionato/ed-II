#ifndef STRUCTS_H

#define STRUCTS_H
struct Header {
  int offest;
};

struct Register {
  char id[4], name[50], insurance[50], insuranceType[30];
};

#endif