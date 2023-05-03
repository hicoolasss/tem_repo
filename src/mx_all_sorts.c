#include <../inc/header.h>

void reverse_sort(char ** arr, int size){
    int check = 1;
    char *t;
    int count_of_op = 0;
    while(check) {
        check = 0;
        for (int i = 0; i < size - 1; i++) {
            if (mx_strcmp(arr[i], arr[i + 1]) < 0) {
                t = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = t;
                check = 1;
                count_of_op++;
            }
        }
    }
}

void sort_c(char ** arr, int size){
    int check = 1;
    char *t;
    int count_of_op = 0;
    while(check) {
        check = 0;
        for (int i = 0; i < size - 1; i++) {
            if (mx_strcmp(arr[i], arr[i + 1]) < 0) {
                t = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = t;
                check = 1;
                count_of_op++;
            }
        }
    }
}
