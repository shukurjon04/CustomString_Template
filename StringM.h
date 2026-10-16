#include<stdio.h>
#ifndef StringM
#define StringM
typedef struct String{
    char *data;
    int leng;
} String;

String *new_str(char *s);
int str_len(String *s);
String *str_cpy(String *s1, String *s2);
String *str_split(int begin,int end, String *s);

#endif