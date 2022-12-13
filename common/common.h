#include <stdint.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

char *load_file(const char *filename, uint32_t *filesize);
