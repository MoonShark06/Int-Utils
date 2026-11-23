#ifndef INTUTILS_H
#define INTUTILS_H

#include <stdint.h>
#include <stddef.h>

typedef enum {
  ADD,
  SUB,
  MUL,
  DIV
} Operation; 

int is_overflow(int32_t a, int32_t b, Operation op); // 오버플로 확인

int int_to_binary(uint32_t value, char *buffer, size_t buffer_size); // 2진수 변환

int count_set_bits(uint32_t value); // 1인 비트 개수

int is_power_of_two(uint32_t value); // 2의 거듭제곱인지

uint32_t reverse_bits(uint32_t value); // 비트 뒤집기

uint32_t logical_shift_left(uint32_t value, unsigned int count); // 논리적, 산술적 왼족 이동

uint32_t logical_shift_right(uint32_t value, unsigned int count); // 논리적 오른쪽 이동

int32_t arithmetic_shift_right(int32_t value, unsigned int count); // 산술적 오른쪽 이동

uint32_t extract_bits(uint32_t value, unsigned int start, unsigned int length); // 비트 추출

uint32_t insert_bits(uint32_t original,
                     uint32_t value, 
                     unsigned int start, 
                     unsigned int length); // 비트 삽입

#endif