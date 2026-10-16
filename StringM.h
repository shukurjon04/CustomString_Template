#ifndef STRINGM_H
#define STRINGM_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

// O'zingizning String strukturangiz
typedef struct String {
    char *data;
    int leng;
} String;

// 1-qism: Topshiriqda so'ralgan standart funksiyalar (Hafta 9 shartlari)
size_t my_strlen(const char *s);
char *my_strcpy(char *dest, const char *src);
char *my_strtok(char *str, const char *delim);
char **my_split(const char *s, char sep);
void my_split_free(char **arr);

// 2-qism: O'zingizning String struktura funksiyalaringiz
String *new_str(const char *s);
int str_len(String *s);
String *str_cpy(String *s1, String *s2);
String *str_split(int begin, int end, String *s);
void free_str(String *s);

#endif