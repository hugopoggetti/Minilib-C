#include "tests.h"
#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>


void *lib = NULL;

// https://www.ibm.com/docs/en/zos/2.5.0?topic=functions-dlopen-gain-access-dynamic-link-library
void load_minilib(void)
{
    if (lib)
        return;

    if (access("./libasm.so", R_OK) == -1) {
        perror("my_lib error access");
        return;
    }
    lib = dlopen("./libasm.so", RTLD_LAZY);
    if (!lib) {
        fprintf(stderr, "dlopen failed: %s\n", dlerror());
        //perror("my_lib.so");
    } else {
        lib_strlen = dlsym(lib, "strlen");
        lib_memmove = dlsym(lib, "memmove");
        lib_strcmp = dlsym(lib, "strcmp");
        lib_strncmp = dlsym(lib, "strncmp");
        lib_strcasecmp = dlsym(lib, "strcasecmp");
        lib_strstr = dlsym(lib, "strstr");
    }
}

Test(strlen, strlen_hello_len)
{
    load_minilib();
    const char * str = "Hello world";

    cr_assert (strlen(str) == lib_strlen(str));
}

Test(strlen, strlen_empty_str)
{
    load_minilib();
    const char *str = "";

    cr_assert (strlen(str) == lib_strlen(str));
}

// memmove test
Test(memmove, memmove_base)
{
    load_minilib();
    char *dest = strdup("test");
    
    const char *src = "this is a str";
    cr_assert(!strcmp("this", (char *)lib_memmove(dest, src, 4)));
}

Test(memmove, memmove_overlap)
{
    load_minilib();

    char *dest = strdup("memmove test with overlap");
    
    cr_assert(memmove(dest + 10, dest + 15, 11)
            == lib_memmove(dest + 10, dest + 15, 11));
}

Test(memmove, memmove_empty_str)
{
    load_minilib();

    char *t = strdup("");
    char *d = strdup("");
    
    cr_assert(!strcmp(t, lib_memmove(t, d, 1)));
}

// strcmp test

Test(strcmp, strcmp_base)
{
    load_minilib();
    char *s1 = "test";

    cr_assert(strcmp(s1, s1) == lib_strcmp(s1,s1));
}

Test(strcmp, strcmp_diff)
{
    load_minilib();
    char *s1 = "test ";
    char *s2 = "test  ";

    cr_assert(strcmp(s1, s2) == lib_strcmp(s1,s2));
}

Test(strcmp, strcmp_diff_)
{
    load_minilib();
    char *s1 = "test ";
    char *s2 = "test  ";

    cr_assert(strcmp(s2, s1) == lib_strcmp(s2,s1));
    cr_assert(strcmp(s2, s2) == lib_strcmp(s2,s2));
}

Test(strcmp, strcmp_same)
{
    load_minilib();
    char *s1 = "test ";
    char *s2 = "test  ";

    cr_assert(strcmp(s2, s2) == lib_strcmp(s2,s2));
}

Test(strcmp, strcmp_empty)
{
    load_minilib();
    char *s1 = "";
    char *s2 = "";

    cr_assert(strcmp(s1, s2) == lib_strcmp(s1,s2));
    cr_assert(strcmp(s2, s1) == lib_strcmp(s2,s1));
}

Test(strcmp, strcmp_one_empty_str)
{
    load_minilib();
    char *s1 = "Hello";
    char *s2 = "";

    cr_assert(strcmp(s1, s2) == lib_strcmp(s1,s2));
    cr_assert(strcmp(s2, s1) == lib_strcmp(s2,s1));
}

Test(strcmp, strcmp_not_equal)
{
    load_minilib();
    char *s1 = "this is a string";
    char *s2 = "this string is not the same";

    cr_assert(strcmp(s2, s1) == lib_strcmp(s2,s1));
}

Test(strcmp, strcmp_not_equal_other)
{
    load_minilib();
    char *s1 = "this is a string";
    char *s2 = "this string is not the same";

    cr_assert(strcmp(s1, s2) == lib_strcmp(s1,s2));
}

// strncmp test

Test(strncmp, strncmp_base)
{
    // cpy to 0
    load_minilib();
    char *s1 = "test";
    int l = strlen(s1);

    cr_assert(strncmp(s1, s1, l) == lib_strncmp(s1,s1, l));
}

Test(strncmp, strncmp_base_to_long_len)
{
    load_minilib();
    char *s1 = "test";
    int l = strlen(s1) + 10;

    cr_assert(strncmp(s1, s1, l) == lib_strncmp(s1,s1, l));
}

Test(strncmp, strncmp_diff)
{
    load_minilib();
    char *s1 = "test ";
    char *s2 = "test  ";
    int l = strlen(s2);

    cr_assert(strncmp(s1, s2, l) == lib_strncmp(s1,s2, l));
    cr_assert(strncmp(s2, s1, l) == lib_strncmp(s2,s1, l));
    cr_assert(strncmp(s2, s2, l) == lib_strncmp(s2,s2, l));
}

Test(strncmp, strncmp_empty)
{
    load_minilib();
    char *s1 = "";
    char *s2 = "";
    int l = strlen(s2);

    cr_assert(strncmp(s1, s2, l) == lib_strncmp(s1,s2, l));
    cr_assert(strncmp(s2, s1, l) == lib_strncmp(s2,s1, l));
}

Test(strncmp, strncmp_diff_len)
{
    load_minilib();
    char *s1 = "this";
    char *s2 = "this is a test";
    int l = strlen(s1);

    cr_assert(strncmp(s1, s2, l) == lib_strncmp(s1,s2, l));
    cr_assert(strncmp(s2, s1, l) == lib_strncmp(s2,s1, l));
}

Test(strncmp, strncmp_one_char)
{
    load_minilib();
    char *s1 = " ";
    char *s2 = " ";
    int l = 10;

    cr_assert(strncmp(s1, s2, l) == lib_strncmp(s1,s2, l));
    cr_assert(strncmp(s2, s1, l) == lib_strncmp(s2,s1, l));
}

Test(strncmp, strncmp_0_byte)
{
    load_minilib();
    char *s1 = " ";
    char *s2 = " ";
    int l = 0;

    cr_assert(strncmp(s1, s2, l) == lib_strncmp(s1,s2, l));
    cr_assert(strncmp(s2, s1, l) == lib_strncmp(s2,s1, l));
}

Test(strncmp, strncmp_0_byte_2)
{
    load_minilib();
    char *s1 = "";
    char *s2 = "";
    int l = 0;

    cr_assert(strncmp(s1, s2, l) == lib_strncmp(s1,s2, l));
    cr_assert(strncmp(s2, s1, l) == lib_strncmp(s2,s1, l));
}

Test(strncmp, strncmp_0_byte_3)
{
    load_minilib();
    char *s1 = "cckdcncd";
    char *s2 = "dcdcvdvvv";
    int l = 0;

    cr_assert(strncmp(s1, s2, l) == lib_strncmp(s1,s2, l));
    cr_assert(strncmp(s2, s1, l) == lib_strncmp(s2,s1, l));
}

Test(strncmp, strncmp_one_empty_str)
{
    load_minilib();
    char *s1 = "Hello";
    char *s2 = "";
    int l = strlen(s1);    

    cr_assert(strncmp(s1, s2,l) == lib_strncmp(s1,s2,l));
    cr_assert(strncmp(s2, s1,l) == lib_strncmp(s2,s1,l));
}

Test(strncmp, strncmp_not_equal)
{
    load_minilib();
    char *s1 = "this is a string";
    char *s2 = "this string is not the same";
    int l = strlen(s2);

    cr_assert(strncmp(s1, s2, l) == lib_strncmp(s1,s2, l));
    cr_assert(strncmp(s2, s1, l) == lib_strncmp(s2,s1, l));
}

// strcase cmp test

Test(strcasecmp, strcasecmp_base)
{
    load_minilib();
    char *s1 = "test";
    char *s2 = "TEST";

    cr_assert(strcasecmp(s1, s2) == lib_strcasecmp(s1,s2));
    cr_assert(strcasecmp(s2, s1) == lib_strcasecmp(s2,s1));
    cr_assert(strcasecmp(s2, s2) == lib_strcasecmp(s2,s2));
    cr_assert(strcasecmp(s1, s1) == lib_strcasecmp(s1,s1));
}

Test(strcasecmp, strcasecmp_diff)
{
    load_minilib();
    char *s1 = "test ";
    char *s2 = "TEST  ";

    cr_assert(strcasecmp(s1, s2) == lib_strcasecmp(s1,s2));
    cr_assert(strcasecmp(s2, s1) == lib_strcasecmp(s2,s1));
    cr_assert(strcasecmp(s2, s2) == lib_strcasecmp(s2,s2));
}

Test(strcasecmp, strcasecmp_empty)
{
    load_minilib();
    char *s1 = "";
    char *s2 = "";

    cr_assert(strcasecmp(s1, s2) == lib_strcasecmp(s1,s2));
    cr_assert(strcasecmp(s2, s1) == lib_strcasecmp(s2,s1));
}

// Test(strcasecmp, strcasecmp_one_empty_str)
// {
//     load_minilib();
//     char *s1 = "Hello";
//     char *s2 = "";
//     int l = strlen(s1);    
//
//     cr_assert(strcasecmp(s1, s2)== lib_strcasecmp(s1,s2));
//     cr_assert(strcasecmp(s2, s1)== lib_strcasecmp(s2,s1));
// }

Test(strcasecmp, strcasecmp_not_equal)
{
    load_minilib();
    char *s1 = "this is a string";
    char *s2 = "this string is not the same";
    int l = strlen(s2);

    cr_assert(strcasecmp(s1, s2) == lib_strcasecmp(s1,s2));
    cr_assert(strcasecmp(s2, s1) == lib_strcasecmp(s2,s1));
}

Test(strcasecmp, strcasecmp_not_equal_U)
{
    load_minilib();
    char *s1 = "THIS IS A STRING";
    char *s2 = "THIS IS E STRING";

    cr_assert(strcasecmp(s1, s2) == lib_strcasecmp(s1,s2));
    cr_assert(strcasecmp(s2, s1) == lib_strcasecmp(s2,s1));
}

// strstr test

Test(strstr, strstr_base)
{
    load_minilib();
    char *s1 = "THIS";
    char *s2 = "IS";

    cr_assert(lib_strstr(s1, s2) == strstr(s1,s2));
    cr_assert(lib_strstr(s2, s1) == strstr(s2,s1));
}

Test(strstr, strstr_emptystr)
{
    load_minilib();
    char *s1 = "";
    char *s2 = "";

    cr_assert(lib_strstr(s1, s2) == strstr(s1,s2));
    cr_assert(lib_strstr(s2, s1) == strstr(s2,s1));
}

Test(strstr, strstr_null)
{
    load_minilib();
    char *s2 = "";
    char *s1 = "";

    // if (lib_strstr("", "") == NULL) {
    //     printf("null\n");
    // } else {
    //     printf("guillement\n");
    // }
    cr_assert(lib_strstr(s1, s2) == strstr(s1,s2));
    cr_assert(lib_strstr(s2, s1) == strstr(s2,s1));
}


Test(strstr, strstr_brut_force)
{
    char one[50];
    load_minilib();
    char *it = "strstr";
    cr_assert(lib_strstr("abcd", "z") == NULL);	/* Not found. */
    cr_assert(lib_strstr("abcd", "abx") == NULL);	/* Dead end. */
    (void) strcpy(one, "abcd");
    cr_assert(lib_strstr(one, "c") == one+2);	/* Basic test. */
    cr_assert(lib_strstr(one, "bc") == one+1);	/* Multichar. */
    cr_assert(lib_strstr(one, "d") == one+3);	/* End of lib_strstring. */
    cr_assert(lib_strstr(one, "cd") == one+2);	/* Tail of lib_strstring. */
    cr_assert(lib_strstr(one, "abc") == one);	/* Beginning. */
    cr_assert(lib_strstr(one, "abcd") == one);	/* Exact match. */
    cr_assert(lib_strstr(one, "abcde") == NULL);	/* Too long. */
    cr_assert(lib_strstr(one, "de") == NULL);	/* Past end. */
    cr_assert(lib_strstr(one, "") == one);	/* Finding empty. */
    (void) strcpy(one, "ababa");
    cr_assert(lib_strstr(one, "ba") == one+1);	/* Finding first. */
    (void) strcpy(one, "");
    cr_assert(lib_strstr(one, "b") == NULL);	/* Empty lib_strstring. */
    cr_assert(lib_strstr(one, "") == one);	/* Empty in empty lib_strstring. */
    (void) strcpy(one, "bcbca");
    cr_assert(lib_strstr(one, "bca") == one+2);	/* False start. */
    (void) strcpy(one, "bbbcabbca");
    cr_assert(lib_strstr(one, "bbca") == one+1);	/* With overlap. */    
}

Test(strstr, strstr_len1_str)
{
    load_minilib();
    char *s1 = " ";
    char *s2 = " ";

    cr_assert(lib_strstr(s1, s2) == strstr(s1,s2));
    cr_assert(lib_strstr(s2, s1) == strstr(s2,s1));
}

Test(strstr, strstr_same_str)
{
    load_minilib();
    char *s1 = "test";
    char *s2 = "test";

    cr_assert(lib_strstr(s1, s2) == strstr(s1,s2));
    cr_assert(lib_strstr(s2, s1) == strstr(s2,s1));
}

Test(strstr, strstr_one_empty_str)
{
    load_minilib();
    char *s1 = "test";
    char *s2 = "";

    cr_assert(lib_strstr(s1, s2) == strstr(s1,s2));
    cr_assert(lib_strstr(s2, s1) == strstr(s2,s1));
}

Test(strstr, strstr_2_find)
{
    load_minilib();
    char *s1 = "test test test";
    char *s2 = "es";

    cr_assert(lib_strstr(s1, s2) == strstr(s1,s2));
    cr_assert(lib_strstr(s2, s1) == strstr(s2,s1));
}

Test(strstr, strstr_no_find)
{
    load_minilib();
    char *s1 = "this is a test";
    char *s2 = "ww";

    cr_assert(lib_strstr(s1, s2) == strstr(s1,s2));
    cr_assert(lib_strstr(s2, s1) == strstr(s2,s1));
}
