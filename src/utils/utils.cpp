#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

char * Utils::readFileToString(const char * filename) {
  char * buffer = 0;
  long length;
  FILE * f = fopen(filename, "rb");

  if (f) {
    fseek(f, 0, SEEK_END);
    length = ftell (f);
    fseek(f, 0, SEEK_SET);
    buffer = (char *) malloc(length);
    if (buffer) {
      fread(buffer, 1, length, f);
    }
    fclose(f);
  }

  return buffer;
}
