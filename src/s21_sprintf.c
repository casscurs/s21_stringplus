/*УБРАТЬ fsanitize из Make*/
/*если нет следующего аргумента или если type несовместим с типом следующего
аргумента, то могут возникнуть различные ошибки.
- обработка va_arg с точки зрения ошибок*/
/*при выноске buf в структуру выставить memset на его обнуление, либо calloc*/
// занулить переменные
//тесты на веественные числа
#include "s21_sprintf.h"
#include <float.h>
#include <locale.h>
#include <math.h>
#include <wchar.h>

// %|flags|(min field width)|.|precision(max field width)|length
// description|specifier
// Порядок обработки: Спецификатор -> Длина -> Точность -> Ширина -> Флаги
// Параметр last является именем последнего параметра, тип которого известен
// вызывающей функции.

void call_var_arg(char **str, opt options, va_list var_arg, int *n_smb,
                  var *variables);
int S_specifier(char **str, opt options, va_list var_arg, var *variables);
void apply_width(char **buf, opt options, var *variables);
void S_sol_fork(opt options, va_list var_arg, var *variables);
int F_specifier(char **str, opt options, va_list var_arg, var *variables);
int recording(char **str, var *variables);
long long int ten_degree_impl(long long int degree);
void precision_CS(int *wlen, opt options);
 long double double_round( long double value, int decimal);
void LDBLtostr(var *variables, long double num, int prec);
void f_solution(var *variables, long double Lfnum, int prec);

// DECLARE_FTOSTR_FUNC(float)
// DECLARE_FTOSTR_FUNC(double)
// DECLARE_FTOSTR_FUNC(ldouble)
void add_sign(char **buf, char sign,var* variables ) {
  if (sign && *buf) {
    int len_buf = 0;
    char *temp = NULL;
    len_buf = strlen(*buf);
    temp = (char *)malloc(sizeof(char) * (len_buf + 2));
    mem_check(temp, variables);
    if (temp) {
      char *tmp_ptr = NULL;
      temp[0] = sign;
      temp[1] = '\0';
      strcat(temp, *buf);
      tmp_ptr = (char *)realloc(*buf, sizeof(char) * (len_buf + 2));
      mem_check(tmp_ptr, variables);
      if (tmp_ptr) {
        *buf = tmp_ptr;
        strcpy(*buf, temp);
      }
      free(temp);
    }
  }
}

long long int ten_degree_impl(long long int degree) {
  long long int res = 1;
  while (degree-- > 0) {
    res = res * 10;
  }
  return res;
}

void free_at_exit(var *variables) {
  if (variables->Chbuf) {
    free(variables->Chbuf);
    variables->Chbuf = NULL;
  }
  if (variables->temp) {
    free(variables->temp);
    variables->temp = NULL;
  }
  if (variables->Chbuf) {
    free(variables->Chbuf);
    variables->temp = NULL;
  }
}
void mem_check(char *str, var *variables) {
  if (str == NULL) {
    // fprintf(stderr, "memory error\n");
    variables->errorFlag = 1;
    free_at_exit(variables);
    exit(1);
  }
}

int main(void) {
  char ex1[6000] = {0};
  char ex2[6000] = {0};
  char ex_templ[] = "%Lf";
  long double fnum = -99.009090999;
  //long double fnum=LDBL_MAX;
  //long double fnum=-.0;
  //long double fnum=99.99;
  // printf("%s number given %Lf\n", ex_templ, fnum);
  s21_sprintf(ex1, ex_templ, fnum);
  sprintf(ex2, ex_templ, fnum);
  printf("m:%s\n", ex1);
  printf("o:%s\n", ex2);
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
      init_options(&options);
      get_options(&format, &options, var_arg);
      call_var_arg(&str, options, var_arg, &n_smb, &variables);
    }
  }
  va_end(var_arg);
  *str = '\0';
  return n_smb;
}
void call_var_arg(char **str, opt options, va_list var_arg, int *n_smb,
                  var *variables) {
  switch (options.format_spec) {
  case C:
    *n_smb += C_specifier(str, options, var_arg, variables);
    break;
  case S:
    *n_smb += S_specifier(str, options, var_arg, variables);
    break;
  case F:
    *n_smb += F_specifier(str, options, var_arg, variables);
    break;
  default:
    **str = '\0';
    break;
  }
}

int F_specifier(char **str, opt options, va_list var_arg, var *variables) {
  int prec = 0;
  prec = options.precision;
  if (prec == -1) {
    prec = 6;
  }
  if (options.len_spec == LUP) {
    long double Lfnum = va_arg(var_arg, long double);
    LDBLtostr(variables, Lfnum, prec);
  } else {
    double fnum = va_arg(var_arg, double);
    LDBLtostr(variables, fnum, prec);
  }
  if (options.flags.SPACE){
   add_sign(&variables->Chbuf,' ',variables );
  }
  apply_width(&(variables->Chbuf), options, variables);
  return (recording(str, variables));
}



 long double double_round(long double value, int decimal) {
   long double rounded;
   long double shift = pow(10, decimal);
   rounded = value * shift;
  rounded = roundl(rounded);
  return (rounded);
}

void LDBLtostr(var *variables, long double num, int prec){
int pointpos = 0;
int len = 0;
long double intpart = 0;
long double fpart = 0;
int minus = 0;
if (num < 0) {
  minus = 1;
  num *= -1;
}
long double fbuf=num;
for (pointpos = (fbuf > 1) ? 0 : 1; fbuf >= 1; pointpos++) {
  fbuf = fbuf / 10;
}
  if (num * pow(10, prec) >= __LDBL_MAX__) {
    fpart = modfl(num, &intpart);
  } else {
    fpart = modfl(double_round(num, prec), &intpart);
  }
if (minus) {
  pointpos++;
}
len = pointpos + prec+1;
variables->Chbuf = calloc(len + 2, sizeof(*variables->Chbuf));
mem_check(variables->Chbuf, variables);
for (int i = len; i >= 0; i--) {
    if (i == len) {
      (variables->Chbuf)[i] = '\0';
    } else if (i == pointpos) {
      (variables->Chbuf)[i] = '.';
    } else if (minus && i == 0) {
      (variables->Chbuf)[i] = '-';
    } else {
      int buf = 0;
      buf = fmodl(intpart, 10);
      (variables->Chbuf)[i] = buf + '0';
      intpart /= 10;
    }
}
}

void WchInStr(char *str, wchar_t *wstr, int len) {
  int buflen = strlen(str);
  char *p = str + buflen;
  for (int i = 0; i < len; i++) {
    *(p++) = (char)*(wstr++);
  }
  *p = '\0';
}
int C_specifier(char **str, opt options, va_list var_arg, var *variables) {
  variables->Chbuf = calloc(2, sizeof(*variables->Chbuf));
  mem_check(variables->Chbuf, variables);
  C_sol_fork(options, var_arg, variables);
  apply_width(&(variables->Chbuf), options, variables);
  return (recording(str, variables));
}
void C_sol_fork(opt options, va_list var_arg, var *variables) {
  if (options.len_spec == LLOW) {
    wchar_t wchar = va_arg(var_arg, wchar_t);
    wchar_t wstr[2] = {0};
    wstr[0] = wchar;
    WchInStr(variables->Chbuf, wstr, 1);
  } else {
    char sym = (char)va_arg(var_arg, int);
    (variables->Chbuf)[0] = sym;
    (variables->Chbuf)[1] = '\0';
  }
}
int wstrlen(wchar_t *wstr) {
  wchar_t *p = NULL;
  p = wstr;
  for (; *p; p++)
    ;
  return p - wstr;
}
void apply_width(char **buf, opt options, var *variables) {
  int len_buf = strlen(*buf);
  if (len_buf < options.min_width) {
    int n_fillers = options.min_width - len_buf;
    char filler = ' ';
    if (!options.flags.MINUS && options.flags.ZERO) {
      filler = '0';
    }
    variables->temp = calloc((options.min_width + 2), sizeof(char));
    mem_check(variables->temp, variables);
    for (int i = 0; i < n_fillers; i++) {
      (variables->temp)[i] = filler;
    }
    (variables->temp)[n_fillers] = '\0';

    variables->tmp_ptr =
        (char *)realloc(*buf, sizeof(char) * (options.min_width + 2));
    mem_check(variables->tmp_ptr, variables);
    if (variables->tmp_ptr) {
      *buf = variables->tmp_ptr;
      if (options.flags.MINUS) {
        strcat(*buf, variables->temp);
      } else {
        strcat(variables->temp, *buf);
        strcpy(*buf, variables->temp);
      }
    }
    free(variables->temp);
    variables->temp = NULL;
  }
}
int S_specifier(char **str, opt options, va_list var_arg, var *variables) {
  S_sol_fork(options, var_arg, variables);
  apply_width(&(variables->Chbuf), options, variables);
  return (recording(str, variables));
}

void precision_CS(int *wlen, opt options) {
  if (((*wlen) > options.precision) && (options.precision > 0)) {
    (*wlen) = options.precision;
  } else if (options.precision == 0) {
    *wlen = 0;
  }
}

void S_sol_fork(opt options, va_list var_arg, var *variables) {
  if (options.len_spec == LLOW) {
    int wlen = 0;
    wchar_t *wstr = NULL;
    wstr = va_arg(var_arg, wchar_t *);
    wlen = wstrlen(wstr);

    precision_CS(&wlen, options);

    variables->Chbuf = calloc(wlen + 1, sizeof(*variables->Chbuf));
    mem_check(variables->Chbuf, variables);
    WchInStr(variables->Chbuf, wstr, wlen);
  } else {
    int len = 0;
    char *Usstr = NULL;
    Usstr = va_arg(var_arg, char *);
    len = strlen(Usstr);
    precision_CS(&len, options);
    variables->Chbuf = calloc(len + 1, sizeof(*variables->Chbuf));
    mem_check(variables->Chbuf, variables);
    for (int i = 0; i < len; i++) {
      (variables->Chbuf)[i] = Usstr[i];
    }
  }
}
int recording(char **str, var *variables) {
  int length = 0;
  strcpy(*str, variables->Chbuf);
  length = strlen(variables->Chbuf);
  *str = *str + length;
  free(variables->Chbuf);
  variables->Chbuf = NULL;
  return (length);
}