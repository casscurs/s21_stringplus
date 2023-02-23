#ifndef SRC_S21_SPRINTF_UTILS_H_
#define SRC_S21_SPRINTF_UTILS_H_

#include <math.h>
#include "s21_sprintf.h"
#include "s21_sprintf_options.h"
#include <float.h>

// conversions
int s21_atoi(const char **str);
char digit_to_char(int digit, int text_case);
char *unsigned_to_str(unsigned long int num, unsigned int notation,
                      int text_case);
char *mantissa_to_str(long double num, int *next_digit, int precision);
char *float_to_str(long double num);
void WchInStr(char *str, wchar_t *wstr, int len);
void invert_str(char *origin, char *inverted);

// obtainig values
void split_float(long double double_var, long double *ones, long double *tens);
long double get_double_variable(opt options, va_list var_arg);
long unsigned get_unsigned_variable(opt options, va_list var_arg,
                                    int *is_negative);
unsigned get_exponent(long double *mantissa);
void get_char_sign(int is_negative, char *sign, opt options);
void precision_CS(int* wlen, opt options);

// output formatting
void apply_num_precision(char **buf, int precision);
void add_notation(char **buf, opt options);
//void apply_width(char **buf, opt options, var *variables);
void delete_trailing_zeros(char **num_string, specifi format_spec);
void math_rounding(char **num_string, int next_digit);

// others
int wstrlen(wchar_t *wstr);
//int recording(char **str, var *variables);
char *nan_inf(long double variable, char *sign, specifi format_spec);
char *sum_and_free_strings(char *string1, char *string2);
int is_spec_int (specifi spec);
int is_spec_float (specifi spec);

#endif  // SRC_S21_SPRINTF_UTILS_H_