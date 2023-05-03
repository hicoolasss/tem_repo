#include "../inc/libmx.h"

int mx_sqrt(int x) {
    if(x <= 0){
        return 0;
    }    
    double num = 1;
    for(int i = 0; i <= 10000; i++){
        num -= (num * num - x) / (num * 2);
    }
    if(num - (int)num == 0) {
        return (int)num;
    }
    else
        return 0;
}

