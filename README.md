Integer Utility Library

32비트 정수의 오버플로우 검사와 비트 연산을 제공하는 C 라이브러리입니다.

정적 라이브러리, 공유 라이브러리, 런타임 동적 로딩 방식으로 빌드하고 사용할 수 있습니다.

-----------------------------------------------------------------

Features

is_overflow(int32_t a, int32_t b, Operation op) 
  정수의 덧셈, 뺄셈, 곱셈, 나눗셈에서 오버플로 여부를 검사합니다.
  반환값이 1이면 오버플로 발생 0이면 발생하지 않음 -1이면 잘못된 접근입니다.

int_to_binary(uint32_t value, char *buffer, size_t buffer_size)
  32비트의 unsigned 정수를 2진수 문자열로 변환합니다.
  변환에 성공하면 0을 버퍼가 잘못되거나 공간이 부족하면 -1을 반환합니다.

reverse_bits(uint32_t value)
  32비트의 unsigned 정수를 반대로 뒤집고 반환합니다.

count_set_bits(uint32_t value)
  1로 설정된 비트의 개수를 반환합니다.

is_power_of_two(uint32_t value)
  2의 거듭제곱인지 검사합니다.
  2의 거듭제곱일땐 1을 아닐땐 0을 반환합니다.

logical_shift_left(uint32_t value, unsigned int count)
  비트를 왼쪽으로 이동시킵니다. 빈 비트는 0으로 채워집니다.
  시프트 연산 결과를 반환하고 count가 32 이상일땐 0을 반환합니다.

logical_shift_right(uint32_t value, unsigned int count)
  비트를 오른쪽으로 이동시킵니다. 빈 비트는 0으로 채워집니다.
  시프트 연산 결과를 반환하고 count가 32 이상일땐 0을 반환합니다.

arithmetic_shift_right(int32_t value, unsigned int count)
  비트를 오른쪽으로 이동시킵니다. 최상위비트가 부호비트로 유지됩니다.
  시프트 연산 결과를 반환하고 count가 32 이상일때 음수는 -1, 0과 양수는 0을 반환합니다.

extract_bits(uint32_t value, unsigned int start, unsigned int length)
  start 위치에서 length만큼의 비트를 추출합니다.
  잘못된 범위거나 length가 0이면 0을 반환합니다.

insert_bits(uint32_t value, uint32_t new_value, unsigned int start, unsigned int length)
  start 위치에서 length만큼을 new_value로 교체합니다.
  질못된 범위거나 length가 0이면 value를 그대로 반환합니다.

-----------------------------------------------------------------

Structure

int_util/
├── include/
│   └── int_util.h
├── src
│   └── int_util.c
├── test/
│   ├── test_static.c
│   ├── test_shared.c
│   └── test_runtime.c
├── Makefile
└── README.md

-----------------------------------------------------------------

Build

make 명령어로 빌드합니다.
빌드 과정에서 정적 라이브러리, 공유 라이브러리, 정적 라이브러리 테스트, 공유 라이브러리 테스트, 런타임 동적로딩 테스트 파일이 생성됩니다,

-----------------------------------------------------------------

Library Usage

gcc -Iinclude test/test_static.c ./libintutils.a -o test_static
./test_static
  정적 라이브러리를 링크하여 실행파일을 생성합니다.
  링크시 라이브러리 코드가 실행 파일에 포합됩니다.

gcc -Iinclude test/test_shared.c -L. -lintutils -o test_shared
LD_LIBRARY_PATH=. ./test_shared
  공유 라이브러리를 링크하여 실행 파일을 생성합니다.
  프로그램 실행시 동적 로더를 통해 연결됩니다.

gcc -Iinclude test/test_runtime.c -ldl -o test_runtime
./test_runtime
  dlopen(), dlsym(), dlclose()를 통해 실행중 필요할때 라이브러리를 직접 불러옵니다.

-----------------------------------------------------------------

Test

make test
  정적 라이브러리, 공유 라이브러리, 런타임 동적 도딩의 테스트를 순서대로 실행합니다.

-----------------------------------------------------------------

Clean

make clean
  빌드 과정에서 생성된 오브젝트 파일, 라이브러리 파일, 테스트파일을 삭제합니다.

-----------------------------------------------------------------

Environment

Language: C
Compiler: GCC
Build Tool: Make
Platform: Linux

