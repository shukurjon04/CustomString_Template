#include<stdlib.h>
#include<string.h>
#include "StringM.h"

static void _rekursiv_kochir(char *p,char *s){
    *p = *s;
    if(*s == '\0') return;

    _rekursiv_kochir(p+1,s+1);
}

int str_len(String *s){
    if(s == NULL || s->data == NULL || *(s->data) == '\0') return 0;
    return 1 + str_len(&(String){.data = s->data+1});
}


String *new_str(char *s){
    String *str = malloc(sizeof(String));
    str->data = malloc((strlen(s)+1)*sizeof(char));
    str->leng = strlen(s);

    _rekursiv_kochir(str->data,s);
    return str;
}


String *str_cpy(String *s1,String *s2){

    if( s1->data!=NULL){
        free(s1->data);
    }

    int len = str_len(s2);
    s1->data = malloc((len+1)*sizeof(char));
    s1->leng = len;
    _rekursiv_kochir(s1->data,s2->data);

    return s1;

}

static void _qirquvchi(char *p,char *s,int len){
    if(len <= 0||*s == '\0'){
        *p='\0';
        return;
    }
    *p=*s;
    _qirquvchi(p+1,s+1,len-1);
}

String *str_split(int start,int end, String *s){
    if(s == NULL || s->data == NULL || *(s->data) == '\0'){
        return s;
    }
    _qirquvchi(s->data,s->data+start,(end - start));

    char *buf = realloc(s->data,(end-start+1)*sizeof(char));
    if(buf!=NULL){
        s->data = buf;
    }
    return s;
}