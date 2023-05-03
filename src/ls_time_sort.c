#include "header.h"

void ls_time_sort(char **arr, int size, int type_sort) {
    int check = 1;
    char *t;
    while(check) {
        check = 0;
        for (int i = 0; i < size - 1; i++) {
            struct stat first_temp;
            struct stat second_temp;                         
            stat(arr[i], &first_temp);
            stat(arr[i+1], &second_temp);
            if ((type_sort == 1) ? (first_temp.st_atime < second_temp.st_atime) : ((type_sort == 2) ? (first_temp.st_ctime < second_temp.st_ctime) : (first_temp.st_mtime < second_temp.st_mtime))) {
                t = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = t;
                check = 1;
            }
        }
    }
}
