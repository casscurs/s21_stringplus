#include "s21_sprintf_utils.h"

int s21_atoi(const char **str) {
  int res = 0;
  while ((**str > 47) && (**str < 58)) {
    res = res * 10 + (int)**str - 48;
    *str += 1;
  }
  return res;
}

char s21_digit_to_char(int digit, int text_case) {
  char ch = '\0';
  if (digit >= 0 && digit < 10) {
    ch = (char)(digit + 48);  // 0 - 9
  } else if (digit >= 10 && digit < 36) {
    if (text_case == 0) {
      ch = (char)(digit + 87);  // a - z
    } else {
      ch = (char)(digit + 55);  // A - Z
    }
  }
  return ch;
}

char *s21_unsigned_to_str(unsigned long int num, unsigned int notation,
                          int text_case) {
  char *ascii_str = s21_NULL, *reverse_str = s21_NULL;
  int length = 0;

  ascii_str = (char *)malloc(sizeof(char) * 50);
  reverse_str = (char *)malloc(sizeof(char) * 50);
  if (reverse_str && ascii_str) {
    if (num == 0) {
      reverse_str[0] = '0';
      length += 1;
    }
    while (num != 0) {
      int digit = num % notation;
      num /= notation;
      reverse_str[length] = s21_digit_to_char(digit, text_case);
      length += 1;
    }
    reverse_str[length] = '\0';
    s21_invert_str(reverse_str, ascii_str);
  }
  if (reverse_str) {
    free(reverse_str);
  }
  return ascii_str;
}

char *s21_mantissa_to_str(long double num, int *next_digit, opt options) {
  char *ascii_str = s21_NULL;
  int length = 0, digit = 0, precision = -1;
  precision = (options.precision >= 0 )? options.precision : 6;

  num *= (num < 0) ? -1 : 1;
  digit = floorl(num);
  num = (num - digit) * 10;

  ascii_str = (char *)malloc(sizeof(char) * (precision + 5));
  if (ascii_str) {
    ascii_str[length++] = s21_digit_to_char(digit, 0);
    if (precision > 0 || options.flags.SHARP) {
      ascii_str[length++] = '.';
    }
    for (int i = 0; i < precision; i++) {
      digit = (floorl(num) >= 0) ? (int)floorl(num) : 0;
      num = (num - digit) * 10;
      ascii_str[length++] = s21_digit_to_char(digit, 0);
    }
    ascii_str[length] = '\0';
    *next_digit = (int)floorl(num);
  }
  return ascii_str;
}

void s21_invert_str(char *origin, char *inverted) {
  if (origin && inverted) {
    int length = 0;
    length = s21_strlen(origin);
    for (int i = 0; i < length; i++) {
      inverted[i] = origin[length - 1 - i];
    }
    inverted[length] = '\0';
  }
}

unsigned s21_get_exponent(long double *mantissa) {
  // возвращает модуль экспоненты и нормализует мантиссу
  unsigned exponent = 0;
  while (*mantissa >= 10. && *mantissa <= LDBL_MAX) {
    *mantissa = *mantissa / 10.;
    exponent += 1;
  }
  while (*mantissa < 1. && *mantissa >= LDBL_TRUE_MIN) {
    *mantissa = *mantissa * 10.;
    exponent += 1;
  }
  return exponent;
}

void s21_get_char_sign(int is_negative, char *sign, opt options) {
  if (options.format_spec != U && options.format_spec != O &&
      options.format_spec != XLOW && options.format_spec != XUP) {
    if (is_negative < 0) {
      *sign = '-';
    } else {
      if (options.flags.PLUS) {
        *sign = '+';
      } else if (options.flags.SPACE) {
        *sign = ' ';
      }
    }
  }
}

void s21_apply_num_precision(char **buf, int precision) {
  if (*buf) {
    int len_buf = 0;
    len_buf = s21_strlen(*buf);
    if ((precision == 0) && (s21_strcmp(*buf, "0") == 0)) {
      *buf[0] = '\0';
    } else if (len_buf < precision) {
      int n_zeros = 0;
      char *temp = s21_NULL;
      n_zeros = precision - len_buf;
      temp = (char *)malloc(sizeof(char) * (precision + 1));
      if (temp) {
        char *tmp_ptr = s21_NULL;
        for (int i = 0; i < n_zeros; i++) {
          temp[i] = '0';
        }
        temp[n_zeros] = '\0';
        s21_strcat(temp, *buf);
        tmp_ptr = (char *)realloc(*buf, sizeof(char) * (precision + 1));
        if (tmp_ptr) {
          *buf = tmp_ptr;
          s21_strcpy(*buf, temp);
        }
        free(temp);
      }
    }
  }
}

void s21_add_sign(char **buf, char sign) {
  if (sign && *buf) {
    int len_buf = 0;
    char *temp = s21_NULL;
    len_buf = s21_strlen(*buf);
    temp = (char *)malloc(sizeof(char) * (len_buf + 2));
    if (temp) {
      char *tmp_ptr = s21_NULL;
      temp[0] = sign;
      temp[1] = '\0';
      s21_strcat(temp, *buf);
      tmp_ptr = (char *)realloc(*buf, sizeof(char) * (len_buf + 2));
      if (tmp_ptr) {
        *buf = tmp_ptr;
        s21_strcpy(*buf, temp);
      }
      free(temp);
    }
  }
}

void s21_add_notation(char **buf, opt options) {
  if (*buf && ((options.flags.SHARP &&
                (options.format_spec == O || options.format_spec == XLOW ||
                 options.format_spec == XUP)) ||
               options.format_spec == P)) {
    int len_buf = 0;
    char *temp = s21_NULL;
    len_buf = s21_strlen(*buf);
    temp = (char *)malloc(sizeof(char) * (len_buf + 3));
    if (temp) {
      char *tmp_ptr = s21_NULL;
      temp[0] = '\0';
      if ((options.format_spec == O) && (**buf != '0')) {
        s21_strcat(temp, "0");
      }
      if (options.format_spec == XLOW || options.format_spec == P) {
        s21_strcat(temp, "0x");
      }
      if (options.format_spec == XUP) {
        s21_strcat(temp, "0X");
      }
      s21_strcat(temp, *buf);
      tmp_ptr = (char *)realloc(*buf, sizeof(char) * (len_buf + 3));
      if (tmp_ptr) {
        *buf = tmp_ptr;
        s21_strcpy(*buf, temp);
      }
      free(temp);
    }
  }
}

void s21_apply_width(char **buf, opt options, var *variables) {
  if (*buf && ((int)s21_strlen(*buf) < options.min_width)) {
    char filler = ' ';
    int n_fillers = 0;
    n_fillers = options.min_width - s21_strlen(*buf);
    if (!options.flags.MINUS && options.flags.ZERO) {
      filler = '0';
    }
    variables->temp = calloc((options.min_width + 2), sizeof(char));
    s21_mem_check(variables->temp, variables);
    for (int i = 0; i < n_fillers; i++) {
      (variables->temp)[i] = filler;
    }
    (variables->temp)[n_fillers] = '\0';
    variables->tmp_ptr =
        (char *)realloc(*buf, sizeof(char) * (options.min_width + 2));
    s21_mem_check(variables->tmp_ptr, variables);
    if (variables->tmp_ptr) {
      *buf = variables->tmp_ptr;
      if (options.flags.MINUS) {
        s21_strcat(*buf, variables->temp);
      } else {
        s21_strcat(variables->temp, *buf);
        s21_strcpy(*buf, variables->temp);
      }
    }
    free(variables->temp);
    variables->temp = s21_NULL;
  }
}

void s21_WchInStr(char *str, wchar_t *wstr, int len) {
  int buflen = 0;
  char *p = s21_NULL;
  buflen = s21_strlen(str);
  p = str + buflen;
  for (int i = 0; i < len; i++) {
    *(p++) = (char)*(wstr++);
  }
  *p = '\0';
}

size_t s21_wstrlen(wchar_t *wstr) {
  wchar_t *p = s21_NULL;
  p = wstr;
  for (; *p; p++)
    ;
  return p - wstr;
}

int s21_recording(char **str, var *variables) {
  int length = 0;
  s21_strcpy(*str, variables->Chbuf);
  length = s21_strlen(variables->Chbuf);
  *str = *str + length;
  free(variables->Chbuf);
  variables->Chbuf = s21_NULL;
  return (length);
}

long double s21_get_double_variable(opt options, va_list var_arg) {
  long double double_var = 0;
  if (options.len_spec == LUP) {
    double_var = va_arg(var_arg, long double);
  } else {
    double_var = va_arg(var_arg, double);
  }
  return double_var;
}

long unsigned s21_get_unsigned_variable(opt options, va_list var_arg,
                                        int *is_negative) {
  // считывает целочисленную переменную в виде беззнакового целого,
  // при наличии знака записывает его в is_negative
  long unsigned u_var = 0;
  if (options.format_spec == D || options.format_spec == I) {
    long int int_var = 0;
    if (options.len_spec == LLOW) {
      int_var = va_arg(var_arg, long int);
      u_var = labs(int_var);
    } else if (options.len_spec == H) {
      int_var = (short)va_arg(var_arg, int);
      u_var = labs(int_var);
    } else {
      int_var = va_arg(var_arg, int);
      u_var = labs(int_var);
    }
    *is_negative = (int_var < 0) ? -1 : 1;
  } else if (options.format_spec == U || options.format_spec == O ||
             options.format_spec == XLOW || options.format_spec == XUP) {
    if (options.len_spec == LLOW) {
      u_var = (unsigned long int)va_arg(var_arg, unsigned long int);
    } else if (options.len_spec == H) {
      u_var = (unsigned short int)va_arg(var_arg, unsigned int);
    } else {
      u_var = (unsigned int)va_arg(var_arg, unsigned int);
    }
  } else if (options.format_spec == P) {
    void *ptr = s21_NULL;
    ptr = va_arg(var_arg, void *);
    u_var = (unsigned long)ptr;
  }
  return u_var;
}

void s21_split_float(long double double_var, long double *ones,
                     long double *tens) {
  *ones = fmodl(double_var, 10.L);
  *tens = (double_var - *ones) / 10.L;
}

char *s21_float_to_str(long double num) {
  char *ascii_str = s21_NULL, *reverse_str = s21_NULL;
  int buf_len = 0;
  int length = 0;
  long double tmp_num = 0;
  num *= (num < 0) ? -1 : 1;
  tmp_num = num;
  while (tmp_num > 1) {
    buf_len += 1;
    tmp_num /= 10;
  }
  buf_len = (buf_len > 0) ? buf_len : 2;
  ascii_str = (char *)calloc((buf_len + 5), sizeof(char));
  reverse_str = (char *)calloc((buf_len + 5), sizeof(char));
  if (ascii_str && reverse_str) {
    while (num >= 1L) {
      int digit = 0;
      digit = (int)fmodl(num, 10);
      num /= 10;
      reverse_str[length] = s21_digit_to_char(digit, 0);
      length += 1;
    }
    reverse_str[length] = '\0';
    s21_invert_str(reverse_str, ascii_str);
  }
  if (reverse_str) {
    free(reverse_str);
  }
  return ascii_str;
}

void s21_math_rounding(char **num_string, int next_digit, char *exp_sign, unsigned *u_exp) {
  if (*num_string && next_digit >= 5) {
    int not_rounded = 1, position = 0;
    position = s21_strlen(*num_string) - 1;
    while (position >= 0 && not_rounded) {
      if ((*num_string)[position] == '.') {
        position -= 1;
      }
      if ((*num_string)[position] == '9') {
        (*num_string)[position] = '0';
        position -= 1;
      } else {
        (*num_string)[position] = (char)((*num_string)[position] + 1);
        not_rounded = 0;
      }
    }
    if (position == -1) {
      char *tmp_ptr = s21_NULL, *tmp_array = s21_NULL;
      int num_string_len = 0;
      num_string_len = s21_strlen(*num_string);
      tmp_array = (char *)calloc(num_string_len + 1, sizeof(char));
      if (tmp_array) {
        s21_strcpy(tmp_array, *num_string);
        tmp_ptr = (char *)realloc(*num_string, sizeof(char)*(num_string_len + 5));
        if (tmp_ptr) {
          tmp_ptr[0] = '1';
          tmp_ptr[1] = '\0';
          s21_strcat(tmp_ptr, tmp_array);
          if (u_exp) {
            if (*exp_sign == '-') {
              *u_exp = *u_exp - 1;
              if (*u_exp == 0) {
                *exp_sign = '+';
              }
            } else {
              *u_exp = *u_exp + 1;
            }
            tmp_ptr[2] = tmp_ptr[1];
            tmp_ptr[1] = '.';
            tmp_ptr[s21_strlen(tmp_ptr) - 1] = '\0';
          }
          *num_string = tmp_ptr;
        }
        free(tmp_array);
      }
    }
  }
}

void s21_delete_trailing_zeros(char **num_string, opt options) {
  if (*num_string && options.flags.SHARP == 0 &&
      (options.format_spec == GUP || options.format_spec == GLOW)) {
    int position = 0;
    position = s21_strlen(*num_string) - 1;
    while ((position > 0) && 
           ((*num_string)[position] == '0' ||
            ((*num_string)[position] == '.'))) {
      (*num_string)[position] = '\0';
      position -= 1;
    }
  }
}

char *s21_nan_inf(long double variable, char *sign, specifi format_spec) {
  char *buf = s21_NULL;
  buf = (char *)calloc(5, sizeof(char));
  if (buf) {
    if (variable != variable) {
      if (format_spec == GUP || format_spec == EUP) {
        s21_strcpy(buf, "NAN");
      } else {
        s21_strcpy(buf, "nan");
      }
      *sign = '\0';
    } else {
      if (format_spec == GUP || format_spec == EUP) {
        s21_strcpy(buf, "INF");
      } else {
        s21_strcpy(buf, "inf");
      }
    }
  }
  return buf;
}

char *s21_sum_and_free_strings(char *string1, char *string2) {
  char *buf = s21_NULL;
  if (string1 && string2) {
    buf = (char *)calloc((s21_strlen(string1) + s21_strlen(string2) + 2),
                         sizeof(char));
    if (buf) {
      s21_strcat(buf, string1);
      s21_strcat(buf, string2);
    }
  }
  if (string1) {
    free(string1);
  }
  if (string2) {
    free(string2);
  }
  return buf;
}

void s21_precision_CS(int *wlen, opt options) {
  if (((*wlen) > options.precision) && (options.precision > 0)) {
    (*wlen) = options.precision;
  } else if (options.precision == 0) {
    *wlen = 0;
  }
}

int s21_is_spec_int(specifi spec) {
  int res = 0;
  if (spec == I || spec == D || spec == U || spec == O || spec == XLOW ||
      spec == XUP || spec == P) {
    res = 1;
  }
  return res;
}

int s21_is_spec_float(specifi spec) {
  int res = 0;
  if (spec == F || spec == ELOW || spec == EUP || spec == GLOW || spec == GUP) {
    res = 1;
  }
  return res;
}