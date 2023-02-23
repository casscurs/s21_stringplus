#include "tests.h"
#define BUFF_SIZE 1000

START_TEST (sprintf_wchar_NULL)
{
  char str1[100];
  char str2[100];
  char *format = "%lc";
  wchar_t *stringLong = NULL;
  s21_sprintf(str1, format, stringLong);
  sprintf(str2, format, stringLong);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_wstr) {
  char str1[1000];
  char str2[1000];
  wchar_t s = 0xC9;
  wchar_t str[10]={0};
  str[0]=s;
  str[1]=s; 
  char *format = "%-10ls";
  s21_sprintf(str1, format, str);
  sprintf(str2, format, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_wchar) {
  char str1[1000];
  char str2[1000];

  char *format = "%03lc";
  wchar_t longChar = 0xC9;
  s21_sprintf(str1, format, longChar);
  sprintf(str2, format, longChar);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_string) {
  char str1[1000];
  char str2[1000];
  char format[] = "This is a simple b%0*sba";
  char str[]="ooooooo";
  s21_sprintf(str1, format,5, str);
  sprintf(str2, format, 5,str);
  ck_assert_str_eq(str1,str2);
}
END_TEST

START_TEST(sprintf_char) {
  char str1[1000];
  char str2[1000];
  char format[] = "This is a simple b%0*cba";
  char c='c';
  s21_sprintf(str1, format, 10,c);
  sprintf(str2, format, 10,c);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_char_spec_both) {
  char str1[1000];
  char str2[1000];
  char format[] = "This is %4c simple %-1s in %02c %*s";
  char c='a';
  char str[]="booba";
  s21_sprintf(str1, format, c,str,c,9,str);
  sprintf(str2, format, c,str,c,9,str);
  ck_assert_str_eq(str1, str2);
}
END_TEST
////////////////////
START_TEST(sprintf_str_prec) {
  char str1[1000];
  char str2[1000];
  char format[] = "This is a simple b%.1sba";
  char str[] = "ooooooo";
  s21_sprintf(str1, format,str);
  sprintf(str2, format,str);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(sprintf_str_width_ast_minus) {
  char str1[1000];
  char str2[1000];
  char format[] = "This is a simple b%-*sba";
  char str[] = "ooooooo";
  s21_sprintf(str1, format, 50, str);
  sprintf(str2, format, 50, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(sprintf_str_width_ast_minus2) {
  char str1[1000];
  char str2[1000];
  char format[] = "This is a simple b%*sba";
  char str[] = "ooooooo";
  s21_sprintf(str1, format, -50, str);
  sprintf(str2, format, -50, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(sprintf_str_prec_ast_minus) {
  char str1[1000];
  char str2[1000];
  char format[] = "This is a simple b%-.*sba";
  char str[] = "ooooooo";
  s21_sprintf(str1, format, 50, str);
  sprintf(str2, format, 50, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(sprintf_str_prec_ast_minus2) {
  char str1[1000];
  char str2[1000];
  char format[] = "This is a simple b%.*sba";
  char str[] = "ooooooo";
  s21_sprintf(str1, format, -50, str);
  sprintf(str2, format, -50, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(sprintf_str_width_ast_zero) {
  char str1[1000];
  char str2[1000];
  char format[] = "This is a simple b%*sba";
  char str[] = "ooooooo";
  s21_sprintf(str1, format, 50, str);
  sprintf(str2, format, 50, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(sprintf_str_prec_ast_zero) {
  char str1[1000];
  char str2[1000];
  char format[] = "This is a simple b%.*sba";
  char str[] = "ooooooo";
  s21_sprintf(str1, format, 0, str);
  sprintf(str2, format, 0, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(sprintf_c_fullhouse) {
  char str1[1000];
  char str2[1000];
  char format[] = "%-5.3c";
  char c = 'o';
  s21_sprintf(str1, format, c);
  sprintf(str2, format, c);
  ck_assert_str_eq(str1, str2);
}
END_TEST
//-------------------------------------
START_TEST(sprintf_Wstr_prec) {
  char str1[1000];
  char str2[1000];
  char format[] = "This is a simple b%.1lsba";
    wchar_t s = 0xC9;
  wchar_t str[10]={0};
  str[0]=s;
  str[1]=s; 
  s21_sprintf(str1, format,str);
  sprintf(str2, format,str);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(sprintf_Wstr_width_ast_minus) {
  char str1[1000];
  char str2[1000];
  char format[] = "This is a simple b%-*lsba";
    wchar_t s = 0xC9;
  wchar_t str[10]={0};
  str[0]=s;
  str[1]=s; 
  s21_sprintf(str1, format, 50, str);
  sprintf(str2, format, 50, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(sprintf_Wstr_width_ast_minus2) {
  char str1[1000];
  char str2[1000];
  char format[] = "This is a simple b%*lsba";
    wchar_t s = 0xC9;
  wchar_t str[10]={0};
  str[0]=s;
  str[1]=s; 
  s21_sprintf(str1, format, -50, str);
  sprintf(str2, format, -50, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(sprintf_Wstr_prec_ast_minus) {
  char str1[1000];
  char str2[1000];
  char format[] = "This is a simple b%-.*lsba";
    wchar_t s = 0xC9;
  wchar_t str[10]={0};
  str[0]=s;
  str[1]=s; 
  s21_sprintf(str1, format, 50, str);
  sprintf(str2, format, 50, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(sprintf_Wstr_prec_ast_minus2) {
  char str1[1000];
  char str2[1000];
  char format[] = "This is a simple b%.*lsba";
    wchar_t s = 0xC9;
  wchar_t str[10]={0};
  str[0]=s;
  str[1]=s; 
  s21_sprintf(str1, format, -50, str);
  sprintf(str2, format, -50, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(sprintf_Wstr_width_ast_zero) {
  char str1[1000];
  char str2[1000];
  char format[] = "This is a simple b%*lsba";
    wchar_t s = 0xC9;
  wchar_t str[10]={0};
  str[0]=s;
  str[1]=s; 
  s21_sprintf(str1, format, 050, str);
  sprintf(str2, format, 050, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(sprintf_Wstr_prec_ast_zero) {
  char str1[1000];
  char str2[1000];
  char format[] = "This is a simple b%.*lsba";
    wchar_t s = 0xC9;
  wchar_t str[10]={0};
  str[0]=s;
  str[1]=s; 
  s21_sprintf(str1, format, 0, str);
  sprintf(str2, format, 0, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(sprintf_Wc_fullhouse) {
  char str1[1000];
  char str2[1000];
  char format[] = "%-5.3lc";
  wchar_t longChar = 0xC9;
  s21_sprintf(str1, format, longChar);
  sprintf(str2, format, longChar);
  ck_assert_str_eq(str1, str2);
}
END_TEST
//__________________________________
START_TEST(wide_char) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "This is a simple wide char %lc";
  unsigned long w = L'汉';
  int a = s21_sprintf(str1, format, w);
  int b = sprintf(str2, format, w);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);
}
START_TEST(width_char) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "This is a simple wide char %5c";
  char w = 'c';
  int a = s21_sprintf(str1, format, w);
  int b = sprintf(str2, format, w);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);
}
START_TEST(minus_wide_char) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "This is a simple wide char %-5lc";
  unsigned long w = L'森';
  int a = s21_sprintf(str1, format, w);
  int b = sprintf(str2, format, w);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);
}
END_TEST
START_TEST(wide_string) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "This is a simple wide char %ls";
  wchar_t w[] = L"森我爱菠萝";
  int a = s21_sprintf(str1, format, w);
  int b = sprintf(str2, format, w);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);
}
END_TEST
START_TEST(wide_string1) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "This is a simple wide char %5.12ls";
  wchar_t w[] = L"森我爱菠萝";
  int a = s21_sprintf(str1, format, w);
  int b = sprintf(str2, format, w);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);
}
END_TEST
START_TEST(wide_string3) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "This is a simple wide char %-43ls";
  wchar_t w[] = L"森我爱菠萝";
  int a = s21_sprintf(str1, format, w);
  int b = sprintf(str2, format, w);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);
}
END_TEST
START_TEST(wide_string4) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "This is a simple wide char %43ls";
  wchar_t w[] = L"森我爱菠萝";
  int a = s21_sprintf(str1, format, w);
  int b = sprintf(str2, format, w);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);
}
END_TEST
START_TEST(wide_char2) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "This is a simple wide char %43lc";
  unsigned long w = L'森';
  int a = s21_sprintf(str1, format, w);
  int b = sprintf(str2, format, w);
  ck_assert_int_eq(a, b);
  ck_assert_str_eq(str1, str2);
}
END_TEST






//_________________
Suite *suite_sprintf(void){

Suite* s;
TCase *tc_core;

s=suite_create("s21_sprintf_C");
tc_core= tcase_create("Core");
tcase_add_test(tc_core,sprintf_wchar_NULL);
tcase_add_test(tc_core,sprintf_wstr);
tcase_add_test(tc_core,sprintf_wchar);
tcase_add_test(tc_core,sprintf_string);
tcase_add_test(tc_core,sprintf_char);
tcase_add_test(tc_core,sprintf_char_spec_both);

tcase_add_test(tc_core,sprintf_str_prec);
tcase_add_test(tc_core,sprintf_str_width_ast_minus);
//tcase_add_test(tc_core,sprintf_str_width_ast_minus2);//-
//tcase_add_test(tc_core,sprintf_str_width_ast_zero);//-
tcase_add_test(tc_core,sprintf_str_prec_ast_zero);
tcase_add_test(tc_core,sprintf_c_fullhouse);
tcase_add_test(tc_core,sprintf_str_prec_ast_minus);
tcase_add_test(tc_core,sprintf_str_prec_ast_minus2);

tcase_add_test(tc_core,sprintf_Wstr_prec);
tcase_add_test(tc_core,sprintf_Wstr_width_ast_minus);
//tcase_add_test(tc_core,sprintf_Wstr_width_ast_minus2);//-
//tcase_add_test(tc_core,sprintf_Wstr_width_ast_zero);//-
tcase_add_test(tc_core,sprintf_Wstr_prec_ast_zero);
tcase_add_test(tc_core,sprintf_Wc_fullhouse);
tcase_add_test(tc_core,sprintf_Wstr_prec_ast_minus);
tcase_add_test(tc_core,sprintf_Wstr_prec_ast_minus2);

//---------------------
tcase_add_test(tc_core,wide_char);
tcase_add_test(tc_core,width_char);
tcase_add_test(tc_core,minus_wide_char);
tcase_add_test(tc_core,wide_string);
tcase_add_test(tc_core,wide_string1);
tcase_add_test(tc_core,wide_string3);
tcase_add_test(tc_core,wide_string4);
tcase_add_test(tc_core,wide_char2);

suite_add_tcase(s, tc_core);
return s;
}