#ifndef SRC_S21_SPRINTF_OPTIONS_H_
#define SRC_S21_SPRINTF_OPTIONS_H_

#include <stdarg.h>

typedef struct flags {
  int MINUS;
  int PLUS;
  int SPACE;
  int ZERO;
  int SHARP;
} flag;

typedef enum specifiers {
  NO_SPEC,
  C,
  D,
  I,
  F,
  S,
  U,
  PERC,
  GLOW,
  GUP,
  ELOW,
  EUP,
  XLOW,
  XUP,
  O,
  N,
  P
} specifi;

typedef enum lenSpec { NO_LEN_SPEC, H, LLOW, LUP } len;

typedef struct options {
  flag flags;
  int min_width;  // -1: undefined
  int precision;  // -1: undefined
  len len_spec;
  specifi format_spec;
} opt;

void s21_init_options(opt *options);
void s21_get_options(const char **format, opt *options, va_list var_arg);

void s21_get_flags(const char **format, opt *options);
void s21_get_min_width(const char **format, opt *options, va_list var_arg);
void s21_get_precision(const char **format, opt *options, va_list var_arg);
void s21_get_len_spec(const char **format, opt *options);
void s21_get_format_spec(const char **format, opt *options);

#endif  // SRC_S21_SPRINTF_OPTIONS_H_