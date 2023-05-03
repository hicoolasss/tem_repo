#include "../inc/libmx.h"

char *mx_strstr(const char *haystack, const char *needle) {
    int sec_len = mx_strlen(needle);      
    int fst_len = mx_strlen(haystack);
    for (int i = 0; i < fst_len; haystack++, i++) {
        char *temp = mx_strchr(haystack, haystack[0]);
        if(mx_strncmp(temp, needle, sec_len) == 0) {
            return (char*)haystack;
        }
    }
    return NULL;
}
