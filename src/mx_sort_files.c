#include "header.h"

int mx_sort_files(char **arr, int size) {
    int check = 1;
    char *t;
    int count_of_op = 0;
    while(check) {
        check = 0;
        for (int i = 0; i < size - 1; i++) {
            DIR *dir1;
            DIR *dir2;
            dir1 = opendir(arr[i]);
            dir2 = opendir(arr[i+1]);
            if(dir1 == NULL && dir2 == NULL) {
                if(mx_strcmp(arr[i], arr[i + 1]) > 0) {
                    t = arr[i];
                    arr[i] = arr[i+1];
                    arr[i+1] = t;
                    check = 1;
                    count_of_op++;
                }
            }
            else if(dir2 == NULL) {
                t = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = t;
                check = 1;
                count_of_op++;
            }
            if(dir1 != NULL) {
                closedir(dir1);
            }
            if(dir2 != NULL) {
                closedir(dir2);
            }
        }
    }
    return count_of_op;
}
