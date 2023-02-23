#include <check.h>
#include <string.h>

#include "s21_string.h"

START_TEST(s21_strlen_test) {
  int n = 6;
  char *str[] = {"kek",         "opafdsa",
                 "AHAHAHHA",    "LESHA I HATE YOU!",
                 "...........", "i love school 21"};
  for (int i = 0; i < n; i++) {
    ck_assert_int_eq(strlen(str[i]), s21_strlen(str[i]));
  }
  char str2[] = "\0";
  char str3[] = "     ";
  ck_assert_int_eq(strlen(str2), s21_strlen(str2));
  ck_assert_int_eq(strlen(str3), s21_strlen(str3));
}
END_TEST

START_TEST(s21_strerror_test) {
  for (int i = -100; i < 250; i++) {
    ck_assert_str_eq(strerror(i), s21_strerror(i));
  }
  char ch = '?';
  ck_assert_str_eq(strerror(ch), s21_strerror(ch));
  ck_assert_str_eq(strerror(-1000), s21_strerror(-1000));
  ck_assert_str_eq(strerror(0), s21_strerror(0));
}
END_TEST

START_TEST(s21_memchr_test) {
  char src[] = "01234567890";
  for (int i = 48; i <= 57; i++) {
    ck_assert_ptr_eq(memchr(src, (char)i, 10), s21_memchr(src, (char)i, 10));
  }

  char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
  for (int i = 97; i <= 122; i++) {
    ck_assert_ptr_eq(memchr(alphabet, (char)i, 25),
                     s21_memchr(alphabet, (char)i, 25));
  }

  char alphabet_upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 65; i <= 90; i++) {
    ck_assert_ptr_eq(memchr(alphabet_upper, (char)i, 25),
                     s21_memchr(alphabet_upper, (char)i, 25));
  }

  char nan[] = "AAAAAAAA";
  ck_assert_ptr_eq(memchr(nan, 'a', 10), s21_memchr(nan, 'a', 10));
  ck_assert_ptr_eq(memchr(nan, 'A', 10), s21_memchr(nan, 'A', 10));
  ck_assert_ptr_eq(memchr(nan, 'B', 10), s21_memchr(nan, 'B', 10));
}
END_TEST

START_TEST(s21_memcpy_test) {
  char dest[100];
  char string[] = "01234567890123456789";
  for (s21_size_t i = 2; i < 20; i++) {
    ck_assert_ptr_eq(memcpy(dest, string, i), s21_memcpy(dest, string, i));
  }
}
END_TEST

START_TEST(s21_strcat_test) {
  char syms[100] = "0123456789";
  char syms_reverse[100] = "9876543210";
  char string[100] = "01234567890123456789";
  char alphabet_upper[100] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char no_syms[100] = "";

  ck_assert_str_eq(strcat(syms, syms_reverse), s21_strcat(syms, syms_reverse));
  ck_assert_str_eq(strcat(string, alphabet_upper),
                   s21_strcat(string, alphabet_upper));
  ck_assert_str_eq(strcat(syms, alphabet_upper),
                   s21_strcat(syms, alphabet_upper));
  ck_assert_str_eq(strcat(no_syms, alphabet_upper),
                   s21_strcat(no_syms, alphabet_upper));
}
END_TEST

START_TEST(s21_strrchr_test) {
  char str[100] = "1234567890";
  for (int i = 48; i <= 57; i++) {
    char *ptr1 = s21_strrchr(str, i);
    char *orig1 = strrchr(str, i);
    ck_assert_str_eq(ptr1, orig1);
  }

  char str1[100] = "abcdefghijklmnopqrstuvwxyz";
  for (int i = 97; i <= 122; i++) {
    char *ptr1 = s21_strrchr(str1, i);
    char *orig1 = strrchr(str1, i);
    ck_assert_str_eq(ptr1, orig1);
  }

  char str2[100] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 65; i <= 90; i++) {
    char *ptr1 = s21_strrchr(str2, i);
    char *orig1 = strrchr(str2, i);
    ck_assert_str_eq(ptr1, orig1);
  }
}
END_TEST

START_TEST(s21_strcmp_test) {
  char str1[100] = "abcdefghijklmnopqrstuvwxyz";
  char str2[100] = "abcdefghijklmnopqrstuvwxyz";
  int my1 = s21_strcmp(str1, str2) > 0 ? 1 : -1;
  int orig1 = strcmp(str1, str2) > 0 ? 1 : -1;
  ck_assert_int_eq(orig1, my1);

  char str3[100] = "abYdefghijklmnopqrstuvwxyz";
  char str4[100] = "abAdefghijklmnopqrstuvwxyz";
  int my2 = s21_strcmp(str3, str4) > 0 ? 1 : -1;
  int orig2 = strcmp(str3, str4) > 0 ? 1 : -1;
  ck_assert_int_eq(orig2, my2);
}
END_TEST

START_TEST(s21_strncmp_test) {
  char str1[] = "abcdefghijklmnopqrstuvwxyz";
  char str2[] = "abcdyfghijklmnopqrstuvwxyz";

  int my1 = s21_strncmp(str1, str2, 3) > 0 ? 1 : -1;
  int orig1 = strncmp(str1, str2, 3) > 0 ? 1 : -1;
  ck_assert_int_eq(orig1, my1);

  int my2 = s21_strncmp(str1, str2, 5) > 0 ? 1 : -1;
  int orig2 = strncmp(str1, str2, 5) > 0 ? 1 : -1;
  ck_assert_int_eq(orig2, my2);

  int my3 = s21_strncmp(str1, str2, 20) > 0 ? 1 : -1;
  int orig3 = strncmp(str1, str2, 20) > 0 ? 1 : -1;
  ck_assert_int_eq(orig3, my3);

  int my4 = s21_strncmp(str1, str2, 10) > 0 ? 1 : -1;
  int orig4 = strncmp(str1, str2, 10) > 0 ? 1 : -1;
  ck_assert_int_eq(orig4, my4);
}
END_TEST

START_TEST(s21_strncat_test) {
  char syms[100] = "0123456789";
  char syms_reverse[100] = "9876543210";
  char string[100] = "01234567890123456789";
  char alphabet_upper[100] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char no_syms[100] = "";

  ck_assert_str_eq(strncat(syms, syms_reverse, 10),
                   s21_strncat(syms, syms_reverse, 10));
  ck_assert_str_eq(strncat(string, alphabet_upper, 1),
                   s21_strncat(string, alphabet_upper, 1));
  ck_assert_str_eq(strncat(syms, alphabet_upper, 5),
                   s21_strncat(syms, alphabet_upper, 5));
  ck_assert_str_eq(strncat(no_syms, alphabet_upper, 3),
                   s21_strncat(no_syms, alphabet_upper, 3));
}
END_TEST

START_TEST(s21_strcpy_test) {
  char str1[50] = "abcdefghijklmnopqrstuvwxyz";
  char str1_cp[50] = {0};
  char str2[50] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char str2_cp[50] = {0};
  char str3[50] = "1234567890";
  char str3_cp[50] = "9876543210";

  ck_assert_str_eq(strcpy(str1_cp, str1), s21_strcpy(str1_cp, str1));
  ck_assert_str_eq(strcpy(str2_cp, str2), s21_strcpy(str2_cp, str2));
  ck_assert_str_eq(strcpy(str3_cp, str3), s21_strcpy(str3_cp, str3));
}
END_TEST

START_TEST(s21_strncpy_test) {
  char str1[100] = "abcdefghijklmnopqrstuvwxyz";
  char str1_cp[25] = {0};
  char str2[100] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char str2_cp[25] = {0};
  char str3[100] = "1234567890";
  char str3_cp[10] = "9876543210";

  ck_assert_str_eq(strncpy(str1_cp, str1, 3), s21_strncpy(str1_cp, str1, 3));
  ck_assert_str_eq(strncpy(str1_cp, str1, 10), s21_strncpy(str1_cp, str1, 10));
  ck_assert_str_eq(strncpy(str2_cp, str2, 5), s21_strncpy(str2_cp, str2, 5));
  ck_assert_str_eq(strncpy(str2_cp, str2, 15), s21_strncpy(str2_cp, str2, 15));
  ck_assert_str_eq(strncpy(str3_cp, str3, 1), s21_strncpy(str3_cp, str3, 1));
  ck_assert_str_eq(strncpy(str3_cp, str3, 10), s21_strncpy(str3_cp, str3, 10));
}
END_TEST

START_TEST(s21_strcspn_test) {
  char str1[] = "0123456789";
  char str1_in[] = "987";

  char str2[] = "abced";
  char str2_in[] = "ecd";

  char str3[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char str3_in[] = "XYZ";
  char str3_not[] = "abc";

  ck_assert_int_eq(strcspn(str1, str1_in), s21_strcspn(str1, str1_in));
  ck_assert_int_eq(strcspn(str2, str2_in), s21_strcspn(str2, str2_in));
  ck_assert_int_eq(strcspn(str3, str3_in), s21_strcspn(str3, str3_in));
  ck_assert_int_eq(strcspn(str3, str3_not), s21_strcspn(str3, str3_not));
}
END_TEST

START_TEST(s21_strpbrk_test) {
  char str1[] = "0123456789";
  char str1_in[] = "987";

  char str2[] = "abced";
  char str2_in[] = "ecd";

  char str3[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char str3_in[] = "XYZ";
  char str3_in2[] = "ZYX";

  ck_assert_str_eq(strpbrk(str1, str1_in), s21_strpbrk(str1, str1_in));
  ck_assert_str_eq(strpbrk(str2, str2_in), s21_strpbrk(str2, str2_in));
  ck_assert_str_eq(strpbrk(str3, str3_in), s21_strpbrk(str3, str3_in));
  ck_assert_str_eq(strpbrk(str3, str3_in2), s21_strpbrk(str3, str3_in2));
}
END_TEST

START_TEST(s21_strstr_test) {
  char str1[] = "0123456789";
  char str1_in[] = "789";

  char str2[] = "abced";
  char str2_in[] = "d";

  char str3[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char str3_in[] = "XYZ";

  char str4[] = "0123456789";
  char str4_in[] = "345";

  ck_assert_str_eq(strstr(str1, str1_in), s21_strstr(str1, str1_in));
  ck_assert_str_eq(strstr(str2, str2_in), s21_strstr(str2, str2_in));
  ck_assert_str_eq(strstr(str3, str3_in), s21_strstr(str3, str3_in));
  ck_assert_str_eq(strstr(str4, str4_in), s21_strstr(str4, str4_in));
}
END_TEST

START_TEST(s21_to_upper_test) {
  char str1[] = "alexey, you are an idiot, ok?";

  char *str1_upper = s21_to_upper(str1);

  if (str1_upper) {
    ck_assert_str_eq("ALEXEY, YOU ARE AN IDIOT, OK?", str1_upper);
  }
  free(str1_upper);
}
END_TEST

START_TEST(s21_to_lower_test) {
  char str1[] = "ALEXEY, YOU ARE AN IDIOT, OK?";

  char *str1_lower = s21_to_lower(str1);

  if (str1_lower) {
    ck_assert_str_eq("alexey, you are an idiot, ok?", str1_lower);
  }
  free(str1_lower);
}
END_TEST

START_TEST(s21_memset_test) {
  char str1[] = "0123456789";

  for (s21_size_t i = 65; i < 90; i++) {
    ck_assert_str_eq(memset(str1, i, s21_strlen(str1)),
                     s21_memset(str1, i, s21_strlen(str1)));
  }

  char str2[] = "abcdefghijklmnopqrstuvwxyzABCABCABC";
  s21_size_t j = 3;
  for (s21_size_t i = 97; i < 122; i++) {
    ck_assert_str_eq(memset(str2, i, j), s21_memset(str2, i, j));
    j++;
  }
}
END_TEST

START_TEST(s21_strspn_test) {
  char str1[] = "0123456789";
  char str1_in[] = "123";

  char str2[] = "abced";
  char str2_in[] = "ed";

  char str3[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char str3_in[] = "XYZ";

  char str4[] = "abcdefghijklmnopqrstuvwxyz";
  char str4_in[] = "abcdefghijklmnopqrstuvwxyz";

  ck_assert_int_eq(strspn(str1, str1_in), s21_strspn(str1, str1_in));
  ck_assert_int_eq(strspn(str2, str2_in), s21_strspn(str2, str2_in));
  ck_assert_int_eq(strspn(str3, str3_in), s21_strspn(str3, str3_in));
  ck_assert_int_eq(strspn(str4, str4_in), s21_strspn(str4, str4_in));
}
END_TEST

START_TEST(s21_strtok_test) {
  char str1[] = "kek@lol@arbidol";
  char str1_delim[] = "@";

  char str2[] = "alexey/dog/snoop";
  char str2_delim[] = "/";

  char str3[] = "i&love&school&21";
  char str3_delim[] = "&";

  char str4[] = "^_^i^_^hate^_^strtok^_^!^_^";
  char str4_delim[] = "^_^";

  char str5[] = ".A...A...A...A.";
  char str5_delim[] = ".";

  char str6[] = "12345";
  char str6_delim[] = "1234";

  char str7[] = "12345";
  char str7_delim[] = "\0";

  char str8[] = "12345";
  char str8_delim[] = "?";

  char str9[] = "a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z";
  char str9_delim[] = ",";
  char *parts = s21_strtok(str9, str9_delim);
  while (parts) {
    ck_assert_str_eq(strtok(str9, str9_delim), s21_strtok(str9, str9_delim));
    parts = s21_strtok(S21_NULL, str9_delim);
  }

  ck_assert_str_eq(strtok(str1, str1_delim), s21_strtok(str1, str1_delim));
  ck_assert_str_eq(strtok(str2, str2_delim), s21_strtok(str2, str2_delim));
  ck_assert_str_eq(strtok(str3, str3_delim), s21_strtok(str3, str3_delim));
  ck_assert_str_eq(strtok(str4, str4_delim), s21_strtok(str4, str4_delim));
  ck_assert_str_eq(strtok(str5, str5_delim), s21_strtok(str5, str5_delim));
  ck_assert_str_eq(strtok(str6, str6_delim), s21_strtok(str6, str6_delim));
  ck_assert_str_eq(strtok(str7, str7_delim), s21_strtok(str7, str7_delim));
  ck_assert_str_eq(strtok(str8, str8_delim), s21_strtok(str8, str8_delim));
}
END_TEST

START_TEST(s21_memcmp_test) {
  char str1[] = "0123456789";
  char str1_cmp[] = "0123456789";

  char str2[] = "abAdefghijklmnopqrstuvwxyz";
  char str2_cmp[] = "abAdefghijklmnopqrstuvwxyz";

  char str3[] = "12345";
  char str3_cmp[] = "54321";

  char str4[] = "ABCDE";
  char str4_cmp[] = "EDCBA";

  int originalTest1 = memcmp(str1, str1_cmp, strlen(str1)) > 0 ? 1 : -1;
  int myTest1 = s21_memcmp(str1, str1_cmp, s21_strlen(str1)) > 0 ? 1 : -1;

  int originalTest2 = memcmp(str2, str2_cmp, strlen(str2)) > 0 ? 1 : -1;
  int myTest2 = s21_memcmp(str2, str2_cmp, s21_strlen(str2)) > 0 ? 1 : -1;

  int originalTest3 = memcmp(str3, str3_cmp, strlen(str3)) > 0 ? 1 : -1;
  int myTest3 = s21_memcmp(str3, str3_cmp, s21_strlen(str3)) > 0 ? 1 : -1;

  int originalTest4 = memcmp(str4, str4_cmp, strlen(str4)) > 0 ? 1 : -1;
  int myTest4 = s21_memcmp(str4, str4_cmp, s21_strlen(str4)) > 0 ? 1 : -1;

  ck_assert_int_eq(originalTest1, myTest1);
  ck_assert_int_eq(originalTest2, myTest2);
  ck_assert_int_eq(originalTest3, myTest3);
  ck_assert_int_eq(originalTest4, myTest4);
}
END_TEST

START_TEST(s21_memmove_test) {
  char str1[] = "0123456789";
  char str1_move[] = "123";

  char str2[] = "kekchikkkkwrtyutretyuiokajd;as";
  char str2_move[] = "pukkkkfdshjk";

  char str4[] = "abcdefghijklm234567890sadsadasdnopqrstuvwxyz";
  char str4_move[] = "abcdefghijklmnopqrs1hkkhkjkhjkhjtuvwxyz";

  char str5[] = "bebro4ka3123232dsdsdsdsds";

  ck_assert_str_eq(memmove(str1, str1_move, strlen(str1)),
                   s21_memmove(str1, str1_move, s21_strlen(str1)));
  ck_assert_str_eq(memmove(str1, str1_move, strlen(str1_move)),
                   s21_memmove(str1, str1_move, s21_strlen(str1_move)));
  ck_assert_str_eq(memmove(str2, str2_move, strlen(str2)),
                   s21_memmove(str2, str2_move, s21_strlen(str2)));
  ck_assert_str_eq(memmove(str2, str2_move, strlen(str2_move)),
                   s21_memmove(str2, str2_move, s21_strlen(str2_move)));
  ck_assert_str_eq(memmove(str2_move, str2, strlen(str2_move)),
                   s21_memmove(str2_move, str2, s21_strlen(str2_move)));
  ck_assert_str_eq(memmove(str2 + 1, str2_move + 2, 7),
                   s21_memmove(str2 + 1, str2_move + 2, 7));
  ck_assert_str_eq(memmove(str4_move, str4, strlen(str4_move)),
                   s21_memmove(str4_move, str4, s21_strlen(str4_move)));
  ck_assert_str_eq(memmove(str5, str5 + 3, strlen(str5)),
                   s21_memmove(str5, str5 + 3, s21_strlen(str5)));
  ck_assert_str_eq(memmove(str5 + 3, str5, 5), s21_memmove(str5 + 3, str5, 5));
}
END_TEST

START_TEST(s21_sprintf_test) {
  char str1[1000];
  char str2[1000];
  char format[] = "This is a simple value %d";
  int val = 69;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_precise_int) {
  char str1[1000];
  char str2[1000];
  char *format = "%.5i";
  int val = 69;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_minus_width_int) {
  char str1[1000];
  char str2[1000];
  char *format = "%-5i";
  int val = 69;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_plus_width_int) {
  char str1[1000];
  char str2[1000];

  char *format = "%+12d";
  int val = 69;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_padding_int) {
  char str1[1000];
  char str2[1000];

  char *format = "%+12d";
  int val = 69;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_flags_long_int) {
  char str1[1000];
  char str2[1000];
  char *format = "%+5.31li";
  long int val = 698518581899;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_flags_short_int) {
  char str1[1000];
  char str2[1000];

  char *format = "%-16.9hi";
  short int val = 6958;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_zero_precision_zero_int) {
  char str1[1000];
  char str2[1000];

  char *format = "%.0d";
  int val = 0;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_space_flag_int) {
  char str1[1000];
  char str2[1000];

  char *format = "% d";
  int val = 0;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_unsigned_val) {
  char str1[1000];
  char str2[1000];
  char *format = "%u";
  unsigned int val = 14140;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_unsigned_val_width) {
  char str1[1000];
  char str2[1000];
  char *format = "%15u";
  unsigned int val = 14140;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_unsigned_val_flags) {
  char str1[1000];
  char str2[1000];

  char *format = "%-16u";
  unsigned int val = 14140;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_unsigned_val_precision) {
  char str1[1000];
  char str2[1000];
  char *format = "%.51u";
  unsigned int val = 14140;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_unsigned_val_many_flags) {
  char str1[1000];
  char str2[1000];
  char *format = "% 5.51u";
  unsigned int val = 14140;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_unsigned_val_short) {
  char str1[1000];
  char str2[1000];

  char *format = "%hu";
  unsigned short int val = 14140;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_unsigned_val_long) {
  char str1[1000];
  char str2[1000];

  char *format = "%lu";
  unsigned long int val = 949149114140;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_unsigned_val_many) {
  char str1[1000];
  char str2[1000];

  char *format = "%lu, %u, %hu, %.5u, %5.u";
  unsigned long int val = 949149114140;
  s21_sprintf(str1, format, val, 14, 1441, 14414, 9681);

  sprintf(str2, format, val, (unsigned)14, (unsigned short)1441,
          (unsigned)14414, (unsigned)9681);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_octal_width) {
  char str1[1000];
  char str2[1000];

  char *format = "%15o";
  int val = 14140;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_octal_flags) {
  char str1[1000];
  char str2[1000];

  char *format = "%-16o";
  int val = 14140;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_octal_precision) {
  char str1[1000];
  char str2[1000];

  char *format = "%.51o";
  int val = 14140;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_octal_many_flags) {
  char str1[1000];
  char str2[1000];

  char *format = "%-5.51o";
  int val = 14140;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_octal_zero) {
  char str1[1000];
  char str2[1000];

  char *format = "%o";
  s21_sprintf(str1, format, 0);
  sprintf(str2, format, 0);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_octal_hash) {
  char str1[1000];
  char str2[1000];
  char *format = "%#o";
  int val = 57175;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_octal_short) {
  char str1[1000];
  char str2[1000];

  char *format = "%hd";
  short int val = 14140;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_octal_long) {
  char str1[1000];
  char str2[1000];

  char *format = "%lo";
  long int val = 949149114140;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_octal_many) {
  char str1[1000];
  char str2[1000];

  char *format = "%lo, %o, %ho, %.5o, %5.o";
  long int val = 949149114140;

  s21_sprintf(str1, format, val, 14, 1441, 14414, 9681);
  sprintf(str2, format, val, (unsigned)14, (unsigned short)1441,
          (unsigned)14414, (unsigned)9681);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_octal) {
  char str1[1000];
  char str2[1000];

  char *format = "%lo";
  long int val = 84518;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_unsigned_zero) {
  char str1[1000];
  char str2[1000];

  char *format = "%u";
  s21_sprintf(str1, format, 0);

  sprintf(str2, format, (unsigned)0);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_hex_width) {
  char str1[1000];
  char str2[1000];

  char *format = "%5x";
  unsigned val = 858158158;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_string) {
  char str1[1000];
  char str2[1000];

  char *format = "%s";
  char *string = "denis classniy";
  s21_sprintf(str1, format, string);
  sprintf(str2, format, string);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_string_precision) {
  char str1[1000];
  char str2[1000];

  char *format = "%.4s";
  char *string = "denis classniy";
  s21_sprintf(str1, format, string);
  sprintf(str2, format, string);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_string__width) {
  char str1[1000];
  char str2[1000];

  char *format = "%25s";
  char *string = "denis classniy";
  s21_sprintf(str1, format, string);
  sprintf(str2, format, string);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_string_minus) {
  char str1[1000];
  char str2[1000];

  char *format = "%-25s";
  char *string = "denis classniy";
  s21_sprintf(str1, format, string);
  sprintf(str2, format, string);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_char) {
  char str1[1000];
  char str2[1000];

  char *format = "%c";
  char sym = '!';
  s21_sprintf(str1, format, sym);
  sprintf(str2, format, sym);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_char_width) {
  char str1[1000];
  char str2[1000];

  char *format = "%5c";
  char sym = '!';
  s21_sprintf(str1, format, sym);
  sprintf(str2, format, sym);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_char_minus) {
  char str1[1000];
  char str2[1000];

  char *format = "%-5c";
  char sym = '!';
  s21_sprintf(str1, format, sym);
  sprintf(str2, format, sym);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_wide_string) {
  char str1[1000];
  char str2[1000];

  char *format = "%ls";
  wchar_t *stringLong = L"i love school 21";
  s21_sprintf(str1, format, stringLong);
  sprintf(str2, format, stringLong);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_wide_string_null) {
  char str1[1000];
  char str2[1000];

  char *format = "%ls";
  wchar_t *stringLong = NULL;
  s21_sprintf(str1, format, stringLong);
  sprintf(str2, format, stringLong);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_wide_char) {
  char str1[1000];
  char str2[1000];

  char *format = "%lc";
  wchar_t longChar = L'!';
  s21_sprintf(str1, format, longChar);
  sprintf(str2, format, longChar);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprint_string_null) {
  char str1[1000];
  char str2[1000];

  char *format = "%s";
  char *string = NULL;
  s21_sprintf(str1, format, string);
  sprintf(str2, format, string);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_float) {
  char str1[1000];
  char str2[1000];

  char *format = "%f";
  double num = 1.9;
  s21_sprintf(str1, format, num);
  sprintf(str2, format, num);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_float_zero) {
  char str1[1000];
  char str2[1000];

  char *format = "%f";
  double zero = 0;
  s21_sprintf(str1, format, zero);
  sprintf(str2, format, zero);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_double_min) {
  char str1[1000];
  char str2[1000];

  char *format = "%lf";
  double num = 1E-12;
  s21_sprintf(str1, format, num);
  sprintf(str2, format, num);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_double) {
  char str1[1000];
  char str2[1000];

  char *format = "%lf";
  double negative = -0.34834493943;
  s21_sprintf(str1, format, negative);
  sprintf(str2, format, negative);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_e_zero) {
  char str1[1000];
  char str2[1000];

  char *format = "%e";
  double zeroE = -1.9;
  s21_sprintf(str1, format, zeroE);
  sprintf(str2, format, zeroE);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_E) {
  char str1[1000];
  char str2[1000];

  char *format = "%E";
  double negativeE = -1.9;
  s21_sprintf(str1, format, negativeE);
  sprintf(str2, format, negativeE);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_E_positive) {
  char str1[1000];
  char str2[1000];

  char *format = "%E";
  double positive = 0.1;
  s21_sprintf(str1, format, positive);
  sprintf(str2, format, positive);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_e_positive) {
  char str1[1000];
  char str2[1000];

  char *format = "%e";
  double positive = -999.3489;
  s21_sprintf(str1, format, positive);
  sprintf(str2, format, positive);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_double_negative) {
  char str1[1000];
  char str2[1000];

  char *format = "%lf";
  double num = -10.934;
  s21_sprintf(str1, format, num);
  sprintf(str2, format, num);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_double_nan) {
  char str1[1000];
  char str2[1000];

  char *format = "%lf";
  double nan = NAN;
  s21_sprintf(str1, format, nan);
  sprintf(str2, format, nan);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_long_double) {
  char str1[1000];
  char str2[1000];

  char *format = "%3.5Lf";
  long double num = 657999999;
  s21_sprintf(str1, format, num);
  sprintf(str2, format, num);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_long_double_zero) {
  char str1[1000];
  char str2[1000];

  char *format = "%3.5Lf";
  long double num = 0;
  s21_sprintf(str1, format, num);
  sprintf(str2, format, num);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_percent) {
  char str1[1000];
  char str2[1000];

  char *format = "%%lf";
  long double num = 0;
  s21_sprintf(str1, format, num);
  sprintf(str2, format, num);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_zero) {
  char str1[1000];
  char str2[1000];

  char *format = "%0Lf";
  long double num = 0;
  s21_sprintf(str1, format, num);
  sprintf(str2, format, num);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_ldouble) {
  char str1[1000];
  char str2[1000];

  char *format = "%Lf\0";
  long double num = 123.55555;
  s21_sprintf(str1, format, num);
  sprintf(str2, format, num);
  ck_assert_str_eq(str1, str2);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, s21_strlen_test);                  // valid
  tcase_add_test(tc1_1, s21_strerror_test);                // valid
  tcase_add_test(tc1_1, s21_memchr_test);                  // valid
  tcase_add_test(tc1_1, s21_memcpy_test);                  // valid
  tcase_add_test(tc1_1, s21_strcat_test);                  // valid
  tcase_add_test(tc1_1, s21_strrchr_test);                 // valid
  tcase_add_test(tc1_1, s21_strcmp_test);                  // valid
  tcase_add_test(tc1_1, s21_strncmp_test);                 // valid
  tcase_add_test(tc1_1, s21_strncat_test);                 // valid
  tcase_add_test(tc1_1, s21_strcpy_test);                  // valid
  tcase_add_test(tc1_1, s21_strncpy_test);                 // valid
  tcase_add_test(tc1_1, s21_strcspn_test);                 // valid
  tcase_add_test(tc1_1, s21_strpbrk_test);                 // valid
  tcase_add_test(tc1_1, s21_strstr_test);                  // valid
  tcase_add_test(tc1_1, s21_to_upper_test);                // valid
  tcase_add_test(tc1_1, s21_to_lower_test);                // valid
  tcase_add_test(tc1_1, s21_memset_test);                  // valid
  tcase_add_test(tc1_1, s21_strspn_test);                  // valid
  tcase_add_test(tc1_1, s21_strtok_test);                  // valid
  tcase_add_test(tc1_1, s21_memcmp_test);                  // valid
  tcase_add_test(tc1_1, s21_memmove_test);                 // valid
  tcase_add_test(tc1_1, s21_sprintf_test);                 // valid
  tcase_add_test(tc1_1, s21_sprintf_precise_int);          // valid
  tcase_add_test(tc1_1, sprintf_minus_width_int);          // valid
  tcase_add_test(tc1_1, sprintf_plus_width_int);           // valid?
  tcase_add_test(tc1_1, sprintf_padding_int);              // valid
  tcase_add_test(tc1_1, sprintf_flags_long_int);           // valid
  tcase_add_test(tc1_1, sprintf_flags_short_int);          // valid
  tcase_add_test(tc1_1, sprintf_zero_precision_zero_int);  // valid
  tcase_add_test(tc1_1, sprintf_space_flag_int);           // valid
  tcase_add_test(tc1_1, sprintf_unsigned_val);             // valid
  tcase_add_test(tc1_1, sprintf_unsigned_val_width);       // valid
  tcase_add_test(tc1_1, sprintf_unsigned_val_flags);       // valid
  tcase_add_test(tc1_1, sprintf_unsigned_val_precision);   // valid
  tcase_add_test(tc1_1, sprintf_unsigned_val_many_flags);  // valid
  tcase_add_test(tc1_1, sprintf_unsigned_val_short);       // valid
  tcase_add_test(tc1_1, sprintf_unsigned_val_long);        // valid
  tcase_add_test(tc1_1, sprintf_unsigned_val_many);        // valid
  tcase_add_test(tc1_1, sprintf_octal_width);              // valid
  tcase_add_test(tc1_1, sprintf_octal_flags);              // valid
  tcase_add_test(tc1_1, sprintf_octal_precision);          // valid
  tcase_add_test(tc1_1, sprintf_octal_many_flags);         // valid
  tcase_add_test(tc1_1, sprintf_octal_zero);               // valid
  tcase_add_test(tc1_1, sprintf_octal_hash);               // valid
  tcase_add_test(tc1_1, sprintf_octal_short);              // valid
  tcase_add_test(tc1_1, sprintf_octal_long);               // valid
  tcase_add_test(tc1_1, sprintf_octal_many);               // valid
  tcase_add_test(tc1_1, sprintf_octal);                    // valid
  tcase_add_test(tc1_1, sprintf_unsigned_zero);            // valid
  tcase_add_test(tc1_1, sprintf_hex_width);                // valid
  tcase_add_test(tc1_1, sprintf_string);                   // valid
  tcase_add_test(tc1_1, sprintf_string_precision);         // valid
  tcase_add_test(tc1_1, sprintf_string__width);            // valid
  tcase_add_test(tc1_1, sprintf_string_minus);             // valid
  tcase_add_test(tc1_1, sprintf_char);                     // valid
  tcase_add_test(tc1_1, sprintf_char_width);               // valid
  tcase_add_test(tc1_1, sprintf_char_minus);               // valid
  tcase_add_test(tc1_1, sprintf_wide_string);              // valid
  tcase_add_test(tc1_1, sprintf_wide_string_null);         // valid
  tcase_add_test(tc1_1, sprintf_wide_char);                // valid
  tcase_add_test(tc1_1, sprint_string_null);               // valid
  tcase_add_test(tc1_1, sprintf_float);                    // valid
  tcase_add_test(tc1_1, sprintf_float_zero);               // valid
  tcase_add_test(tc1_1, sprintf_double_min);               // valid
  tcase_add_test(tc1_1, sprintf_double);                   // valid
  tcase_add_test(tc1_1, sprintf_e_zero);                   // valid
  tcase_add_test(tc1_1, sprintf_E);                        // valid
  tcase_add_test(tc1_1, sprintf_E_positive);               // valid
  tcase_add_test(tc1_1, sprintf_e_positive);               // valid
  tcase_add_test(tc1_1, sprintf_double_negative);          // valid
  tcase_add_test(tc1_1, sprintf_double_nan);               // valid
  tcase_add_test(tc1_1, sprintf_long_double);              // valid
  tcase_add_test(tc1_1, sprintf_long_double_zero);         // valid
  tcase_add_test(tc1_1, sprintf_percent);                  // valid
  tcase_add_test(tc1_1, sprintf_zero);                     // valid
  tcase_add_test(tc1_1, sprintf_ldouble);                  // valid

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
