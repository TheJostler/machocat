#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int keygen(char *key, int length) {
    int fd = open("/dev/random", O_RDONLY);
    if (fd < 0) {
        perror("Error opening /dev/random");
        return 1;
    }

    FILE *keyfile = fopen(key, "wb");
    if (!keyfile) {
        perror("Error creating key file");
        close(fd);
        return 1;
    }

    unsigned char buffer[length];
    if (read(fd, buffer, length) != length) {
        perror("Error reading random data");
        fclose(keyfile);
        close(fd);
        return 1;
    }

    fwrite(buffer, 1, length, keyfile);
    fclose(keyfile);
    close(fd);

    printf("Generated a %d-byte key file: %s\n", length, key);
    char shared_key[256];
    snprintf(shared_key, sizeof(shared_key), "%s.", key);

    FILE *shared_keyfile = fopen(shared_key, "wb");
    if (!shared_keyfile) {
      perror("Error creating shared key file");
      return 1;
    }

    fwrite(buffer, 1, length, shared_keyfile);
    fclose(shared_keyfile);

    printf("Generated a shared key file: %s\n", shared_key);
    return 0;
}
