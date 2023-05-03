#include <../inc/header.h>

int get_max(char ** arr, int counter){
    int max_current = 0;
    for (int i = 0; i < counter; i++) {       
        if(mx_strlen(arr[i]) >= max_current){
            max_current = mx_strlen(arr[i]);
        }  
    }
    if (max_current % 8 == 0){
        max_current += 8;
    }
    else{
        max_current = 8 - (max_current % 8) + max_current;
    }
    return max_current; 
}
