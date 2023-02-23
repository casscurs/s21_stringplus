#ifndef SRC_S21_SPRINTF_UTILS_H_
#define SRC_S21_SPRINTF_UTILS_H_

#include <math.h>

#include "../s21_string.h"
#include "s21_sprintf.h"
#include "s21_sprintf_options.h"

// conversions
int s21_atoi(const char **str);
char s21_digit_to_char(int digit, int text_case);
char *s21_unsigned_to_str(unsigned long int num, unsigned int notation,
                          int text_case);
char *s21_mantissa_to_str(long double num, int *next_digit, int precision);
char *s21_float_to_str(long double num);
void s21_WchInStr(char *str, wchar_t *wstr, int len);
void s21_invert_str(char *origin, char *inverted);

// obtainig values
void s21_split_float(long double double_var, long double *ones,
                     long double *tens);
long double s21_get_double_variable(opt options, va_list var_arg);
long unsigned s21_get_unsigned_variable(opt options, va_list var_arg,
                                        int *is_negative);
unsigned s21_get_exponent(long double *mantissa);
void s21_get_char_sign(int is_negative, char *sign, opt options);
void s21_precision_CS(int *wlen, opt options);

// output formatting
void s21_apply_num_precision(char **buf, int precision);
void s21_add_notation(char **buf, opt options);
void s21_add_sign(char **buf, char sign);
void s21_apply_width(char **buf, opt options, var *variables);
void s21_delete_trailing_zeros(char **num_string, specifi format_spec);
void s21_math_rounding(char **num_string, int next_digit);

// others
size_t s21_wstrlen(wchar_t *wstr);
int s21_recording(char **str, var *variables);
char *s21_nan_inf(long double variable, char *sign, specifi format_spec);
char *s21_sum_and_free_strings(char *string1, char *string2);
int s21_is_spec_int(specifi spec);
int s21_is_spec_float(specifi spec);

#endif  // SRC_S21_SPRINTF_UTILS_H_