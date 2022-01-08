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

void populate_initial_byte_field()
{
    int start_pos = random_range(0, 7);
    byte_fields[0][start_pos] = 1;
}

void populate_random_byte_field(int row)
{
    for (int i = 0; i < BYTE_FIELD_SIZE; ++i)
    {
        byte_fields[row][i] = random() % 2;
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
            populate_initial_byte_field();
        }
        else
        {
            populate_random_byte_field(row);
        }
    }

    byte_field_rows = rows;
}

void free_byte_fields()
{
    for (int i = 0; i < byte_field_rows; ++i)
    {
        free(byte_fields[i]);
    }
    free(byte_fields);
}

void print_byte_field(int row)
{
    for (int i = 0; i < BYTE_FIELD_SIZE; ++i)
    {
        printf("%i", byte_fields[row][i]);
    }
    printf("\n");
}

void print_byte_fields()
{
    for (int i = 0; i < byte_field_rows; ++i)
    {
        print_byte_field(i);
    }
}

int main()
{
    srandom(time(0));

    create_byte_fields(4);
    print_byte_fields();
    free_byte_fields();
}
