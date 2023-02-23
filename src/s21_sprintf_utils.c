#include "s21_sprintf_utils.h"
#include <float.h>


int s21_atoi(const char **str) {
  int res = 0;
  while ((**str > 47) && (**str < 58)) {
    res = res * 10 + (int)**str - 48;
    *str += 1;
  }
  return res;
}

char digit_to_char(int digit, int text_case) {
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

char *unsigned_to_str(unsigned long int num, unsigned int notation,
                      int text_case) {
  char *ascii_str = NULL, *reverse_str = NULL;
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
      reverse_str[length] = digit_to_char(digit, text_case);
      length += 1;
    }
    reverse_str[length] = '\0';
    invert_str(reverse_str, ascii_str);
  }
  if (reverse_str) {
    free(reverse_str);
  }
  return ascii_str;
}

char *mantissa_to_str(long double num, int *next_digit, int precision) {
  char *ascii_str = NULL;
  int length = 0, digit = 0;

  num *= (num < 0) ? -1 : 1;
  digit = floorl(num);
  num = (num - digit) * 10;

  ascii_str = (char *)malloc(sizeof(char) * (precision + 5));
  if (ascii_str) {
    ascii_str[length++] = digit_to_char(digit, 0);
    if (precision > 0) {
      ascii_str[length++] = '.';
    }
    for (int i = 0; i < precision; i++) {
      digit = (floorl(num) >= 0) ? (int)floorl(num) : 0;
      num = (num - digit) * 10;
      ascii_str[length++] = digit_to_char(digit, 0);
    }
    ascii_str[length] = '\0';
    *next_digit = (int)floorl(num);
  }
  return ascii_str;
}

void invert_str(char *origin, char *inverted) {
  if (origin && inverted) {
    int length = 0;
    length = strlen(origin);
    for (int i = 0; i < length; i++) {
      inverted[i] = origin[length - 1 - i];
    }
    inverted[length] = '\0';
  }
}

unsigned get_exponent(long double *mantissa) {
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

void get_char_sign(int is_negative, char *sign, opt options) {
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

void apply_num_precision(char **buf, int precision) {
  if (*buf) {
    int len_buf = 0;
    len_buf = strlen(*buf);
    if ((precision == 0) && (strcmp(*buf, "0") == 0)) {
      *buf[0] = '\0';
    } else if (len_buf < precision) {
      int n_zeros = 0;
      char *temp = NULL;
      n_zeros = precision - len_buf;
      temp = (char *)malloc(sizeof(char) * (precision + 1));
      if (temp) {
        char *tmp_ptr = NULL;
        for (int i = 0; i < n_zeros; i++) {
          temp[i] = '0';
        }
        temp[n_zeros] = '\0';
        strcat(temp, *buf);
        tmp_ptr = (char *)realloc(*buf, sizeof(char) * (precision + 1));
        if (tmp_ptr) {
          *buf = tmp_ptr;
          strcpy(*buf, temp);
        }
        free(temp);
      }
    }
  }
}

void add_notation(char **buf, opt options) {
  if (*buf && ((options.flags.SHARP &&
      (options.format_spec == O || options.format_spec == XLOW ||
       options.format_spec == XUP)) || options.format_spec == P)) {
    int len_buf = 0;
    char *temp = NULL;
    len_buf = strlen(*buf);
    temp = (char *)malloc(sizeof(char) * (len_buf + 3));
    if (temp) {
      char *tmp_ptr = NULL;
      temp[0] = '\0';
      if ((options.format_spec == O) && (**buf != '0')) {
        strcat(temp, "0");
      }
      if (options.format_spec == XLOW || options.format_spec == P) {
        strcat(temp, "0x");
      }
      if (options.format_spec == XUP) {
        strcat(temp, "0X");
      }
      strcat(temp, *buf);
      tmp_ptr = (char *)realloc(*buf, sizeof(char) * (len_buf + 3));
      if (tmp_ptr) {
        *buf = tmp_ptr;
        strcpy(*buf, temp);
      }
      free(temp);
    }
  }
}


long double get_double_variable(opt options, va_list var_arg) {
  long double double_var = 0;
  if (options.len_spec == LUP) {
    double_var = va_arg(var_arg, long double);
  } else {
    double_var = va_arg(var_arg, double);
  }
  return double_var;
}

long unsigned get_unsigned_variable(opt options, va_list var_arg,
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
    void *ptr = NULL;
    ptr = va_arg(var_arg, void *);
    u_var = (unsigned long)ptr;
  }
  return u_var;
}

void split_float(long double double_var, long double *ones, long double *tens) {
  *ones = fmodl(double_var, 10.L);
  *tens = (double_var - *ones) / 10.L;
}

char *float_to_str(long double num) {
  char *ascii_str = NULL, *reverse_str = NULL;
  int buf_len = 0;
  int length = 0;
  num *= (num < 0) ? -1 : 1;
  buf_len = (int)roundl(log10l(num));
  buf_len = (buf_len > 0) ? buf_len : 2;
  ascii_str = (char *)malloc(sizeof(char) * (buf_len + 2));
  reverse_str = (char *)malloc(sizeof(char) * (buf_len + 2));
  if (ascii_str && reverse_str) {
    while (num >= 1L) {
      int digit = 0;
      digit = (int)fmodl(num, 10);
      num /= 10;
      reverse_str[length] = digit_to_char(digit, 0);
      length += 1;
    }
    reverse_str[length] = '\0';
    invert_str(reverse_str, ascii_str);
  }
  if (reverse_str) {
    free(reverse_str);
  }
  return ascii_str;
}

void math_rounding(char **num_string, int next_digit) {
  if (*num_string && next_digit >= 5) {
    int not_rounded = 1, position = 0;
    position = strlen(*num_string) - 1;
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
      char *tmp_ptr = NULL;
      tmp_ptr = (char *)calloc(strlen(*num_string)+3, sizeof(char));
      if (tmp_ptr) {
        tmp_ptr[0] = '1';
        strcat(tmp_ptr, *num_string);
        *num_string = tmp_ptr;
      }
    }
  }
}

void delete_trailing_zeros(char **num_string, specifi format_spec) {
  if (*num_string && (format_spec == GUP || format_spec == GLOW)) {
    int position = 0;
    position = strlen(*num_string) - 1;
    while ((position > 0) &&
           ((*num_string)[position] == '0' || (*num_string)[position] == '.')) {
      (*num_string)[position] = '\0';
      position -= 1;
    }
  }
}

char *nan_inf(long double variable, char *sign, specifi format_spec) {
  char *buf = NULL;
  buf = (char *)calloc(5, sizeof(char));
  if (buf) {
    if (variable != variable) {
      if (format_spec == GUP || format_spec == EUP) {
        strcpy(buf, "NAN");
      } else {
        strcpy(buf, "nan");
      }
      *sign = '\0';
    } else {
      if (format_spec == GUP || format_spec == EUP) {
        strcpy(buf, "INF");
      } else {
        strcpy(buf, "inf");
      }
    }
    
  }
  return buf;
}

char *sum_and_free_strings(char *string1, char *string2) {
  char *buf = NULL;
  if (string1 && string2) {
    buf = (char *)calloc((strlen(string1) + strlen(string2) + 2),
                        sizeof(char));
    if (buf) {
      strcat(buf, string1);
      strcat(buf, string2);
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

int is_spec_int (specifi spec) {
  int res = 0;
  if (spec == I || spec == D || spec == U || spec == O ||
      spec == XLOW || spec == XUP || spec == P) {
    res = 1;
  }
  return res;
}

int is_spec_float (specifi spec) {
  int res = 0;
  if (spec == F || spec == ELOW || spec == EUP ||
      spec == GLOW || spec == GUP) {
    res = 1;
  }
  return res;
}