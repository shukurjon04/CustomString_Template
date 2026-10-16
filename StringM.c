#include "StringM.h"
// 1. my_strlen
size_t my_strlen(const char *s) {
    if (s == NULL) return 0;

    size_t len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

// 2. my_strcpy
char *my_strcpy(char *dest, const char *src) {
    if (dest == NULL || src == NULL) return dest;

    char *p = dest;
    while (*src != '\0') {
        *p = *src;
        p++;
        src++;
    }
    *p = '\0';
    return dest;
}

// my_strtok uchun yordamchi funksiya
static int _is_delim(char c, const char *delim) {
    while (*delim != '\0') {
        if (c == *delim) return 1;
        delim++;
    }
    return 0;
}

// 3. my_strtok
char *my_strtok(char *str, const char *delim) {
    static char *saqlangan = NULL;

    if (delim == NULL) return NULL;
    if (str != NULL) {
        saqlangan = str;
    }
    if (saqlangan == NULL) return NULL;

    // Boshidagi bo'luvchi belgilarni o'tkazib yuboramiz
    while (*saqlangan != '\0' && _is_delim(*saqlangan, delim)) {
        saqlangan++;
    }

    if (*saqlangan == '\0') {
        saqlangan = NULL;
        return NULL;
    }

    char *token_boshi = saqlangan;

    // Keyingi bo'luvchi belgigacha yuramiz
    while (*saqlangan != '\0' && !_is_delim(*saqlangan, delim)) {
        saqlangan++;
    }

    if (*saqlangan != '\0') {
        *saqlangan = '\0';
        saqlangan++;
    } else {
        saqlangan = NULL;
    }

    return token_boshi;
}

// my_split uchun so'zlar sonini hisoblovchi yordamchi
static int _sozlar_soni(const char *s, char sep) {
    int count = 0;
    int ichida = 0;

    while (*s != '\0') {
        if (*s != sep && !ichida) {
            ichida = 1;
            count++;
        } else if (*s == sep) {
            ichida = 0;
        }
        s++;
    }
    return count;
}

// 4. my_split
char **my_split(const char *s, char sep) {
    if (s == NULL) return NULL;

    int words = _sozlar_soni(s, sep);
    char **natija = (char **)malloc((words + 1) * sizeof(char *));
    if (natija == NULL) return NULL;

    int idx = 0;
    while (*s != '\0') {
        while (*s == sep && *s != '\0') s++;
        if (*s == '\0') break;

        int len = 0;
        while (s[len] != '\0' && s[len] != sep) {
            len++;
        }

        natija[idx] = (char *)malloc((len + 1) * sizeof(char));
        if (natija[idx] == NULL) {
            // Xotira xatosi bo'lsa, shu paytgacha ajratilganini tozalaymiz
            my_split_free(natija);
            return NULL;
        }

        for (int i = 0; i < len; i++) {
            natija[idx][i] = s[i];
        }
        natija[idx][len] = '\0';

        idx++;
        s += len;
    }

    natija[idx] = NULL;
    return natija;
}

// 5. my_split_free
void my_split_free(char **arr) {
    if (arr == NULL) return;

    for (int i = 0; arr[i] != NULL; i++) {
        free(arr[i]);
    }
    free(arr);
}


static void _rekursiv_kochir(char *p, const char *s) {
    *p = *s;
    if (*s == '\0') return;
    _rekursiv_kochir(p + 1, s + 1);
}

static void _qirquvchi(char *p, const char *s, int len) {
    if (len <= 0 || *s == '\0') {
        *p = '\0';
        return;
    }
    *p = *s;
    _qirquvchi(p + 1, s + 1, len - 1);
}

int str_len(String *s) {
    if (s == NULL || s->data == NULL || *(s->data) == '\0') return 0;
    return 1 + str_len(&(String){ .data = s->data + 1 });
}

String *new_str(const char *s) {
    if (s == NULL) return NULL;

    String *str = (String *)malloc(sizeof(String));
    int len = (int)my_strlen(s);

    str->data = (char *)malloc((len + 1) * sizeof(char));
    str->leng = len;

    _rekursiv_kochir(str->data, s);
    return str;
}

String *str_cpy(String *s1, String *s2) {
    if (s1 == NULL || s2 == NULL || s2->data == NULL) return NULL;

    if (s1->data != NULL) {
        free(s1->data);
    }

    int len = str_len(s2);
    s1->data = (char *)malloc((len + 1) * sizeof(char));
    s1->leng = len;

    _rekursiv_kochir(s1->data, s2->data);
    return s1;
}

String *str_split(int start, int end, String *s) {
    if (s == NULL || s->data == NULL || *(s->data) == '\0') {
        return s;
    }

    if (start < 0) start = 0;
    if (end > s->leng) end = s->leng;
    int len = end - start;
    if (len < 0) len = 0;

    _qirquvchi(s->data, s->data + start, len);
    s->leng = len;

    char *temp = (char *)realloc(s->data, (len + 1) * sizeof(char));
    if (temp != NULL) {
        s->data = temp;
    }

    return s;
}

void free_str(String *s) {
    if (s != NULL) {
        free(s->data);
        free(s);
    }
}