#include <stdio.h>
#include "StringM.h"

int main() {
    printf("=== 1. String struktura testlari ===\n");
    String *s1 = new_str("Shukurjon");
    String *s2 = new_str("Dasturchi");

    printf("s1: %s (uzunligi = %d)\n", s1->data, str_len(s1));

    // Qirqish testi (0 dan 6 gacha -> "Shukur")
    str_split(0, 6, s1);
    printf("Qirqilgan s1: %s (uzunligi = %d)\n", s1->data, s1->leng);

    // Nusxalash testi
    str_cpy(s1, s2);
    printf("Nusxalangan s1: %s (uzunligi = %d)\n\n", s1->data, s1->leng);

    // Xotirani tozalaymiz (Valgrind uchun!)
    free_str(s1);
    free_str(s2);

    printf("=== 2. Hafta 9 funksiyalari testlari ===\n");
    char buf[50];
    my_strcpy(buf, "salom,dunyo,c,dasturlash");
    printf("my_strcpy va my_strlen: '%s' (%zu ta belgi)\n", buf, my_strlen(buf));

    // my_strtok testi
    printf("my_strtok natijasi: ");
    char *tok = my_strtok(buf, ",");
    while (tok != NULL) {
        printf("[%s] ", tok);
        tok = my_strtok(NULL, ",");
    }
    printf("\n");

    // my_split va my_split_free testi
    char **sozlar = my_split("bir ikki uch tort", ' ');
    printf("my_split natijasi: ");
    for (int i = 0; sozlar[i] != NULL; i++) {
        printf("{%s} ", sozlar[i]);
    }
    printf("\n");

    // Split xotirasini tozalaymiz
    my_split_free(sozlar);

    return 0;
}