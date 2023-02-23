NAME = s21_sprintf
HEADER = s21_sprintf.h s21_sprintf_options.h s21_sprintf_utils.h s21_sprintf_template.h
SRCS = s21_sprintf.c s21_sprintf_options.c s21_sprintf_utils.c
OBJS	= $(patsubst %.c,%.o,$(SRCS))
D_FILES = $(patsubst %.c,%.d,$(SRCS))
FLAGS =	-Wall -Wextra -g -D_GNU_SOURCE 
CC = gcc

all : $(NAME)

%.o : %.c  $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@ -MD

include $(wildcard $(D_FILES))

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

test: fclean
	$(CC) $(FLAGS) $(SRCS) check.c tests/*.c -lcheck -o test
	./test

gcov_report:
	mkdir -p html
	$(CC) $(FLAGS) $(SRCS) check.c tests/*.c -lcheck -o test --coverage
	./test
	gcov -b -l -p -c s21_*.gcno ## Run code coverage
	gcovr -o html/gcov_report.html --html --html-details ## Generate gcovr report
	open html/gcov_report.html
	rm *.gcno *.gcda *.gcov

clean:
	rm -f $(OBJS) $(D_FILES)

fclean: clean
	rm -f $(NAME)
	rm -rf test func *.gcno *.gcda *.gcov *.html *.css html/*
	rm -rf html

re:	fclean all

.PHONY : all clean fclean re