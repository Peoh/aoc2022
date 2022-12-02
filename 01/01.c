#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"

#define BASE10 10

struct top3 {
    uint32_t first;
    uint32_t second;
    uint32_t third;
};

uint32_t parse(const char *data, uint32_t filesize, struct top3 *top3) {
    uint32_t max_sum = 0;
    uint32_t curr_sum = 0;
    uint32_t curr_idx = 0;

    while (curr_idx < filesize) {
        uint32_t start_idx;

        if (data[curr_idx] == '\n') {

            max_sum = curr_sum > max_sum ? curr_sum : max_sum;

            if (top3->third < curr_sum) {
                top3->third = curr_sum;
            }
            if (top3->second < curr_sum) {
                top3->third = top3->second;
                top3->second = curr_sum;
            }
            if (top3->first < curr_sum) {
                top3->third = top3->second;
                top3->second = top3->first;
                top3->first = curr_sum;
            }

            curr_sum = 0;
            curr_idx++;
        }
        start_idx = curr_idx;

        while (data[curr_idx] != '\n' && data[curr_idx] != 0) {
            curr_idx++;
        }
        curr_sum += strtol(&data[start_idx], NULL, BASE10);
        curr_idx++;
    }
    return max_sum;
}

int main() {
    uint32_t filesize = 0;
    uint32_t max = 0;
    struct top3 top3 = {0};

    // Load input into buffer
    char *filedata = load_file("01.input.txt", &filesize);
    if (filedata == NULL) {
        printf("Can't load input file\n");
        goto clean;
    }

    // Parse buffer
    max = parse(filedata, filesize, &top3);

    printf("Maximum: %u\n", max);
    printf("top3 : %u, %u, %u\n", top3.first, top3.second, top3.third);
    printf("top3 sum: %u\n", top3.first + top3.second + top3.third);

clean:
    if (filedata) {
        free(filedata);
    }
    return 0;
}
