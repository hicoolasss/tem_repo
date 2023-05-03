#include <../inc/header.h>

void get_cols_rows(char **arr, int counter, int *cols, int * rows, int max_size){
    *rows = 1;
    int max = get_max(arr, counter);
    if(max_size / max != 0){
        *cols = max_size / max;
    }
    else {
        *cols = 1;
    }
    if (max * (*cols) > max_size && *cols != 1) {
        *cols -= 1;
    }
    if (counter * max > max_size) {
        *rows = counter / *cols;
        if (*rows == 0 || counter % (*cols) != 0) {
            *rows += 1;
        }
    }
}
