#ifndef SRC_S21_SPRINTF_H_
#define SRC_S21_SPRINTF_H_

#include <float.h>
#include <limits.h>
#include <stdarg.h>

#include "s21_sprintf_options.h"

typedef struct variables {
  int errorFlag;
  char *Chbuf;
  char *temp;
  char *tmp_ptr;
} var;

void s21_free_at_exit(var *variables);
void s21_mem_check(char *str, var *variables);

void s21_call_var_arg(char **str, opt options, va_list var_arg, int *n_smb,
                      var *variables);

int s21_int_specifiers(char **str, opt options, va_list var_arg,
                       var *variables);
int s21_e_specifiers(char **str, opt options, long double double_var,
                     var *variables);
int s21_f_specifier(char **str, opt options, long double double_var,
                    var *variables);
int s21_g_specifiers(char **str, opt *options, long double double_var,
                     var *variables);
int s21_p_specifier(char **str, opt options, va_list var_arg, var *variables);
int s21_perc_specifier(char **str, opt options, var *variables);
void s21_n_specifier(opt options, va_list var_arg, long int n_smb);
int s21_c_specifier(char **str, opt options, va_list var_arg, var *variables);
void s21_c_sol_fork(opt options, va_list var_arg, var *variables);
int s21_s_specifier(char **str, opt options, va_list var_arg, var *variables);
void s21_s_sol_fork(opt options, va_list var_arg, var *variables);

#endif  // SRC_S21_SPRINTF_H_
