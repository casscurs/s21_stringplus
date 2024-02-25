# s21_string+

Implementation of the string.h library with additions.

This is a team project developed in collaboration with Cupcakep, Takakoka, Mathildc and Jesicahi also students of School 21 in Moscow.

## Chapter I

### string.h Types

| No. | Variable | Description |
| ------ | ------ | ------ |
| 1 | size_t | Unsigned integral type resulting from the sizeof keyword. |
	
### string.h Macro

| No. | Macro | Description |
| ------ | ------ | ------ |
| 1 | NULL | Value of a null pointer constant. |

### string.h Functions

| No. | Function | Description |
| ------ | ------ | ------ |
| 1 | void *memchr(const void *str, int c, size_t n) | Searches for the first occurrence of character c in the first n bytes of the string str. |
| 2 | int memcmp(const void *str1, const void *str2, size_t n) | Compares the first n bytes of str1 and str2. |
| 3 | void *memcpy(void *dest, const void *src, size_t n) | Copies n characters from src to dest. |
| 4 | void *memmove(void *dest, const void *src, size_t n) | Copies n characters from src to dest. |
| 5 | void *memset(void *str, int c, size_t n) | Copies the character c to the first n characters of the string str. |
| 6 | char *strcat(char *dest, const char *src) | Appends src to the end of dest. |
| 7 | char *strncat(char *dest, const char *src, size_t n) | Appends src to dest up to n characters long. |
| 8 | char *strchr(const char *str, int c) | Searches for the first occurrence of character c in str. |
| 9 | int strcmp(const char *str1, const char *str2) | Compares str1 to str2. |
| 10 | int strncmp(const char *str1, const char *str2, size_t n) | Compares at most the first n bytes of str1 and str2. |
| 11 | char *strcpy(char *dest, const char *src) | Copies src to dest. |
| 12 | char *strncpy(char *dest, const char *src, size_t n) | Copies up to n characters from src to dest. |
| 13 | size_t strcspn(const char *str1, const char *str2) | Calculates the length of the initial segment of str1 not in str2. |
| 14 | char *strerror(int errnum) | Searches an internal array for the error number errnum and returns a pointer to an error message string. |
| 15 | size_t strlen(const char *str) | Computes the length of str. |
| 16 | char *strpbrk(const char *str1, const char *str2) | Finds the first character in str1 that matches any character in str2. |
| 17 | char *strrchr(const char *str, int c) | Searches for the last occurrence of character c in str. |
| 18 | size_t strspn(const char *str1, const char *str2) | Calculates the length of the initial segment of str1 consisting entirely of characters in str2. |
| 19 | char *strstr(const char *haystack, const char *needle) | Finds the first occurrence of needle in haystack. |
| 20 | char *strtok(char *str, const char *delim) | Breaks str into tokens separated by delim. |

### sprintf and sscanf

- int sscanf(const char *str, const char *format, ...) - reads formatted input from a string.
- int sprintf(char *str, const char *format, ...) - sends formatted output to a string.

### sprintf And sscanf Specifiers

| No. | Specifier | sprintf output | sscanf output |
| --- | --- | --- | --- |
| 1 | c | Character | Character |
| 2 | d | Signed decimal integer | Signed decimal integer |
| 3 | i | Signed decimal integer | Signed integer |
| 4 | e | Scientific notation using e character | Decimal floating point or scientific notation |
| 5 | E | Scientific notation using E character | Decimal floating point or scientific notation |
| 6 | f | Decimal floating point | Decimal floating point or scientific notation |
| 7 | g | Shortest representation of decimal floating point | Decimal floating point or scientific notation |
| 8 | G | Shortest representation of decimal floating point | Decimal floating point or scientific notation |
| 9 | o | Unsigned octal | Unsigned octal |
| 10 | s | String of characters | String of characters |
| 11 | u | Unsigned decimal integer | Unsigned decimal integer |
| 12 | x | Unsigned hexadecimal integer | Unsigned hexadecimal integer |
| 13 | X | Unsigned hexadecimal integer | Unsigned hexadecimal integer |
| 14 | p | Pointer address | Pointer address |
| 15 | n | Number of characters printed until %n | Number of characters scanned until %n |
| 16 | % | Character % | Character % |

### sprintf Flags

| No. | Flags | Description |
| --- | --- | --- |
| 1 | - | Left-justify within the given field width. |
| 2 | + | Precede the result with a plus or minus sign. |
| 3 | (space) | Insert a blank space before the value if no sign is written. |
| 4 | # | Precede with 0, 0x, or 0X for values different than zero. Force a decimal point even if no digits follow. |
| 5 | 0 | Left-pad with zeroes. |

### sprintf And sscanf Width Description

| No. | Width | Description |
| --- | --- | --- |
| 1 | (number) | Minimum number of characters to be printed. |
| 2 | * | Width is specified as an additional integer value argument. |

### sprintf Precision Description

| No. | .precision | Description |
| --- | --- | --- |
| 1 | .number | Minimum number of digits to be written or the number of digits to be printed after the decimal point. |
| 2 | .* | Precision is specified as an additional integer value argument. |

### sprintf And sscanf Length Description

| No. | Length | Description |
| --- | --- | --- |
| 1 | h | Interpreted as short int or unsigned short int. |
| 2 | l | Interpreted as long int or unsigned long int for integers, and as wide character or wide character string for characters. |
| 3 | L | Interpreted as long double. |

### Special string processing functions (from the String class in C#)

| No. | Function | Description |
| ------ | ------ | ------ |
| 1 | void *to_upper(const char *str) | Returns a copy of str converted to uppercase. |
| 2 | void *to_lower(const char *str) | Returns a copy of str converted to lowercase. |
| 3 | void *insert(const char *src, const char *str, size_t start_index) | Inserts str at start_index in src. |
| 4 | void *trim(const char *src, const char *trim_chars) | Removes leading and trailing occurrences of specified characters from src. |

## Chapter II

## Part 1. Implementation of string.h library functions

- Develop the functions described above in C language following POSIX.1-2017 standard.
- Adhere to Google style guide.
- Ensure proper unit-test coverage using the Check library.
- Implement as a static library (with header file s21_string.h).
- Minimize code duplication; follow principles of structured programming.
- Avoid using system errors arrays; implement platform-specific errors arrays.
- Functions should work with ASCII-encoded single-byte character strings.

## Part 2. Partial Implementation of the sprintf function

- Implement sprintf with partial formatting support, as outlined.
- Follow the same guidelines as Part 1.
- Support specifiers, flags, width, precision, and length description.

## Part 3. Bonus. Implementation of some format modifiers of the sprintf function

- Extend sprintf support to additional format modifiers.
- Follow guidelines from Part 1.
- Support specified specifiers, flags, width, precision, and length description.

## Part 4. Bonus. Implementation of the sscanf function

- Implement sscanf function.
- Follow guidelines from Part 1.
- Support full formatting.

## Part 5. Bonus. Implementation of special string processing functions

- Implement special string processing functions from the String class in C#.
- Follow guidelines from Part 1, excluding comparison with standard library.
