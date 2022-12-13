#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"

#define BASE10 10

/**
 * RULES
 * -----
 * Opponent:
 * A for Rock, B for Paper, and C for Scissors
 * Self:
 * X for Rock, Y for Paper, and Z for Scissors
 */

#define WIN_POINTS 6
#define DRAW_POINTS 3
#define LOST_POINTS 0

enum rps_e {
    INVALID = -1,
    ROCK = 0,
    PAPER = 1,
    SCISSORS = 2,
};

struct rps_resolver_line {
    enum rps_e rps;
    char opponent_char;
    char self_char;
    int value;
    enum rps_e win_against;
    enum rps_e draw_against;
    enum rps_e lost_against;
};

struct rps_resolver_line rps_solver_table[] = {
    {ROCK, 'A', 'X', 1, SCISSORS, ROCK, PAPER},
    {PAPER, 'B', 'Y', 2, ROCK, PAPER, SCISSORS},
    {SCISSORS, 'C', 'Z', 3, PAPER, SCISSORS, ROCK}};

uint32_t parse(const char *data, uint32_t filesize) {
    uint32_t total_sum_1 = 0;
    uint32_t total_sum_2 = 0;
    uint32_t curr_sum = 0;
    uint32_t curr_idx = 0;

    while (curr_idx < filesize) {
        uint32_t start_idx;
        char opponent_char = 0;
        char self_char = 0;
        start_idx = curr_idx;

        while (data[curr_idx] != '\n' && data[curr_idx] != 0) {
            curr_idx++;
        }

        int ret = sscanf(&data[start_idx], "%c %c", &opponent_char, &self_char);
        if (ret != 2) {
            printf("Error: Invalid data\n");
            return 0;
        }

        // Detect values in rps_e enum
        enum rps_e opponent_val = INVALID;
        enum rps_e self_val = INVALID;
        for (uint32_t i = 0; i < ARRAY_SIZE(rps_solver_table); i++) {
            if (rps_solver_table[i].opponent_char == opponent_char) {
                opponent_val = rps_solver_table[i].rps;
            }
        }
        for (uint32_t i = 0; i < ARRAY_SIZE(rps_solver_table); i++) {
            if (rps_solver_table[i].self_char == self_char) {
                self_val = rps_solver_table[i].rps;
            }
        }

        if (opponent_val == INVALID || self_val == INVALID) {
            printf("Error: Invalid input data\n");
            curr_idx++;
            continue;
        }

        // Parsing for Part One
        {
            curr_sum = 0;

            if (rps_solver_table[self_val].win_against == opponent_val) {
                curr_sum = WIN_POINTS;
            } else if (rps_solver_table[self_val].lost_against ==
                       opponent_val) {
                curr_sum = LOST_POINTS;
            } else {
                // draw case
                curr_sum = DRAW_POINTS;
            }

            curr_sum += rps_solver_table[self_val].value;

            total_sum_1 += curr_sum;
        }

        // Parsing for Part Two
        {
            curr_sum = 0;
            enum rps_e played_val = INVALID;

            if (rps_solver_table[self_val].self_char == 'X') {
                // Need to Loose
                curr_sum = LOST_POINTS;
                played_val = rps_solver_table[opponent_val].win_against;
            } else if (rps_solver_table[self_val].self_char == 'Y') {
                // Draw
                played_val = rps_solver_table[opponent_val].draw_against;
                curr_sum = DRAW_POINTS;
            } else if (rps_solver_table[self_val].self_char == 'Z') {
                // Win
                played_val = rps_solver_table[opponent_val].lost_against;
                curr_sum = WIN_POINTS;
            }

            curr_sum += rps_solver_table[played_val].value;

            total_sum_2 += curr_sum;
        }

        curr_idx++;
    }
    printf("Part One: Total points: %d\n", total_sum_1);
    printf("Part Two: Total points: %d\n", total_sum_2);

    return total_sum_1;
}

int main() {
    uint32_t filesize = 0;

    // Load input into buffer
    char *filedata = load_file("02.input.txt", &filesize);
    if (filedata == NULL) {
        printf("Can't load input file\n");
        goto clean;
    }

    // Parse buffer
    total = parse(filedata, filesize);

clean:
    if (filedata) {
        free(filedata);
    }
    return 0;
}
