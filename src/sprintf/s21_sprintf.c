#include "s21_sprintf.h"

#include "../s21_string.h"
#include "s21_sprintf_utils.h"

void s21_free_at_exit(var *variables) {
  if (variables->Chbuf) {
    free(variables->Chbuf);
    variables->Chbuf = s21_NULL;
  }
  if (variables->temp) {
    free(variables->temp);
    variables->temp = s21_NULL;
  }
  if (variables->Chbuf) {
    free(variables->Chbuf);
    variables->temp = s21_NULL;
  }
}

void s21_mem_check(char *str, var *variables) {
  if (str == s21_NULL) {
    variables->errorFlag = 1;
    s21_free_at_exit(variables);
    exit(1);
  }
}

int s21_sprintf(char *str, const char *format, ...) {
  int n_smb = 0;
  opt options;
  va_list var_arg;
  var variables = {0};
  va_start(var_arg, format);
  while (*format) {
    if (*format != '%') {
      *str++ = *format++;
      n_smb += 1;
    } else {
      s21_init_options(&options);
      s21_get_options(&format, &options, var_arg);
      s21_call_var_arg(&str, options, var_arg, &n_smb, &variables);
    }
  }
  va_end(var_arg);
  *str = '\0';
  return n_smb;
}

void s21_call_var_arg(char **str, opt options, va_list var_arg, int *n_smb,
                      var *variables) {
  if (options.format_spec == C) {
    *n_smb += s21_c_specifier(str, options, var_arg, variables);
  } else if (options.format_spec == S) {
    *n_smb += s21_s_specifier(str, options, var_arg, variables);
  } else if (s21_is_spec_int(options.format_spec)) {
    *n_smb += s21_int_specifiers(str, options, var_arg, variables);
  } else if (s21_is_spec_float(options.format_spec)) {
    long double double_var = 0L;
    double_var = s21_get_double_variable(options, var_arg);
    if (options.format_spec == F) {
      *n_smb += s21_f_specifier(str, options, double_var, variables);
    } else if (options.format_spec == ELOW || options.format_spec == EUP) {
      *n_smb += s21_e_specifiers(str, options, double_var, variables);
    } else {
      *n_smb += s21_g_specifiers(str, &options, double_var, variables);
    }
  } else if (options.format_spec == PERC) {
    *n_smb += s21_perc_specifier(str, options, variables);
  } else if (options.format_spec == N) {
    s21_n_specifier(options, var_arg, *n_smb);
  } else {
    **str = '\0';
  }
}

int s21_int_specifiers(char **str, opt options, va_list var_arg,
                       var *variables) {
  long unsigned u_var = 0;
  int len = 0, is_negative = 0, notation = 10;
  char *buf = s21_NULL;
  char sign = '\0';
  u_var = s21_get_unsigned_variable(options, var_arg, &is_negative);
  if (options.format_spec == O) {
    notation = 8;
  } else if (options.format_spec == XLOW || options.format_spec == XUP ||
             options.format_spec == P) {
    notation = 16;
  }
  s21_get_char_sign(is_negative, &sign, options);
  buf = s21_unsigned_to_str(u_var, notation, options.format_spec == XUP);
  if (options.precision != -1) {
    s21_apply_num_precision(&buf, options.precision);
  } else if (options.flags.ZERO && !options.flags.MINUS &&
             options.min_width > 0) {
    s21_apply_num_precision(&buf, options.min_width - (sign != '\0'));
  }
  if (u_var != 0 || options.format_spec == P ||
      (u_var == 0 && options.format_spec == O && options.precision == 0)) {
    s21_add_notation(&buf, options);
  }
  s21_add_sign(&buf, sign);
  if (options.flags.MINUS || !options.flags.ZERO) {
    s21_apply_width(&buf, options, variables);
  }
  if (buf) {
    variables->Chbuf = buf;
    len = s21_recording(str, variables);
  }
  return len;
}

int s21_e_specifiers(char **str, opt options, long double double_var,
                     var *variables) {
  int is_negative = 1, len = 0;
  char *buf = s21_NULL, sign = '\0';
  is_negative = (double_var < 0) ? -1 : 1;
  s21_get_char_sign(is_negative, &sign, options);
  double_var = double_var * is_negative;
  if ((double_var <= LDBL_MAX && options.len_spec == LUP) ||
      (double_var <= DBL_MAX && options.len_spec != LUP)) {
    unsigned u_exponent = 0;
    long double mantissa = 0.;
    int next_digit = 0;
    char *mant_buf = s21_NULL, *exp_buf = s21_NULL, exp_sign = '\0',
         e_char = '\0';
    e_char =
        (options.format_spec == EUP || options.format_spec == GUP) ? 'E' : 'e';
    mantissa = double_var;
    exp_sign = (mantissa < 1. && mantissa >= LDBL_TRUE_MIN) ? '-' : '+';
    u_exponent = s21_get_exponent(&mantissa);
    mant_buf = s21_mantissa_to_str(mantissa, &next_digit, options);
    s21_math_rounding(&mant_buf, next_digit, &exp_sign, &u_exponent);
    s21_delete_trailing_zeros(&mant_buf, options);
    exp_buf = s21_unsigned_to_str(u_exponent, 10, 0);
    s21_apply_num_precision(&exp_buf, 2);
    s21_add_sign(&exp_buf, exp_sign);
    s21_add_sign(&exp_buf, e_char);
    buf = s21_sum_and_free_strings(mant_buf, exp_buf);
    if (options.flags.ZERO && !options.flags.MINUS && options.min_width > 0) {
      s21_apply_num_precision(&buf, options.min_width - (sign != '\0'));
    }
  } else {
    buf = s21_nan_inf(double_var, &sign, options.format_spec);
  }
  s21_add_sign(&buf, sign);
  if (options.flags.MINUS || !options.flags.ZERO) {
    s21_apply_width(&buf, options, variables);
  }
  if (buf) {
    variables->Chbuf = buf;
    len = s21_recording(str, variables);
  }
  return len;
}

int s21_f_specifier(char **str, opt options, long double double_var,
                    var *variables) {
  int is_negative = 1, len = 0;
  long double tens = 0.;  // tens - старшие разряды числа (десятки и выше),
  long double ones = 0.;  // ones - младшие (единицы и ниже)
  char *ones_buf = s21_NULL, *tens_buf = s21_NULL, *buf = s21_NULL;
  char sign = '\0';
  is_negative = (double_var < 0) ? -1 : 1;
  s21_get_char_sign(is_negative, &sign, options);
  double_var = double_var * is_negative;
  if (double_var <= LDBL_MAX) {
    int next_digit = 0;
    s21_split_float(double_var, &ones, &tens);
    tens_buf = s21_float_to_str(tens);
    ones_buf = s21_mantissa_to_str(ones, &next_digit, options);
    buf = s21_sum_and_free_strings(tens_buf, ones_buf);
    s21_math_rounding(&buf, next_digit, s21_NULL, s21_NULL);
    s21_delete_trailing_zeros(&buf, options);
    if (options.flags.ZERO && !options.flags.MINUS && options.min_width > 0) {
      s21_apply_num_precision(&buf, options.min_width - (sign != '\0'));
    }
  } else {
    buf = s21_nan_inf(double_var, &sign, options.format_spec);
  }
  s21_add_sign(&buf, sign);
  if (options.flags.MINUS || !options.flags.ZERO) {
    s21_apply_width(&buf, options, variables);
  }
  if (buf) {
    variables->Chbuf = buf;
    len = s21_recording(str, variables);
  }
  return len;
}

int s21_g_specifiers(char **str, opt *options, long double double_var,
                     var *variables) {
  int len = 0, exp_check = 0;
  long double double_var_temp = 0;

  double_var_temp = (double_var >= 0) ? double_var : -double_var;
  exp_check = s21_get_exponent(&double_var_temp);
  double_var_temp = fabsl(double_var);
  exp_check *=
      (double_var_temp < 1. && double_var_temp >= LDBL_TRUE_MIN) ? -1 : 1;

  if (options->precision < 0) {
    options->precision = 6;
  } else if (options->precision == 0) {
    options->precision = 1;
  }
  if ((-4 <= exp_check) && (exp_check < options->precision)) {
    options->precision = options->precision - 1 - exp_check;
    len = s21_f_specifier(str, *options, double_var, variables);
  } else {
    options->precision = options->precision - 1;
    len = s21_e_specifiers(str, *options, double_var, variables);
  }
  return len;
}

int s21_perc_specifier(char **str, opt options, var *variables) {
  char *buf = s21_NULL;
  int len = 0;
  buf = (char *)malloc(sizeof(char) * 3);
  if (buf) {
    buf[0] = '\0';
    s21_strcat(buf, "%");
    if (options.flags.ZERO && !options.flags.MINUS && options.min_width > 0) {
      s21_apply_num_precision(&buf, options.min_width);
    }
    if (options.flags.MINUS || !options.flags.ZERO) {
      s21_apply_width(&buf, options, variables);
    }
    if (buf) {
      variables->Chbuf = buf;
      len = s21_recording(str, variables);
    }
  }
  return len;
}

void s21_n_specifier(opt options, va_list var_arg, long int n_smb) {
  if (options.len_spec == H) {
    short int *variable = s21_NULL;
    variable = va_arg(var_arg, short int *);
    *variable = n_smb;
  } else if (options.len_spec == LLOW) {
    long int *variable = s21_NULL;
    variable = va_arg(var_arg, long int *);
    *variable = n_smb;
  } else {
    int *variable = s21_NULL;
    variable = va_arg(var_arg, int *);
    *variable = n_smb;
  }
}

int s21_c_specifier(char **str, opt options, va_list var_arg, var *variables) {
  variables->Chbuf = calloc(2, sizeof(*variables->Chbuf));
  s21_mem_check(variables->Chbuf, variables);
  s21_c_sol_fork(options, var_arg, variables);
  s21_apply_width(&(variables->Chbuf), options, variables);
  return (s21_recording(str, variables));
}

void s21_c_sol_fork(opt options, va_list var_arg, var *variables) {
  if (options.len_spec == LLOW) {
    wchar_t wchar = va_arg(var_arg, wchar_t);
    wchar_t wstr[2] = {0};
    wstr[0] = wchar;
    s21_WchInStr(variables->Chbuf, wstr, 1);
  } else {
    char sym = (char)va_arg(var_arg, int);
    (variables->Chbuf)[0] = sym;
    (variables->Chbuf)[1] = '\0';
  }
}

int s21_s_specifier(char **str, opt options, va_list var_arg, var *variables) {
  s21_s_sol_fork(options, var_arg, variables);
  s21_apply_width(&(variables->Chbuf), options, variables);
  return (s21_recording(str, variables));
}

void s21_s_sol_fork(opt options, va_list var_arg, var *variables) {
  if (options.len_spec == LLOW) {
    int wlen = 0;
    wchar_t *wstr = s21_NULL;
    wstr = va_arg(var_arg, wchar_t *);
    wlen = s21_wstrlen(wstr);
    s21_precision_CS(&wlen, options);
    variables->Chbuf = calloc(wlen + 1, sizeof(*variables->Chbuf));
    s21_mem_check(variables->Chbuf, variables);
    s21_WchInStr(variables->Chbuf, wstr, wlen);
  } else {
    int len = 0;
    char *Usstr = s21_NULL;
    Usstr = va_arg(var_arg, char *);
    len = s21_strlen(Usstr);
    s21_precision_CS(&len, options);
    variables->Chbuf = calloc(len + 1, sizeof(*variables->Chbuf));
    s21_mem_check(variables->Chbuf, variables);
    for (int i = 0; i < len; i++) {
      (variables->Chbuf)[i] = Usstr[i];
    }
  }
}
