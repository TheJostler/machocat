#ifndef FXOR_H
#define FXOR_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define BUFFER_SIZE 4096

int fxor(char *input, char *key, char *output);

#endif