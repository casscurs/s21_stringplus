#include "s21_string.h"

/*
  calculation functions
  Cupcakep
*/

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  for (; *(str + len); len++)
    ;
  return len;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t i = 0;
  while (*str1 && s21_strchr(str2, *str1++)) {
    i++;
  }
  return i;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t i = 0;
  while (*str1 && !s21_strchr(str2, *str1++)) i++;
  return i;
}

/*
  С# functions
  Cupcakep
*/

void *s21_to_upper(const char *str) {
  char step = 'A' - 'a';

  if (str == s21_NULL) return s21_NULL;

  s21_size_t len = s21_strlen(str);
  // char *res = (char *)malloc(len + 1);
  char *res = (char *)calloc(len + 1, sizeof(char));
  for (s21_size_t i = 0; i < len; i++) {
    res[i] = str[i];
    if (res[i] >= 'a' && res[i] <= 'z') res[i] += step;
  }

  return (void *)res;
}

void *s21_to_lower(const char *str) {
  char step = 'a' - 'A';

  if (str == s21_NULL) return s21_NULL;

  s21_size_t len = s21_strlen(str);
  // char *res = (char *)malloc(len + 1);
  char *res = (char *)calloc(len + 1, sizeof(char));

  for (s21_size_t i = 0; i < len; i++) {
    res[i] = str[i];
    if (res[i] >= 'A' && res[i] <= 'Z') res[i] += step;
  }

  return (void *)res;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  s21_size_t lensrc = 0;
  s21_size_t lenstr = 0;

  if (src != s21_NULL)
    lensrc = s21_strlen(src);
  else
    lensrc = 0;
  if (str != s21_NULL)
    lenstr = s21_strlen(str);
  else
    lenstr = 0;

  s21_size_t len = lensrc + lenstr;

  if (start_index > lensrc) return s21_NULL;

  // char *res = (char *)malloc(len + 1);
  char *res = (char *)calloc(len + 1, sizeof(char));

  if (res) {
    for (s21_size_t i = 0; i < len; i++) {
      if (i < start_index)
        res[i] = src[i];
      else if (i < start_index + lenstr)
        res[i] = str[i - start_index];
      else
        res[i] = src[i - lenstr];
    }
  }
  res[lensrc + lenstr] = '\0';
  return (void *)res;
}

int find(int in, char *trim) {
  int count = 0;
  while (*trim != '\0') {
    if (*trim == in) count++;
    trim++;
  }
  int flag = 0;
  if (count >= 1) {
    flag = 1;
  } else {
    flag = 0;
  }
  return flag;
}

void *s21_trim(const char *src, const char *trim_chars) {
  s21_size_t i = 0;
  if (src == s21_NULL) return s21_NULL;
  // char *res = (char *)malloc(s21_strlen(src) + 1);
  char *res = (char *)calloc(s21_strlen(src) + 1, sizeof(char));
  strcpy(res, src);
  if (trim_chars == s21_NULL) return (void *)res;
  // char *trim = (char *)malloc(s21_strlen(trim_chars) + 1);
  char *trim = (char *)calloc(s21_strlen(trim_chars) + 1, sizeof(char));

  if (trim_chars != s21_NULL && s21_strlen(trim_chars) != 0)
    strcpy(trim, trim_chars);
  else
    strcpy(trim, "\t\n\v\r\f ");

  int index = 0, j, k = 0;
  while (find(res[index], trim)) {
    index++;
  }
  int len = s21_strlen(res);
  if (index > 0) {
    for (j = 0, k = index; j <= len - index; j++, k++) {
      res[j] = res[k];
    }
    res[j] = '\0';
  }

  for (i = s21_strlen(res) - 1; (find(res[i], trim)); i--)
    ;

  res[i + 1] = '\0';
  free(trim);

  return (void *)res;
}

/*
  comparison functions
  Takakoka

*/

int s21_strcmp(const char *str1, const char *str2) {
  for (; *str1 && *str1 == *str2; str1++, str2++) {
  }
  if (!*str1 && !*str2) return 0;
  return *str1 - *str2;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int i = 0;
  for (; *str1 && *str1 == *str2 && i < (int)n - 1; str1++, str2++) {
    i++;
  }
  if ((!*str1 && !*str2) || (n == 0)) return 0;
  return *str1 - *str2;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int k = 0;
  for (int i = 0; i < (int)n; i++) {
    if (((unsigned char *)str1)[i] != ((unsigned char *)str2)[i]) {
      k = ((unsigned char *)str1)[i] - ((unsigned char *)str2)[i];
      break;
    }
  }
  return k;
}
/*
  Search functions
  Takakoka
*/

// Searches for the first occurrence of the character 'c'
char *s21_strchr(const char *str, int c) {
  while (*str != c && *str != '\0') str++;
  if (*str == c) {
    return (char *)str;
  }
  return s21_NULL;
}

// Finds the first character in the string str1 that
// matches any character specified in str2
char *s21_strpbrk(const char *str1, const char *str2) {
  while (*str1 != '\0') {
    if (s21_strchr(str2, *str1) != s21_NULL) {
      return (char *)str1;
      break;
    }
    str1++;
  }
  return s21_NULL;
}

// Searches for the last occurrence of the character 'c'
char *s21_strrchr(const char *str, int c) {
  int start = 0;
  char *error = "";
  char *newstr = s21_NULL;
  if (c == '\0')
    return error;
  else {
    for (int i = s21_strlen(str); str[i] != c && i > 0; i--) {
      start = i;
    }
    if (start != 0) {
      for (s21_size_t i = start - 1; str[i] != '\0'; i++) {
        newstr = (char *)&str[i];
        return newstr;
      }
    }
  }
  return s21_NULL;
}

// Finds the first occurrence of the entire string needle
// which appears in the string haystack
char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t i = 0;
  s21_size_t len = s21_strlen(needle);
  if (*needle == '\0') {
    return (char *)haystack;
  } else {
    while (*haystack != '\0') {
      while (*needle == *haystack) {
        needle++;
        i++;
      }
      if (i == len) {
        return (char *)haystack - i + 1;
      }
      haystack++;
    }
  }
  return s21_NULL;
}

// Searches for the first occurrence of the character 'c'
// in the first n bytes of the string
void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *ptr = (unsigned char *)str;
  while (n > 0) {
    if (*ptr == c) {
      return (void *)ptr;
    } else {
      ptr++;
      n--;
    }
  }
  return s21_NULL;
}
/*
  Copy functions
  Jesicahi
*/

void *s21_memcpy(void *restrict dest, const void *restrict src, s21_size_t n) {
  s21_size_t i = 0;
  unsigned char *c_dest = (unsigned char *)dest;
  unsigned char *c_src = (unsigned char *)src;
  while (i < n) {
    c_dest[i] = c_src[i];
    i++;
  }
  return dest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  const char *s;
  const char *lasts;
  char *d;
  char *lastd;

  d = dest;
  s = src;
  if (d < s) {
    while (n--) *d++ = *s++;
  } else {
    lasts = s + (n - 1);
    lastd = d + (n - 1);
    while (n--) *lastd-- = *lasts--;
  }

  return (dest);
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *c_str = (unsigned char *)str;
  s21_size_t i = 0;

  while (i < n) {
    c_str[i] = c;
    i++;
  }

  return str;
}

char *s21_strcpy(char *restrict dest, const char *restrict src) {
  char *start = dest;

  while (*src != '\0') {
    *dest = *src;
    dest++;
    src++;
  }

  *dest = '\0';

  return start;
}

char *s21_strncpy(char *restrict dest, const char *restrict src, s21_size_t n) {
  char *start = dest;
  s21_size_t src_len = s21_strlen(src);
  for (s21_size_t i = 0; i < n; i++) {
    if (i >= src_len) {
      dest[i] = '\0';
    } else {
      dest[i] = src[i];
    }
  }
  return start;
}

/*
  help functions
  Jesicahi
*/

char *s21_strcat(char *restrict dest, const char *restrict src) {
  char *start = dest;

  while (*dest != '\0') {
    dest++;
  }

  while (*src != '\0') {
    *dest = *src;
    dest++;
    src++;
  }

  *dest = '\0';
  return start;
}

char *s21_strncat(char *restrict dest, const char *restrict src, s21_size_t n) {
  char *tmp = dest;
  while (*tmp != '\0') tmp++;
  for (s21_size_t i = 0; i < n; i++) *tmp++ = src[i];
  return dest;
}

char *s21_strtok(char *restrict str, const char *restrict delim) {
  static char *last;
  register int ch;

  if (str == 0) {
    str = last;
  }
  do {
    if ((ch = *str++) == '\0') {
      return 0;
    }
  } while (s21_strchr(delim, ch));
  --str;
  last = str + s21_strcspn(str, delim);
  if (*last != 0) {
    *last++ = 0;
  }
  return str;
}

#if defined(__APPLE__)
#define MAX_ERRLIST 107
#define MIN_ERRLIST -1
#define ERROR "Unknown error: "

const char *arr_error[] = {"Undefined error: 0",
                           "Operation not permitted",
                           "No such file or directory",
                           "No such process",
                           "Interrupted system call",
                           "Input/output error",
                           "Device not configured",
                           "Argument list too long",
                           "Exec format error",
                           "Bad file descriptor",
                           "No child processes",
                           "Resource deadlock avoided",
                           "Cannot allocate memory",
                           "Permission denied",
                           "Bad address",
                           "Block device required",
                           "Resource busy",
                           "File exists",
                           "Cross-device link",
                           "Operation not supported by device",
                           "Not a directory",
                           "Is a directory",
                           "Invalid argument",
                           "Too many open files in system",
                           "Too many open files",
                           "Inappropriate ioctl for device",
                           "Text file busy",
                           "File too large",
                           "No space left on device",
                           "Illegal seek",
                           "Read-only file system",
                           "Too many links",
                           "Broken pipe",
                           "Numerical argument out of domain",
                           "Result too large",
                           "Resource temporarily unavailable",
                           "Operation now in progress",
                           "Operation already in progress",
                           "Socket operation on non-socket",
                           "Destination address required",
                           "Message too long",
                           "Protocol wrong type for socket",
                           "Protocol not available",
                           "Protocol not supported",
                           "Socket type not supported",
                           "Operation not supported",
                           "Protocol family not supported",
                           "Address family not supported by protocol family",
                           "Address already in use",
                           "Can't assign requested address",
                           "Network is down",
                           "Network is unreachable",
                           "Network dropped connection on reset",
                           "Software caused connection abort",
                           "Connection reset by peer",
                           "No buffer space available",
                           "Socket is already connected",
                           "Socket is not connected",
                           "Can't send after socket shutdown",
                           "Too many references: can't splice",
                           "Operation timed out",
                           "Connection refused",
                           "Too many levels of symbolic links",
                           "File name too long",
                           "Host is down",
                           "No route to host",
                           "Directory not empty",
                           "Too many processes",
                           "Too many users",
                           "Disc quota exceeded",
                           "Stale NFS file handle",
                           "Too many levels of remote in path",
                           "RPC struct is bad",
                           "RPC version wrong",
                           "RPC prog. not avail",
                           "Program version wrong",
                           "Bad procedure for program",
                           "No locks available",
                           "Function not implemented",
                           "Inappropriate file type or format",
                           "Authentication error",
                           "Need authenticator",
                           "Device power is off",
                           "Device error",
                           "Value too large to be stored in data type",
                           "Bad executable (or shared library)",
                           "Bad CPU type in executable",
                           "Shared library version mismatch",
                           "Malformed Mach-o file",
                           "Operation canceled",
                           "Identifier removed",
                           "No message of desired type",
                           "Illegal byte sequence",
                           "Attribute not found",
                           "Bad message",
                           "EMULTIHOP (Reserved)",
                           "No message available on STREAM",
                           "ENOLINK (Reserved)",
                           "No STREAM resources",
                           "Not a STREAM",
                           "Protocol error",
                           "STREAM ioctl timeout",
                           "Operation not supported on socket",
                           "Policy not found",
                           "State not recoverable",
                           "Previous owner died",
                           "Interface output queue is full"};

#elif defined(__linux__)
#define MAX_ERRLIST 134
#define MIN_ERRLIST -1
#define ERROR "Unknown error "

static const char *arr_error[] = {
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource temporarily unavailable",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Device or resource busy",
    "File exists",
    "Invalid cross-device link",
    "No such device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Numerical result out of range",
    "Resource deadlock avoided",
    "File name too long",
    "No locks available",
    "Function not implemented",
    "Directory not empty",
    "Too many levels of symbolic links",
    "Unknown error 41",
    "No message of desired type",
    "Identifier removed",
    "Channel number out of range",
    "Level 2 not synchronized",
    "Level 3 halted",
    "Level 3 reset",
    "Link number out of range",
    "Protocol driver not attached",
    "No CSI structure available",
    "Level 2 halted",
    "Invalid exchange",
    "Invalid request descriptor",
    "Exchange full",
    "No anode",
    "Invalid request code",
    "Invalid slot",
    "Unknown error 58",
    "Bad font file format",
    "Device not a stream",
    "No data available",
    "Timer expired",
    "Out of streams resources",
    "Machine is not on the network",
    "Package not installed",
    "Object is remote",
    "Link has been severed",
    "Advertise error",
    "Srmount error",
    "Communication error on send",
    "Protocol error",
    "Multihop attempted",
    "RFS specific error",
    "Bad message",
    "Value too large for defined data type",
    "Name not unique on network",
    "File descriptor in bad state",
    "Remote address changed",
    "Can not access a needed shared library",
    "Accessing a corrupted shared library",
    ".lib section in a.out corrupted",
    "Attempting to link in too many shared libraries",
    "Cannot exec a shared library directly",
    "Invalid or incomplete multibyte or wide character",
    "Interrupted system call should be restarted",
    "Streams pipe error",
    "Too many users",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol",
    "Address already in use",
    "Cannot assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Transport endpoint is already connected",
    "Transport endpoint is not connected",
    "Cannot send after transport endpoint shutdown",
    "Too many references: cannot splice",
    "Connection timed out",
    "Connection refused",
    "Host is down",
    "No route to host",
    "Operation already in progress",
    "Operation now in progress",
    "Stale file handle",
    "Structure needs cleaning",
    "Not a XENIX named type file",
    "No XENIX semaphores available",
    "Is a named type file",
    "Remote I/O error",
    "Disk quota exceeded",
    "No medium found",
    "Wrong medium type",
    "Operation canceled",
    "Required key not available",
    "Key has expired",
    "Key has been revoked",
    "Key was rejected by service",
    "Owner died",
    "State not recoverable",
    "Operation not possible due to RF-kill",
    "Memory page has hardware error"};
#endif

char *s21_strerror(int errnum) {
  static char *ptr_result = s21_NULL;
  if (MIN_ERRLIST < errnum && errnum < MAX_ERRLIST) {
    ptr_result = (char *)arr_error[errnum];
  } else {
    static char message[128] = {'\0'};
    sprintf(message, "%s%d", ERROR, errnum);
    ptr_result = message;
  }
  return ptr_result;
}
