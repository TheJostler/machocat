#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define BUFFER_SIZE 4096

int openf(const char *pathname, int flags, mode_t mode) {
  int fd = open(pathname, flags, mode);
  if (fd == -1) {
    perror("open");
    printf("file: \"%s\"\n", pathname);
    exit(1);
  }
  return fd;
}

void fill(int fd, off_t input_size, char val) {
  // Fill input and key files with 0xff bytes
  lseek(fd, 0, SEEK_SET);
  char fill_buffer[BUFFER_SIZE];
  memset(fill_buffer, val, BUFFER_SIZE);

  for (off_t remaining = input_size; remaining > 0; remaining -= BUFFER_SIZE) {
    ssize_t to_write = remaining < BUFFER_SIZE ? remaining : BUFFER_SIZE;
    write(fd, fill_buffer, to_write);
  }
  fsync(fd);
}

char xor(char a, char b) {
  return a ^ b;
}

int fxor(char *input, char *key, char *output) {
  int inputfd = openf(input, O_RDWR | O_SYNC, 0);
  int keyfd = openf(key, O_RDWR | O_SYNC, 0);
  int outputfd = openf(output, O_WRONLY | O_CREAT | O_TRUNC, 0666);
  int i = 0;
  off_t input_size = lseek(inputfd, 0, SEEK_END);
  lseek(inputfd, 0, SEEK_SET);

  printf("Processing... %s\n", input);


  char input_buffer[BUFFER_SIZE];
  char key_buffer[BUFFER_SIZE];
  char output_buffer[BUFFER_SIZE];
  ssize_t input_read, key_read, output_written;

  while ((input_read = read(inputfd, input_buffer, BUFFER_SIZE)) > 0) {
    key_read = read(keyfd, key_buffer, input_read);
    if (key_read < input_read) {
      printf("\nKey file is too short\n");
      close(inputfd);
      close(keyfd);
      close(outputfd);
      return 1;
    }

    for (ssize_t j = 0; j < input_read; j++) {
      output_buffer[j] = xor(input_buffer[j], key_buffer[j]);
    }

    output_written = write(outputfd, output_buffer, input_read);
    if (output_written != input_read) {
      perror("Error writing to output file");
       return 1;
    }

    printf("\r%li%%", (i++ * BUFFER_SIZE * 100) / input_size);
    fflush(stdout);
  }

  printf("\r100%%\n");
  printf("Done!\n");

  fill(inputfd, input_size, 0xff);
  fill(keyfd, input_size, 0xff);
  fill(inputfd, input_size, 0x00);
  fill(keyfd, input_size, 0x00);

  unlink(input);
  unlink(key);

  //Clear buffers
  memset(input_buffer, 0, BUFFER_SIZE);
  memset(key_buffer, 0, BUFFER_SIZE);
  memset(output_buffer, 0, BUFFER_SIZE);

  // Close file descriptors
  close(inputfd);
  close(keyfd);
  close(outputfd);
  return 0;
}