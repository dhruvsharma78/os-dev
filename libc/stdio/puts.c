#include <stdio.h>

/* writes the string s and a trailing newline to stdout */
int puts(const char* str) {
    return printf("%s\n", str);
}
