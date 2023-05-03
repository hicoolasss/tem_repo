#include <../inc/header.h>

static void print_tab(char ** arr, int max, int current_j){
    int count = 0;
    int diff = max - mx_strlen(arr[current_j]);
    if (diff % 8 != 0) {
        count = (diff / 8) + 1;
    }
    else {
        count = diff / 8;
    }
    for (int i = 0; i < count; i++) {
        mx_printchar('\t');
    }
}

void print_rows(char ** arr, int counter, int rows, int max){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < counter; j++) {
            if((j - i) % rows == 0){
                mx_printstr(arr[j]);
                if(j != counter - 1 && j + rows < counter){
                    print_tab(arr, max, j);
                }
            }
        }
        if(i != rows - 1){
            mx_printchar('\n');
        }        
    }
}
