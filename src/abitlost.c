/*
Copyright 2022 Jesse Douglas.

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option) any
later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#define BYTE_SIZE 8

bool **bytes;
int byte_rows;
int current_row;
int rows_printed;

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

void print_byte(bool const *byte) {
    for (int i = 0; i < BYTE_SIZE; ++i) {
        printf("%i", byte[i]);
    }
    printf("\n");
    ++rows_printed;
}

void create_byte_rows(int rows) {
    bytes = calloc(rows, sizeof(bool *));

    for (int row = 0; row < rows; ++row) {
        bytes[row] = calloc(BYTE_SIZE, sizeof(bool));
        if (row == 0) {
            populate_initial_byte(bytes[row]);
        } else {
            populate_random_byte(bytes[row]);
        }
    }

    byte_rows = rows;
}

void free_bytes() {
    for (int i = 0; i < byte_rows; ++i) {
        free(bytes[i]);
    }
    free(bytes);
}

void move_cursor_up(int rows) {
    if (rows) {
        printf("\033[%iA", rows);
        rows_printed -= rows;
    }
}

void print_bytes() {
    move_cursor_up(rows_printed);
    for (int i = 0; i < byte_rows; ++i) {
        if (i < current_row) {
            printf("\033[K\n");
            ++rows_printed;
        } else {
            print_byte(bytes[i]);
        }
    }
}

void process_input(char c) {
    switch (c) {
    case 'a':
    case 'A':
    case '&':
        and_bytes(bytes[current_row], bytes[current_row + 1],
                  bytes[current_row + 1]);
        ++current_row;
        break;
    case 'x':
    case 'X':
    case '^':
        xor_bytes(bytes[current_row], bytes[current_row + 1],
                  bytes[current_row + 1]);
        ++current_row;
        break;
    }
}

int main() {
    srandom(time(0));
    create_byte_rows(4);

    struct termios old_termios, new_termios;
    tcgetattr(STDIN_FILENO, &old_termios);
    new_termios = old_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    char c = 0;
    do {
        process_input(c);
        print_bytes();
    } while ((c = getchar()) != 'q');

    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);

    free_bytes();
}
