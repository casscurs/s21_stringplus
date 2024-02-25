#include "s21_sscanf.h"

#include "s21_string.h"
#include "templates/s21_sscanf_templates.h"

DECLARE_NO_FLOAT_FUNC(uinteger, ui, 0, uloloint)
DECLARE_NO_FLOAT_FUNC(ushint, us, 0, uloloint)
DECLARE_NO_FLOAT_FUNC(uloint, ul, 0, uloloint)
DECLARE_NO_FLOAT_FUNC(uloloint, ull, 0, uloloint)
DECLARE_NO_FLOAT_FUNC(integer, i, 1, loloint)
DECLARE_NO_FLOAT_FUNC(shint, s, 1, loloint)
DECLARE_NO_FLOAT_FUNC(loint, l, 1, loloint)
DECLARE_NO_FLOAT_FUNC(loloint, ll, 1, loloint)

DECLARE_FLOAT_FUNC(float, f)
DECLARE_FLOAT_FUNC(double, d)
DECLARE_FLOAT_FUNC(ldouble, ld)

int s21_sscanf(const char *str, const char *format, ...) {
  const char *start = str;
  int count_success = 0;
  va_list(input);
  va_start(input, format);
  bool work_func = true;
  /* Начало считывания элементов. Элементы считываются посимвольно*/
  while (*format && work_func) {
    // если символы не пробелы, не % И РАВНЫ, то прибавляй
    if (*format == *str && s21_strchr(SPACE_SYM, *format) == s21_NULL &&
        *format != '%') {
      format++;
      str++;
      continue;
    }
    /* если встретил пробелы, то съешь все */
    else if (s21_strchr(SPACE_SYM, *format) != s21_NULL) {
      s21_delete_spaces(&format);
      s21_delete_spaces(&str);
      continue;
    }
    /* реализация */
    else if (*format == '%') {
      specifier spec;
      // считываем спецификатор
      format = s21_reading_the_specifier(++format, &spec, &work_func);
      // если в считывании произошла ошибка, то выходи из while
      if (!work_func) {
        continue;
      }
      // При флаге 'c' обычный  пропуск символов  пустых  промежутков  в этом
      // случае подавляется
      if (spec.spec != 'c' || (spec.spec == 'c' && spec.widht > 0)) {
        s21_delete_spaces(&str);
      }
      // Обработка конца строки EOF (вывод -1)
      if (!*str && count_success == 0) {
        count_success = -!count_success;
      } else {
        if (*str) {
          count_success += s21_process_and_assign_str_val(start, &str, &spec,
                                                          &input, &work_func);
        }
      }
    }
    /* если мы не зашли выше, то у нас ошибка */
    else {
      work_func = false;
    }
  }
  /* закрываем лист переменных */
  va_end(input);
  /* возвращаем кол-во успешных присваиваний */
  return count_success;
}

// void print_spec(specifier *sp) {
//   printf("Specifier at %p:\n", sp);
//   printf("\tType: %c\n", sp->spec);
//   printf("\tNo Assignment: %s\n", sp->no_assign ? "True" : "False");
//   printf("\tWidth: %d\n", sp->widht);
//   printf("\tLength: %c\n", sp->length);
// }

void s21_delete_spaces(const char **string) {
  /**
   * Skips all spaces in the string
   *
   * @param string adress of the line in which we iterate
   *
   * @return line address
   */
  // p_str -> adress; *p_str -> char;
  const char *p_str = *string;
  while (s21_strchr(SPACE_SYM, *p_str) != s21_NULL && *p_str != '\0') p_str++;
  // присваиваем изменившейся адрес переменной строки
  *string = p_str;
}

char is_digit(char c) { return c >= '0' && c <= '9'; }

const char *s21_reading_the_specifier(const char *format, specifier *spec,
                                      bool *work_func) {
  /**
   * @brief function parses the specifier and related data by format:
   * %[*][width][{h|l|ll}]type
   *
   * @param format pointer to string with the specifier
   * @param flags struct with specifier data
   * @param work_funk error variable
   *
   * @return address of the string after the specifier
   */
  specifier flag = {0, -1, 0, 0};
  // printf("%c\n", *format);

  if (*format == '*') {
    flag.no_assign = 1;
    format++;
  }
  // Если есть параметр ширины, то выполняй
  if (is_digit(*format)) {
    flag.widht = 0;
    while (is_digit(*format)) {
      flag.widht = flag.widht * 10 + s21_ctoi(*format);
      format++;
    }
  }

  // Если есть параметр длины, то делай
  if (s21_strchr("hLl", *format) != s21_NULL) {
    if (*format == 'l' && *(format + 1) == 'l') {
      flag.length = 'L';
      format += 2;
    } else {
      flag.length = *format;
      format++;
    }
  }

  // Если есть спецификатор, то считай. Если нет, то - ошибка.
  if (s21_strchr("cdieEfgGosuxXpn%%", *format) != s21_NULL) {
    flag.spec = *format;
    format++;
  } else {
    *work_func = false;
  }
  *spec = flag;

  return format;
}

bool s21_process_and_assign_str_val(const char *start, const char **str,
                                    specifier *flag, va_list *input,
                                    bool *work_func) {
  /// @brief the function reads value from STR with flags from FLAG and assigns
  /// a value to addres from INPUT
  /// @param start - pointer of start stting
  /// @param str - pointer to pointer of initial string
  /// @param flag - struct with specifier info
  /// @param input - va_list with pointers to variables
  /// @param work_func - variable to control errors
  /// @return - result of assign to variable: 0 or 1

  bool success = 0;
  switch (flag->spec) {
    case 'c':
      success = s21_read_char(str, flag, input, work_func);
      break;
    case 's':
      success = s21_read_string(str, flag, input);
      break;
    case 'd':
      if (flag->length == 'h')
        success = s21_strtoi_s(str, flag, input, 10, work_func);
      else if (flag->length == 'l')
        success = s21_strtoi_l(str, flag, input, 10, work_func);
      else if (flag->length == 'L')
        success = s21_strtoi_ll(str, flag, input, 10, work_func);
      else
        success = s21_strtoi_i(str, flag, input, 10, work_func);
      break;
    case 'u':
      if (flag->length == 'h')
        success = s21_strtoi_us(str, flag, input, 10, work_func);
      else if (flag->length == 'l')
        success = s21_strtoi_ul(str, flag, input, 10, work_func);
      else if (flag->length == 'L')
        success = s21_strtoi_ull(str, flag, input, 10, work_func);
      else
        success = s21_strtoi_ui(str, flag, input, 10, work_func);
      break;
    case 'i':
      if (flag->length == 'h')
        success = s21_strtoi_s(str, flag, input, 0, work_func);
      else if (flag->length == 'l')
        success = s21_strtoi_l(str, flag, input, 0, work_func);
      else if (flag->length == 'L')
        success = s21_strtoi_ll(str, flag, input, 0, work_func);
      else
        success = s21_strtoi_i(str, flag, input, 0, work_func);
      break;
    case 'o':
      if (flag->length == 'h')
        success = s21_strtoi_us(str, flag, input, 8, work_func);
      else if (flag->length == 'l')
        success = s21_strtoi_ul(str, flag, input, 8, work_func);
      else if (flag->length == 'L')
        success = s21_strtoi_ull(str, flag, input, 8, work_func);
      else
        success = s21_strtoi_ui(str, flag, input, 8, work_func);
      break;
    case 'x':
    case 'X':
      if (flag->length == 'h')
        success = s21_strtoi_us(str, flag, input, 16, work_func);
      else if (flag->length == 'l')
        success = s21_strtoi_ul(str, flag, input, 16, work_func);
      else if (flag->length == 'L')
        success = s21_strtoi_ull(str, flag, input, 16, work_func);
      else
        success = s21_strtoi_ui(str, flag, input, 16, work_func);
      break;
    case 'p':
      success = s21_strtoi_ull(str, flag, input, 16, work_func);
      break;
    case 'e':
    case 'E':
    case 'f':
    case 'g':
    case 'G':
      if (flag->length == 'l')
        success = s21_strtod(str, flag, input, work_func);
      else if (flag->length == 'L')
        success = s21_strtold(str, flag, input, work_func);
      else
        success = s21_strtof(str, flag, input, work_func);
      break;
    case 'n':;
      int *n = va_arg(*input, int *);
      *n = *str - start;
      break;
    case '%':
      (*str)++;
      break;
  }
  return success;
}

bool s21_read_char(const char **str, specifier *flag, va_list *input,
                   bool *work_func) {
  /// @brief func read char from STR and skips widht chars from struct FLAG
  /// @param str - pointer on pointer to string to read
  /// @param flag - struc with spec info
  /// @param input - va_list with variable pointers
  /// @param work_func - var to control errors
  /// @return - status of assign: 1 or 0

  bool result = 0;
  // p_str - adress; *p_str - char;
  const char *p_str = *str;
  /* Если флаг присваивания == 0, то присваиваем */
  if (flag->no_assign == 0) {
    char *var = va_arg(*input, char *);
    *var = *p_str;
    result = 1;
  }
  /* Если длина больше или равна 1, то пропусти widht символов*/
  if (flag->widht >= 1) {
    p_str += flag->widht;
  }
  // Если ширина символа == 0, то это ошибка.
  else if (flag->widht == 0) {
    *work_func = false;
  }
  // Если ни то, ни другое, то подвинь поинтер на 1.
  else {
    p_str++;
  }
  // присваиваем изменившейся адрес переменной строки
  *str = p_str;

  return result;
}

bool s21_read_string(const char **str, specifier *flag, va_list *input) {
  /// @brief read string from STR and assign to var from INPUT
  /// @param str - pointer on pointer to string to read
  /// @param flag - struct with spec info
  /// @param input - va_list with var pointers
  /// @return status of assign: 1 or 0

  // p_str - adress; *p_str - char;
  const char *p_str = *str;
  int res = 0;
  char *var;
  if (flag->no_assign == 0) {
    var = va_arg(*input, char *);
  } else {
    var = s21_NULL;
  }
  // Пока не встретились пробелы, не конец строки, и ширина не равна 0, делай
  while (s21_strchr(SPACE_SYM, *p_str) == s21_NULL && *p_str &&
         flag->widht != 0) {
    if (flag->no_assign == 0) *var = *p_str;
    var++;
    p_str++;
    (flag->widht)--;
  }
  // добавляем символ конца строки
  if (flag->no_assign == 0) *var = '\0';
  // проверяем произошло ли присваивание: Если произошло, то адреса должны
  // быть разными, что даст 1. Если нет, то даст 0;
  if (flag->no_assign == 0) {
    res = p_str != *str;
  }

  // присваиваем изменившейся адрес переменной строки
  *str = p_str;

  return res;
}

bool s21_get_sign(int *widht, const char **str) {
  /// @brief read 1 char from *STR to understand what sign is number
  /// @param widht - reading width
  /// @param str - pointer on pointer to string to read
  /// @return 0 if theree is no sign or sign is + and 1 if sign is -

  const char *p_str = *str;
  int sign = 0;
  if (*widht != 0) {
    if (*p_str == '-' || *p_str == '+') {
      if (*p_str == '-') {
        sign = 1;
      }
      p_str++;
      (*widht)--;
    }
  }
  *str = p_str;
  return sign;
}

int s21_ctoi(char h) {
  /// @brief finds out if there is a char H - number or no
  /// @param h - char from string
  /// @return the number that the ascii character stands for: from 0 to 15

  int res = 0;
  if (h >= 'a' && h <= 'f')
    res = h - 'a' + 10;
  else if (h >= 'A' && h <= 'F')
    res = h - 'A' + 10;
  else if (h >= '0' && h <= '9')
    res = h - '0';
  return res;
}

int s21_get_base(const char *str) {
  /// @brief finds out in which number system you need to count in func
  /// s21_strtoi
  /// @param str - pointer to string to read
  /// @return number system: 8 or 10 or 16

  int base = 10;
  if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')) {
    base = 16;
  } else if (*str == '0') {
    base = 8;
  }
  return base;
}

bool s21_checkinf(int widht, const char **str) {
  /// @brief finds out is there inf in string to read
  /// @param widht - widht of reading line
  /// @param str - pointer on pointer to string to read
  /// @return is there inf: 0 or 1

  const char *p_str = *str;
  int isinf = 0;
  if (widht == -1 || widht >= 3) {
    if ((*p_str == 'I' || *p_str == 'i') &&
        (*(p_str + 1) == 'N' || *(p_str + 1) == 'n') &&
        (*(p_str + 2) == 'F' || *(p_str + 2) == 'f')) {
      isinf = 1;
    }
  }
  return isinf;
}

bool s21_checknan(int widht, const char **str) {
  /// @brief finds out is there nan in string to read
  /// @param widht - widht of reading line
  /// @param str - pointer on pointer to string to read
  /// @return is there nan: 0 or 1

  const char *p_str = *str;
  int isnan = 0;
  if (widht == -1 || widht >= 3) {
    if ((*p_str == 'N' || *p_str == 'n') &&
        (*(p_str + 1) == 'A' || *(p_str + 1) == 'a') &&
        (*(p_str + 2) == 'N' || *(p_str + 2) == 'n')) {
      isnan = 1;
    }
  }
  return isnan;
}