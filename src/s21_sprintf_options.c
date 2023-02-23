#include "s21_sprintf_options.h"

#include "s21_sprintf_utils.h"

void init_options(opt *options) {
  options->flags = (flag){0};
  options->min_width = -1;
  options->precision = -1;
  options->len_spec = 0;
  options->format_spec = 0;
}

void get_options(const char **format, opt *options, va_list var_arg) {
  get_flags(format, options);
  get_min_width(format, options, var_arg);
  get_precision(format, options, var_arg);
  get_len_spec(format, options);
  get_format_spec(format, options);
}

void get_flags(const char **format, opt *options) {
  int get_next = 1;
  while (get_next && *(*format + 1)) {
    *format += 1;
    switch (**format) {
      case '-':
        options->flags.MINUS = 1;
        break;
      case '+':
        options->flags.PLUS = 1;
        break;
      case '0':
        options->flags.ZERO = 1;
        break;
      case '#':
        options->flags.SHARP = 1;
        break;
      case ' ':
        options->flags.SPACE = 1;
        break;
      default:
        get_next = 0;
    }
  }
}

void get_min_width(const char **format, opt *options, va_list var_arg) {
  int min_width = -1;
  if ((**format > 47) && (**format < 58)) {
    min_width = atoi(format);
  } else if (**format == '*') {
    min_width = va_arg(var_arg, int);
    if (min_width < 0) {
      min_width *= -1;
      options->flags.MINUS = 1;
    }
    *format += 1;
  }
  options->min_width = min_width;
}

void get_precision(const char **format, opt *options, va_list var_arg) {
  int precision = -1;
  if ((**format == '.') && *(*format + 1)) {
    *format += 1;
    if ((**format > 47) && (**format < 58)) {
      precision = atoi(format);
    } else if (**format == '*') {
      precision = va_arg(var_arg, int);
      *format += 1;
    } else {
      precision = 0;
    }
  }
  options->precision = precision;
}

void get_len_spec(const char **format, opt *options) {
  char specifiers[] = "hlL";
  char *spec_ptr = NULL;
  if (**format) {
    spec_ptr = strchr(specifiers, **format);
    if (spec_ptr) {
      options->len_spec = (spec_ptr - specifiers + 1);
      *format += 1;
    }
  }
}

void get_format_spec(const char **format, opt *options) {
  char specifiers[] = "cdifsu%gGeExXonp";
  char *spec_ptr = NULL;
  if (**format) {
    spec_ptr = strchr(specifiers, **format);
    if (spec_ptr) {
      options->format_spec = (spec_ptr - specifiers + 1);
      *format += 1;
    }
  }
}
