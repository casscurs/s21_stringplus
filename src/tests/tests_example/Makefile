CC=gcc -g
CFLAGS=-Wall -Werror -Wextra -std=c11

all: all_functions clean

C_FILES=$(wildcard s21_*.c)
O_FILES=*.o

ifeq ($(UNAME), Linux)
 GFLAGS =  -lm -lsubunit -lpthread -lrt
endif

s21_decimal.a: all_functions
	ar rc s21_decimal.a $(O_FILES)
	ranlib s21_decimal.a
	rm -rf *.o

test: clean s21_decimal.a
	$(CC) $(FLAGS) s21_decimal.a check.c tests/*.c -lcheck -o test
	./test

gcov_report:
	mkdir -p html
	$(CC) $(FLAGS) $(C_FILES) check.c tests/*.c -lcheck -o test --coverage
	./test
	rm check*.gcda check*.gcno comparisons*.gcda comparisons*.gcno all*.gcda all*.gcno s21_long_decimal*.gcda s21_long_decimal*.gcno s21_mul*.gcno s21_mul*.gcda
	gcov -b -l -p -c s21_*.gcno
	gcovr -o html/gcov_report.html --html --html-details
	open html/gcov_report.html
	rm *.gcno *.gcda *.gcov

all_functions: $(C_FILES)
	gcc -c $(CFLAGS) $(C_FILES)
	# gcc $(CFLAGS) main.c $(C_FILES) -o func


main: $(C_FILES)
	gcc $(CFLAGS) print.c main.c $(C_FILES)

style: clean
	mv ../materials/linters/.clang-format .
	clang-format -i *.c 
	clang-format -i *.h
	clang-format -n *.c
	clang-format -n *.h
	mv .clang-format ../materials/linters/

clean:
	rm -rf *.o *.a test func *.gcno *.gcda *.gcov *.html *.css html/*
	# rm -d html

rebuild:
	clean all
