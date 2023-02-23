#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long unsigned s21_size_t;
#define s21_NULL (void *)0
#define s21_void

// calculation functions Cupcakep
s21_size_t s21_strlen(const char *str);
s21_size_t s21_strspn(const char *str1, const char *str2);
s21_size_t s21_strcspn(const char *str1, const char *str2);

// C# functions Cupcakep
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
int find(int in, char *trim);
void *s21_trim(const char *src, const char *trim_chars);

// comparison functions Takakoka
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);

// search functions Takakoka
char *s21_strchr(const char *str, int c);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
void *s21_memchr(const void *str, int c, s21_size_t n);

// copy functions Jesicahi
/* Copy N bytes of SRC to DEST.  */
void *s21_memcpy(void *restrict dest, const void *restrict src, s21_size_t n);

/* Copy N bytes of SRC to DEST, guaranteeing
   correct behavior for overlapping strings.  */
void *s21_memmove(void *dest, const void *src, size_t n);

/* Set N bytes of S to C.  */
void *s21_memset(void *str, int c, s21_size_t n);

/* Copy SRC to DEST.  */
char *s21_strcpy(char *restrict dest, const char *restrict src);

/* Copy no more than N characters of SRC to DEST.  */
char *s21_strncpy(char *restrict dest, const char *restrict src, s21_size_t n);

// help functions Jesicahi
/**
 * Devided SRC into tokens separated in characters in DELIM.
 */
char *s21_strtok(char *restrict str, const char *restrict delim);

/**
 * Retrun a string describe the meaning of thr "errno" code in ERRNUM
 */
char *s21_strerror(int errnum);

/**
 * Append SRC onto DEST.
 */
char *s21_strcat(char *restrict dest, const char *restrict src);

/**
 * Append no more than N characters from SRC onto DEST
 */
char *s21_strncat(char *restrict dest, const char *restrict src, s21_size_t n);

int s21_sprintf(char *str, const char *format, ...);

#endif  //  SRC_S21_STRINGS_H_