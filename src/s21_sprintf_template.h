typedef long double ldouble;

#define DECLARE_FTOSTR_FUNC(n)                                                 \
  static void n##_to_str(var *variables, n num) {                              \
    long long int reallen = 0;                                                 \
    long long int intlen = 0;                                                  \
    long long int pointpos = 0;                                                \
    long long int len = 0;                                                     \
    int minus = 0;                                                             \
    if (num < 0) {                                                             \
      (minus) = 1;                                                             \
      (num) = (num) * (-1);                                                    \
    }                                                                          \
    n fbuf = num;                                                              \
    long long int intpart = num;                                               \
    while (((fbuf - intpart) > 0.0) && ((fbuf - intpart) != 0.0)) {            \
      fbuf = num * ten_degree_impl(++reallen);                                 \
      intpart = fbuf;                                                          \
    }                                                                          \
    for (intlen = (num > 1) ? 0 : 1; num > 1; intlen++) {                      \
      num = num / 10;                                                          \
    }                                                                          \
    pointpos = intlen;                                                         \
    len = intlen + 1 + reallen;                                                \
    variables->Chbuf = calloc(len + 1, sizeof(*variables->Chbuf));             \
    mem_check(variables->Chbuf, variables);                                    \
    if (minus) {                                                               \
      (pointpos)++;                                                            \
      (len)++;                                                                 \
    }                                                                          \
    for (long long int i = len; i >= 0; i--) {                                 \
      if (i == len) {                                                          \
        (variables->Chbuf)[i] = '\0';                                          \
      } else if (i == pointpos) {                                              \
        (variables->Chbuf)[i] = '.';                                           \
      } else if (minus && i == 0) {                                            \
        (variables->Chbuf)[i] = '-';                                           \
      } else {                                                                 \
        (variables->Chbuf)[i] = (intpart % 10) + '0';                          \
        intpart = intpart / 10;                                                \
      }                                                                        \
    }                                                                          \
  }
