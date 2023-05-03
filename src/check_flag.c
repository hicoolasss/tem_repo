#include <../inc/header.h>

int check_flag(int argc, char*argv[], t_flags *flag, int *temp_check_num){
    int check_value = 0;
    bool check = false;
    bool one_check = false;
    if(isatty(1) == 0){
        flag->one = 2;
    }
    for (int i = 1; i < argc; i++) {
        if(argv[i][0] != '-' || (argv[i][0] == '-' && mx_strlen(argv[i]) == 1)){
            check_value++;
            *temp_check_num = i;
            break;
        }
        for(int j = 1; j < mx_strlen(argv[i]); j++) {
            check = false;
            if(argv[i][j] == 't') {
                flag->t = 2;
                check = true;
                one_check = true;
            }
            if(argv[i][j] == 'u') {
                flag->u = 2;
                check = true;
                one_check = true;
            }
            if(argv[i][j] == 'c') {
                flag->c = 2;
                check = true;
                one_check = true;
            }
            if(argv[i][j] == 'T') {
                flag->T = 2;
                check = true;
                one_check = true;
            }
            if(argv[i][j] == 'l'){
                flag->l = 2;
                check = true;
                one_check = true;
            }
            if(argv[i][j] == 'R'){
                flag->R = 2;
                check = true;
                one_check = true;
            }
            if(argv[i][j] == '1'){
                flag->one = 2;
                check = true;
                one_check = true;
            }
            if(argv[i][j] == 'r'){
                flag->r = 2;
                check = true;
                one_check = true;
            }
            if(argv[i][j] == 'a'){
                flag->a = 2;
                flag->A = 1;
                check = true;
                one_check = true;
            }
            if(argv[i][j] == 'A'){
                check = true;
                if(flag->a != 2){
                    flag->A = 2;
                    one_check = true;
                }
            }
            char temp[1];
            if(!check){
                mx_printerr("uls: illegal option -- ");
                temp[0] = argv[i][j];
                mx_printerr(temp);
                mx_printerr("\nusage: uls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
                exit(EXIT_FAILURE);
            }
        }        
    }
    if(!one_check){
        flag->without_flags = 2;
    }
    return check_value;
}
