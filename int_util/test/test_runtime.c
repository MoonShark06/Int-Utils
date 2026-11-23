#include <stdio.h>
#include <stdint.h>
#include <dlfcn.h>
#include "int_util.h"

int main(void) {
    printf("=== Runtime Dynamic Loading Test ===\n");

    void *handle = dlopen("./libintutils.so", RTLD_LAZY);

    if (handle == NULL) {
        printf("Library loading failed: %s\n", dlerror());
        return 1;
    }

    printf("Library loaded successfully!\n\n");

    // 함수 포인터 선언
    int (*is_overflow_func)(int32_t, int32_t, Operation);
    int (*int_to_binary_func)(uint32_t, char *, size_t);
    uint32_t (*reverse_bits_func)(uint32_t);
    uint32_t (*logical_shift_left_func)(uint32_t, unsigned int);
    uint32_t (*logical_shift_right_func)(uint32_t, unsigned int);
    int32_t (*arithmetic_shift_right_func)(int32_t, unsigned int);
    uint32_t (*extract_bits_func)(uint32_t, unsigned int, unsigned int);
    uint32_t (*insert_bits_func)(uint32_t, uint32_t, unsigned int, unsigned int);
    int (*count_set_bits_func)(uint32_t);
    int (*is_power_of_two_func)(uint32_t);

    char *error;

    // 라이브러리에서 함수 주소 가져오기
    #define LOAD_FUNCTION(name) \
        do { \
            dlerror(); \
            *(void **)(&name##_func) = dlsym(handle, #name); \
            error = dlerror(); \
            if (error != NULL) { \
                printf(#name " loading failed: %s\n", error); \
                dlclose(handle); \
                return 1; \
            } \
        } while (0)

    LOAD_FUNCTION(is_overflow);
    LOAD_FUNCTION(int_to_binary);
    LOAD_FUNCTION(reverse_bits);
    LOAD_FUNCTION(logical_shift_left);
    LOAD_FUNCTION(logical_shift_right);
    LOAD_FUNCTION(arithmetic_shift_right);
    LOAD_FUNCTION(extract_bits);
    LOAD_FUNCTION(insert_bits);
    LOAD_FUNCTION(count_set_bits);
    LOAD_FUNCTION(is_power_of_two);

    #undef LOAD_FUNCTION

    // 함수 호출 및 결과 출력
    char buffer[33];

    printf("is_overflow: %d\n",
           is_overflow_func(INT32_MAX, 1, ADD));

    int_to_binary_func(13, buffer, sizeof(buffer));
    printf("int_to_binary(13): %s\n", buffer);

    printf("reverse_bits(1): %u\n",
           reverse_bits_func(1));

    printf("logical_shift_left(8, 2): %u\n",
           logical_shift_left_func(8, 2));

    printf("logical_shift_right(8, 2): %u\n",
           logical_shift_right_func(8, 2));

    printf("arithmetic_shift_right(-8, 2): %d\n",
           arithmetic_shift_right_func(-8, 2));

    printf("extract_bits(13, 1, 2): %u\n",
           extract_bits_func(13, 1, 2));

    printf("insert_bits(8, 3, 1, 2): %u\n",
           insert_bits_func(8, 3, 1, 2));

    printf("count_set_bits(15): %d\n",
           count_set_bits_func(15));

    printf("is_power_of_two(16): %d\n",
           is_power_of_two_func(16));

    dlclose(handle);

    return 0;
}
