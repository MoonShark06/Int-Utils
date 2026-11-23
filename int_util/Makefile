
CC = gcc

CFLAGS = -Wall -Wextra -Iinclude
PICFLAGS = -fPIC

LIB = libintutils
SRC = src/int_util.c

.PHONY: all static shared test clean

all: static shared test

# 정적 라이브러리
static: $(LIB).a

$(LIB).a: int_util.o
	ar rcs $@ $^

int_util.o: $(SRC) include/int_util.h
	$(CC) $(CFLAGS) -c $(SRC) -o $@

# 공유 라이브러리
shared: $(LIB).so

$(LIB).so: int_util_pic.o
	$(CC) -shared -o $@ $^

int_util_pic.o: $(SRC) include/int_util.h
	$(CC) $(CFLAGS) $(PICFLAGS) -c $(SRC) -o $@

# 테스트
test: test_static test_shared test_runtime
	./test_static
	LD_LIBRARY_PATH=. ./test_shared
	./test_runtime

test_static: test/test_static.c $(LIB).a
	$(CC) $(CFLAGS) $< ./$(LIB).a -o $@

test_shared: test/test_shared.c $(LIB).so
	$(CC) $(CFLAGS) $< -L. -lintutils -o $@

test_runtime: test/test_runtime.c $(LIB).so
	$(CC) $(CFLAGS) $< -ldl -o $@

# 클린
clean:
	rm -f *.o *.a *.so test_static test_shared test_runtime
