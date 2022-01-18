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

typedef enum { in_progress, game_won, game_lost } win_state;

struct termios old_termios;

bool **bytes;
int byte_rows;
int current_row;
int destination[BYTE_SIZE];
int game_level;
int lines_printed;
win_state current_win_state;

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

void set_destination() {
    bool target[BYTE_SIZE];

    for (int i = 0; i < byte_rows - 1; ++i) {
        if (random() % 2) {
            and_bytes(bytes[i], bytes[i + 1], target);
        } else {
            xor_bytes(bytes[i], bytes[i + 1], target);
        }
    }

    for (int i = 0; i < BYTE_SIZE; ++i) {
        destination[i] = -1;
    }

    // TODO limit to BYTE_SIZE exits
    for (int i = 0; i < game_level; ++i) {
        int random_bit = random_range(0, BYTE_SIZE - 1);
        if (destination[random_bit] != -1) {
            --i;
            continue;
        }
        destination[random_bit] = target[random_bit];
    }
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

    set_destination();
}

void free_bytes() {
    if (byte_rows) {
        for (int i = 0; i < byte_rows; ++i) {
            free(bytes[i]);
        }
        free(bytes);
    }
}

void move_cursor_up(int lines) {
    if (lines) {
        printf("\033[%iA", lines);
        lines_printed -= lines;
    }
}

void print_new_line() {
    printf("\033[K\n");
    ++lines_printed;
}

void print_byte(bool const *byte, bool is_current) {
    for (int i = 0; i < BYTE_SIZE; ++i) {
        printf("%i ", byte[i]);
    }
    if (is_current) {
        printf("<-");
    }
    print_new_line();
}

void print_destination() {
    for (int i = 0; i < BYTE_SIZE; ++i) {
        if (destination[i] == 0) {
            printf("x ");
        } else if (destination[i] == 1) {
            printf("v ");
        } else {
            printf("  ");
        }
    }
    print_new_line();
}

void print_ui() {
    print_new_line();
    switch (current_win_state) {
    case game_lost:
        printf("You lost. :(  r: reset level  q: quit");
        break;
    case game_won:
        printf("You won! :)  n: next level  r: reset level  q: quit");
        break;
    default:
        printf("a/&: and  x/^: xor  r: reset level  q: quit");
        break;
    }
    print_new_line();
}

void display() {
    // TODO add color and/or emoji
    move_cursor_up(lines_printed);

    printf("Level %i", game_level);
    print_new_line();
    print_new_line();

    for (int i = 0; i < byte_rows; ++i) {
        if (i < current_row) {
            print_new_line();
        } else {
            print_byte(bytes[i], i == current_row);
        }
    }

    print_destination();
    print_ui();
}

void process_input(char);

void check_win() {
    if (current_row < byte_rows - 1) {
        current_win_state = in_progress;
        return;
    }
    for (int i = 0; i < BYTE_SIZE; ++i) {
        if (destination[i] > -1 && bytes[current_row][i] != destination[i]) {
            current_win_state = game_lost;
            return;
        }
    }
    current_win_state = game_won;
}

void start_game(int level) {
    game_level = level;
    // TODO alternate adding row or exit per level
    create_byte_rows(game_level + 1);

    char c = 0;
    do {
        process_input(c);
        check_win();
        display();
    } while ((c = getchar()));
}

void restart_game(int level) {
    free_bytes();
    current_row = 0;
    current_win_state = in_progress;
    start_game(level);
}

void process_input(char c) {
    if (c == 'q' || c == 'Q') {
        exit(0);
    } else if (c == 'r' || c == 'R') {
        restart_game(game_level);
    } else if (current_win_state == game_won && (c == 'n' || c == 'N')) {
        restart_game(game_level + 1);
    } else if (current_win_state == in_progress) {
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
}

void set_termios() {
    tcgetattr(STDIN_FILENO, &old_termios);
    struct termios new_termios = old_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

void on_exit() {
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
    free_bytes();
}

int main() {
    srandom(time(0));

    set_termios();
    atexit(on_exit);

    // TODO display intro
    start_game(1);
}
