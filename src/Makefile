CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++20
SRC =*.cpp
SRC_TEST = ./tests/*.cpp
UNAME_S = $(shell uname -s)

ifndef VERBOSE
	MAKEFLAGS += --no-print-directory
endif

ifeq ($(UNAME_S),Linux)
	CC += -DLINUX
	FLAGS_TEST = -lgtest -lgtest_main -pthread
    CMD_OPEN = xdg-open
else ifeq ($(UNAME_S),Darwin)
	CC += -DDARWIN
	FLAGS_TEST = -lgtest -lgtest_main -pthread -I/opt/homebrew/include -L/opt/homebrew/lib
	CMD_OPEN = open
endif

.PHONY: test s21_matrix_oop.a gcov_report

all:
all: gcov_report test s21_matrix_oop.a

test:
test: s21_matrix_oop.a
	@rm -rf	./$@
	$(CC) $(CFLAGS) $(SRC_TEST) ./s21_matrix_oop.a $(FLAGS_TEST) -o ./$@

s21_matrix_oop.a:
	@rm -rf ./$@
	$(CC) $(CFLAGS) -c $(SRC)
	@ar rc ./$@ ./*.o
	@ranlib ./$@
	@rm -rf ./*.o

gcov_report: clean
	@rm -rf $@ report *.info *.gcda *.gcno
	$(CC) -c $(SRC) --coverage
	@ar rcs libs21_matrix_oop.a *.o
	@ranlib libs21_matrix_oop.a
	@rm -rf *.o
	$(CC) $(SRC_TEST)  -L. -ls21_matrix_oop --coverage $(FLAGS_TEST) -std=c++20 -o $@
	-@./$@ > /dev/null
	@mkdir report
	@lcov --ignore-errors inconsistent --exclude '*/tests/*.cpp' --exclude '*/gtest/' --branch-coverage -q -o $@.info -c -d .
	@lcov --ignore-errors inconsistent -q -r $@.info '/usr/*' -o $@.info
	@genhtml --ignore-errors inconsistent --ignore-errors category -q $@.info -o report
	@rm -rf *.gcno *.gcda *.gcov *.info libs21_matrix_oop.a
	$(CMD_OPEN) report/index.html

clean:
	@rm -rf \
	./test ./gcov_report ./report \
	*.a *.o *.gcno *.gcda *.gcov *.info

open: SHELL:=/bin/bash
open:
	$(CMD_OPEN) "./report/index.html"

clangtest:
	@clang-format --style=Google -n ./*.h ./*.cpp ./tests/*.h ./tests/*.cpp

clang:
	@clang-format --style=Google -i ./*.h ./*.cpp ./tests/*.h ./tests/*.cpp