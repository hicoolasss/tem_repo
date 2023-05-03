#include <../inc/header.h>

int mx_sort_link(char **arr, int size) {
    int check = 1;
    char *t;
    int count_of_op = 0;
    while(check) {
        check = 0;
        for (int i = 0; i < size - 1; i++) {
            struct stat first;
            struct stat second;
            lstat(arr[i], &first);
            lstat(arr[i+1], &second);
            if( (((first.st_mode) & S_IFMT) == S_IFLNK) && (((second.st_mode) & S_IFMT) == S_IFLNK) ) {
                if (mx_strcmp(arr[i], arr[i + 1]) > 0) {
                    t = arr[i];
                    arr[i] = arr[i+1];
                    arr[i+1] = t;
                    check = 1;
                    count_of_op++;
                }
            }
            else if(((second.st_mode) & S_IFMT) == S_IFLNK) {
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
