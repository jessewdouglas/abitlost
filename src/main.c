#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define BYTE_FIELD_SIZE 8

bool **byte_fields;
int byte_field_length;
int current_row;

void populate_byte_fields(int length)
{
    byte_fields = calloc(length, sizeof(bool *));
    for (int i = 0; i < length; ++i)
    {
        byte_fields[i] = calloc(BYTE_FIELD_SIZE, sizeof(bool));
    }

    byte_field_length = length;
}

void free_byte_fields()
{
    for (int i = 0; i < byte_field_length; ++i)
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
    for (int i = 0; i < byte_field_length; ++i)
    {
        print_byte_field(i);
    }
}

int main()
{
    populate_byte_fields(4);
    print_byte_fields();
    free_byte_fields();
}
