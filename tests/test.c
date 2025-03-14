#include <stdio.h>

extern char *strstr(const char *s1, const char*s2);
extern int strncmp(const char *s1, const char *s2, unsigned long n);
extern int strcmp(const char *s1, const char *s2);

int main(void)
{
    char *s1 = "";
    char *s2 = "";

    if (strstr(s1, s2) == NULL) {
        printf("null\n");
    } else {
        printf("not null\n");
    }
    // teststrncmp with 0
    printf("result = %d\n", strncmp("tata", "toto", 10));
    printf("result = %d\n", strncmp("cest", "test", 1));
    printf("result = %d\n", strncmp("t", "a", 0));
    printf("result = %d\n", strncmp("          ", "          ", 0));
    printf("result = %d\n", strncmp("", "", 1));
    printf("result = %d\n", strncmp("", "", 0));
    printf("result = %d\n", strncmp("", "", 11));
    printf("result = %d\n", strncmp(" ", " ", 0));
    printf("result = %d\n", strncmp("", "", 10));
    printf("result = %d\n", strcmp("tata", "toto"));
    printf("result = %d\n", strcmp("cest", "test"));
    printf("result = %d\n", strcmp("t", "a"));
    printf("result = %d\n", strcmp("", ""));
    printf("result = %d\n", strcmp("cecei rest ine te", "-è-'(è(-))"));
    return 0;
}
