#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fxor.h"
#include "keygen.h"

#define DEFAULT_KEYFILE "keyfile"

void usage(char *name) {
  printf(
      "Usage: %s keygen output_keyfile\n"
      "       %s fxor input_file key_file output_file\n",
      name, name);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    usage(argv[0]);
    return 1;
  } else if (strcmp(argv[1], "keygen") == 0) {
    char *key;
    int length = 4096;
    if (argc < 3) {
      key = DEFAULT_KEYFILE;
    } else {
      key = argv[2];
    }
    if (argc > 3) {
      length = atoi(argv[3]);
    }
    return keygen(key, length);
  } else if (strcmp(argv[1], "fxor") == 0) {
    if (argc != 5) {
      usage(argv[0]);
      return 1;
    }
    return fxor(argv[2], argv[3], argv[4]);
  } else {
    usage(argv[0]);
    return 1;
  }
}