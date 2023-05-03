#include "../inc/libmx.h"

char *mx_strdup(const char * str) {
    char *result = mx_strnew(mx_strlen(str));    
    mx_strcpy(result, str);
    return result;
}
