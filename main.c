#include<stdio.h>

#include "StringM.h"

int main(){
    String *s = new_str("Shukurjon");

    printf("uzunligi = %d ga teng , matn = %s\n",s->leng,s->data);


    printf("kesilgan matn = %s , boshlanishi = %d va tugashi = %d\n",(str_split(2,6,s)->data),2,6);
}