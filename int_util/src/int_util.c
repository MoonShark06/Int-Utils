#include <stdint.h>
#include <stddef.h>
#include "int_util.h"

int is_overflow(int32_t a, int32_t b, Operation op){
  switch (op)
  {
  case ADD: {
    if (b > 0 && a > INT32_MAX - b){
      return 1;
    }
    if (b < 0 && a < INT32_MIN - b){
      return 1;
    }
    break;
  }

  case SUB: {
    if (b < 0 && a > INT32_MAX + b){
      return 1;
    }
    if (b > 0 && a < INT32_MIN + b){
      return 1;
    }
    break;  
  }

  case MUL: {
    int64_t result = (int64_t)a * b;

    if (result > INT32_MAX || result < INT32_MIN) {
        return 1;
    }
    break;   
  }

  case DIV: {
    if (b == 0){
      return -1;
    }

    if (a == INT32_MIN && b == -1){
      return 1;
    }
    break;    
  }
  default:
    return -1;
  }
  
  return 0;
}


int int_to_binary(uint32_t value, char *buffer, size_t buffer_size) {
    if (buffer == NULL || buffer_size == 0) {
        return -1;
    }

    if (value == 0) {
        if (buffer_size < 2) {
            return -1;
        }

        buffer[0] = '0';
        buffer[1] = '\0';
        return 0;
    }

    size_t index = 0;

    while (value > 0) {
        if (index + 1 >= buffer_size) {
            return -1;
        }

        buffer[index] = (value % 2) + '0';
        value /= 2;
        index++;
    }

    // 뒤집기
    for (size_t i = 0; i < index / 2; i++) {
        char temp = buffer[i];
        buffer[i] = buffer[index - 1 - i];
        buffer[index - 1 - i] = temp;
    }

    buffer[index] = '\0';

    return 0;
}

int count_set_bits(uint32_t value) {
    int count = 0;

    while (value > 0) {
        count += value & 1; // 1 & 1 = 1 , 1(0) & 0(1) = 0
        value >>= 1;
    }

    return count;
}

int is_power_of_two(uint32_t value) {
    if (value == 0) {
        return 0;
    }

    return count_set_bits(value) == 1; // 1인 비트가 1개면 2의 거듭제곱
}

uint32_t reverse_bits(uint32_t value) {
    uint32_t result = 0;

    for (int i = 0; i < 32; i++) {
        result <<= 1; // result 왼쪽 이동
        result |= (value & 1); // value 오른쪽 비트 result에 추가
        value >>= 1; // value 오른쪽 이동
    }

    return result;
}

uint32_t logical_shift_left(uint32_t value, unsigned int count) {
    if (count >= 32) {
        return 0;
    }

    return value << count;
}

uint32_t logical_shift_right(uint32_t value, unsigned int count) {
    if (count >= 32) {
        return 0;
    }

    return value >> count;
}

int32_t arithmetic_shift_right(int32_t value, unsigned int count) {
    if (count >= 32) {
        return (value < 0) ? -1 : 0;
    }

    if (count == 0) {
        return value;
    }

    uint32_t result = (uint32_t)value >> count;

    // 1로 채우기
    if (value < 0) {
        result |= (UINT32_MAX << (32 - count));
    }

    return (int32_t)result;
}

uint32_t extract_bits(uint32_t value, unsigned int start, unsigned int length) {
    if (start >= 32 || length == 0 || length > 32 - start) {
        return 0;
    }

    uint32_t mask;

    if (length == 32) {
        mask = UINT32_MAX;
    }
    else {
        mask = (1U << length) - 1;
    }

    return (value >> start) & mask;
}

uint32_t insert_bits(uint32_t value, uint32_t new_value,
                     unsigned int start, unsigned int length) {
    if (start >= 32 || length == 0 || length > 32 - start) {
        return value;
    }

    uint32_t mask;

    if (length == 32) {
        mask = UINT32_MAX;
    }
    else {
        mask = (1U << length) - 1;
    }

    mask <<= start;

    value &= ~mask;

    new_value = (new_value << start) & mask;

    value |= new_value;

    return value;
}