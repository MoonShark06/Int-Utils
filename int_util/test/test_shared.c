#include <stdio.h>
#include <stdint.h>
#include "int_util.h"

int main(void) {
    printf("=== Shared Library Test ===\n");

    printf("is_overflow: %d\n", is_overflow(INT32_MAX, 1, ADD));

    char buffer[33];
    int_to_binary(13, buffer, sizeof(buffer));
    printf("int_to_binary(13): %s\n", buffer);

    printf("reverse_bits(1): %u\n", reverse_bits(1));

    printf("logical_shift_left(8, 2): %u\n",
           logical_shift_left(8, 2));

    printf("logical_shift_right(8, 2): %u\n",
           logical_shift_right(8, 2));

    printf("arithmetic_shift_right(-8, 2): %d\n",
           arithmetic_shift_right(-8, 2));

    printf("extract_bits(13, 1, 2): %u\n",
           extract_bits(13, 1, 2));

    printf("insert_bits(8, 3, 1, 2): %u\n",
           insert_bits(8, 3, 1, 2));

    printf("count_set_bits(15): %d\n",
           count_set_bits(15));

    printf("is_power_of_two(16): %d\n",
           is_power_of_two(16));

    return 0;
}
