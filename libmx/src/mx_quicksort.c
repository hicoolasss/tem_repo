#include "../inc/libmx.h"

int mx_quicksort(char **arr, int left, int right) {
    if (!arr) {
         return -1;
    }
    int number_of_swaps = 0;

    if (left < right) {
        int temp_left = left;
        int temp_right = right;
        char *current = arr[(temp_right + temp_left) / 2];

        while (temp_left <= temp_right) {
            
            while (mx_strlen(arr[temp_right]) > mx_strlen(current)) {
                temp_right--;
            }
            while (mx_strlen(arr[temp_left]) < mx_strlen(current)) {
                temp_left++;
            }
            if (temp_left <= temp_right) {
                if (mx_strlen(arr[temp_right]) != mx_strlen(arr[temp_left])) {
                    char *temp = arr[temp_left];
                    arr[temp_left] = arr[temp_right];
                    arr[temp_right] = temp;
                    number_of_swaps++;
                }
                temp_right--;
                temp_left++;
            }
        }

        number_of_swaps += mx_quicksort(arr, left, temp_right);
        number_of_swaps += mx_quicksort(arr, temp_left, right);
    }
    return number_of_swaps;
}
