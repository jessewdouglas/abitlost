#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BYTE_SIZE 8

bool **bytes;
int byte_rows;
int current_row;

long random_range(int lower, int upper) {
    return random() % (upper - lower + 1) + lower;
}

bool and_bools(bool x, bool y) { return x && y; }

bool xor_bools(bool x, bool y) { return (x && !y) || (!x && y); }

void and_bytes(bool const *first, bool const *second, bool *out) {
    for (int i = 0; i < BYTE_SIZE; ++i) {
        out[i] = and_bools(first[i], second[i]);
    }
}

void xor_bytes(bool const *first, bool const *second, bool *out) {
    for (int i = 0; i < BYTE_SIZE; ++i) {
        out[i] = xor_bools(first[i], second[i]);
    }
}

void populate_initial_byte(bool *out) {
    int start_pos = random_range(0, 7);
    out[start_pos] = 1;
}

void populate_random_byte(bool *out) {
    for (int i = 0; i < BYTE_SIZE; ++i) {
        out[i] = random() % 2;
    }
}

void populate_byte_from_operation(bool const *operand, bool *out) {
    bool temp[BYTE_SIZE];
    populate_random_byte(temp);

    if (random() % 2) {
        and_bytes(operand, temp, out);
    } else {
        xor_bytes(operand, temp, out);
    }
}

void print_byte(bool const *byte) {
    for (int i = 0; i < BYTE_SIZE; ++i) {
        printf("%i", byte[i]);
    }
    printf("\n");
}

void create_byte_rows(int rows) {
    bytes = calloc(rows, sizeof(bool *));

    for (int row = 0; row < rows; ++row) {
        bytes[row] = calloc(BYTE_SIZE, sizeof(bool));
        if (row == 0) {
            populate_initial_byte(bytes[row]);
        } else if (row == 1) {
            populate_random_byte(bytes[row]);
        } else {
            populate_byte_from_operation(bytes[row - 1], bytes[row]);
        }
    }

    byte_rows = rows;
}

void print_bytes() {
    for (int i = 0; i < byte_rows; ++i) {
        print_byte(bytes[i]);
    }
}

void free_bytes() {
    for (int i = 0; i < byte_rows; ++i) {
        free(bytes[i]);
    }
    free(bytes);
}

int main() {
    srandom(time(0));

    create_byte_rows(4);
    print_bytes();
    free_bytes();
}
