#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BYTE_FIELD_SIZE 8

bool **byte_fields;
int byte_field_rows;
int current_row;

long random_range(int lower, int upper)
{
    return random() % (upper - lower + 1) + lower;
}

bool bool_and(bool x, bool y)
{
    return x && y;
}

bool bool_xor(bool x, bool y)
{
    return (x && !y) || (!x && y);
}

void populate_initial_byte_field(bool *byte_field)
{
    int start_pos = random_range(0, 7);
    byte_field[start_pos] = 1;
}

void populate_random_byte_field(bool *byte_field)
{
    for (int i = 0; i < BYTE_FIELD_SIZE; ++i)
    {
        byte_field[i] = random() % 2;
    }
}

void print_byte_field(bool const *byte_field)
{
    for (int i = 0; i < BYTE_FIELD_SIZE; ++i)
    {
        printf("%i", byte_field[i]);
    }
    printf("\n");
}

void and_byte_fields(bool const *first, bool const *second, bool *out)
{
    for (int i = 0; i < BYTE_FIELD_SIZE; ++i)
    {
        out[i] = bool_and(first[i], second[i]);
    }
}

void xor_byte_fields(bool const *first, bool const *second, bool *out)
{
    for (int i = 0; i < BYTE_FIELD_SIZE; ++i)
    {
        out[i] = bool_xor(first[i], second[i]);
    }
}

void create_byte_fields(int rows)
{
    byte_fields = calloc(rows, sizeof(bool *));

    for (int row = 0; row < rows; ++row)
    {
        byte_fields[row] = calloc(BYTE_FIELD_SIZE, sizeof(bool));
        if (row == 0)
        {
            populate_initial_byte_field(byte_fields[row]);
        }
        else if (row == 1)
        {
            populate_random_byte_field(byte_fields[row]);
        }
    }

    byte_field_rows = rows;
}

void print_byte_fields()
{
    for (int i = 0; i < byte_field_rows; ++i)
    {
        print_byte_field(byte_fields[i]);
    }
}

void free_byte_fields()
{
    for (int i = 0; i < byte_field_rows; ++i)
    {
        free(byte_fields[i]);
    }
    free(byte_fields);
}

int main()
{
    srandom(time(0));

    create_byte_fields(4);
    print_byte_fields();
    free_byte_fields();
}
