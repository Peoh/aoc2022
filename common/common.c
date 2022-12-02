#include "common.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *load_file(const char *filename, uint32_t *filesize) {
    FILE *filep = NULL;

    if (NULL == filename || filesize == NULL) {
        return NULL;
    }

    filep = fopen(filename, "r");
    if (NULL == filep) {
        printf("No correct file provided: '%s'\n", filename);
        return NULL;
    }

    // Get file size
    fseek(filep, 0L, SEEK_END);
    *filesize = ftell(filep) + 1;
    fseek(filep, 0, SEEK_SET);

    char *data = calloc(sizeof(*data), *filesize);
    if (data == NULL) {
        fclose(filep);
        return NULL;
    }

    // Read file into buffer
    uint32_t ret = fread(data, sizeof(*data), *filesize - 1, filep);
    if (ret != (sizeof(*data)) * (*filesize - 1)) {
        printf("Can't read file %u\n", ret);
        free(data);
        fclose(filep);
        return NULL;
    }

    fclose(filep);
    return data;
}