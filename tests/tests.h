#pragma once

#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <stddef.h>
#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <unistd.h>
#define LIB_PATH "./libasm.so"

// function declaration 
int (*lib_strlen)(const char *s);
void *(*lib_memmove)(void *dest, const void *src, size_t n);
int (*lib_strncmp)(const char *s1, const char *s2, int n);
int (*lib_strcmp)(const char *s1, const char *s2);
int (*lib_strcasecmp)(const char *s1, const char *s2);
char *(*lib_strstr)(const char *s1, const char *s2);
