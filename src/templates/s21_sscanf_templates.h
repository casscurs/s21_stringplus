#ifndef SRC_S21_SSCANF_TEMPLATES_H_
#define SRC_S21_SSCANF_TEMPLATES_H_

#define DECLARE_NO_FLOAT_FUNC(type, c, signed_or_not, ll_u_or_not)             \
  bool s21_strtoi_##c(const char **str, specifier *flag, va_list *input,       \
                      int base, bool *work_func) {                             \
    char num_sys[] = "0123456789ABCDEFabcdef";                                 \
    int res = 0;                                                               \
    bool overload = false;                                                     \
    ll_u_or_not next_num = 0, num = 0;                                         \
                                                                               \
    int sign = s21_get_sign(&flag->widht, str);                                \
    const char *p_str = *str;                                                  \
                                                                               \
    if (base == 0) base = s21_get_base(*str);                                  \
    if (base == 10) num_sys[10] = '\0';                                        \
    if (base == 8) num_sys[8] = '\0';                                          \
                                                                               \
    if (base == 16 && *p_str == '0' &&                                         \
        (*(p_str + 1) == 'x' || *(p_str + 1) == 'X')) {                        \
      p_str += 2;                                                              \
      res = 1;                                                                 \
    }                                                                          \
    while (s21_strchr(num_sys, *p_str) != s21_NULL && flag->widht && *p_str) { \
      num = next_num;                                                          \
      next_num = num * base + s21_ctoi(*p_str);                                \
      if (next_num < num)                                                      \
        overload = true;                                                       \
      else                                                                     \
        num = next_num;                                                        \
      p_str++;                                                                 \
      flag->widht--;                                                           \
      res = 1;                                                                 \
    }                                                                          \
    if (res == 0) *work_func = false;                                          \
    *str = p_str;                                                              \
    if (overload) {                                                            \
      if (sign && signed_or_not) {                                             \
        num = LLONG_MIN;                                                       \
      } else {                                                                 \
        if (!signed_or_not) {                                                  \
          num = ULLONG_MAX;                                                    \
        } else {                                                               \
          num = LLONG_MAX;                                                     \
        }                                                                      \
      }                                                                        \
    } else if (res) {                                                          \
      if (sign) num = -num;                                                    \
    }                                                                          \
    if (flag->no_assign == 0 && res) {                                         \
      type *var = va_arg(*input, type *);                                      \
      *var = num;                                                              \
    } else {                                                                   \
      res = 0;                                                                 \
    }                                                                          \
    return res;                                                                \
  }

#define DECLARE_FLOAT_FUNC(type, c)                                    \
  bool s21_strto##c(const char **str, specifier *flag, va_list *input, \
                    bool *work_func) {                                 \
    long double res_float = 0;                                         \
    int res = 0;                                                       \
    long double f_pow = 0.1;                                           \
                                                                       \
    int exp_pow = 0;                                                   \
    int exp_res = 0;                                                   \
                                                                       \
    int sign = s21_get_sign(&flag->widht, str);                        \
    const char *p_str = *str;                                          \
                                                                       \
    if (s21_checkinf(flag->widht, str)) {                              \
      res_float = 1.0 / 0.0;                                           \
      p_str += 3;                                                      \
      res = 1;                                                         \
    } else if (s21_checknan(flag->widht, str)) {                       \
      res_float = 0.0 / 0.0;                                           \
      p_str += 3;                                                      \
      res = 1;                                                         \
    } else {                                                           \
      if (is_digit(*p_str) && *p_str) {                                \
        res = 1;                                                       \
        while (is_digit(*p_str) && *p_str && flag->widht) {            \
          res_float = res_float * 10 + s21_ctoi(*p_str);               \
          p_str++;                                                     \
          flag->widht--;                                               \
        }                                                              \
      }                                                                \
                                                                       \
      if (*p_str == '.' && *work_func && flag->widht) {                \
        p_str++;                                                       \
        if (is_digit(*p_str) && *p_str && flag->widht) {               \
          flag->widht--;                                               \
          res = 1;                                                     \
          while (is_digit(*p_str) && *p_str && flag->widht) {          \
            res_float += f_pow * s21_ctoi(*p_str);                     \
            f_pow /= 10;                                               \
            p_str++;                                                   \
            flag->widht--;                                             \
          }                                                            \
        } else if (p_str - *str == 1)                                  \
          *work_func = false;                                          \
      }                                                                \
      if ((*p_str == 'e' || *p_str == 'E') && *work_func) {            \
        res = 1;                                                       \
        p_str++;                                                       \
        flag->widht--;                                                 \
        int exp_neg = s21_get_sign(&flag->widht, &p_str);              \
        bool overload = false;                                         \
        if (is_digit(*p_str)) {                                        \
          while (is_digit(*p_str) && flag->widht && *p_str) {          \
            int next = exp_pow;                                        \
            next = exp_pow * 10 + s21_ctoi(*p_str);                    \
            if (next < exp_pow) {                                      \
              exp_pow = -1;                                            \
              overload = true;                                         \
            } else {                                                   \
              exp_pow = next;                                          \
              p_str++;                                                 \
              flag->widht--;                                           \
              exp_res = 1;                                             \
            }                                                          \
          }                                                            \
        }                                                              \
        if (exp_res == 1 && !overload)                                 \
          res_float *= pow(10, exp_neg ? -exp_pow : exp_pow);          \
      }                                                                \
    }                                                                  \
    if (flag->no_assign) res = 0;                                      \
                                                                       \
    *str = p_str;                                                      \
    if (sign) res_float = -res_float;                                  \
    if (flag->no_assign == 0 && res) {                                 \
      type *var = va_arg(*input, type *);                              \
      *var = res_float;                                                \
    }                                                                  \
    return res;                                                        \
  }

#endif