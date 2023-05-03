#include <../inc/header.h>

int mx_sort_args(char **arr, int size, int start) {
    int check = 1;
    char *t;
    int count_of_op = 0;
    while(check) {
        check = 0;
        for (int i = start; i < size - 1; i++) {
            if (mx_strcmp(arr[i], arr[i + 1]) > 0) {
                t = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = t;
                check = 1;
                count_of_op++;
            }
        }
    }
    return count_of_op;
}
