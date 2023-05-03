#include "../inc/libmx.h"

char *mx_strcat(char * restrict s1, const char * restrict s2) {
    int s1_size = mx_strlen(s1);
    int s2_size = mx_strlen(s2);
    int counter = s1_size;
    for(int j = 0; counter < s1_size + s2_size; j++) {
        s1[counter] = s2[j];
        counter++;
    }
    s1[counter++] = '\0';
    return s1;
}
