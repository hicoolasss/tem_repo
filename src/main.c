#include <../inc/header.h>

int main(int argc, char *argv[]) {
    char curDir[256];
    char *path = ".";
    int len_dir = mx_strlen(path) + 1;
    DIR *dir;
    char **strarr = (char **)malloc((100 + 1) * sizeof(char *));
    int counter = 0;
    int error = 0;
    struct dirent *dirent_new;
    t_flags flag;
    int temp_check_num = 0;
    int check_value = check_flag(argc, argv, &flag, &temp_check_num);
    bool arg_trans = false;
    if((dir = opendir(path)) != NULL) {
        mx_strcpy(curDir, path);
        int check_count = 0;
        if(!check_value) {
            while((dirent_new = readdir(dir)) != NULL){   
                if(flag.A == 2){
                    if(mx_strcmp(dirent_new->d_name, ".") == 0|| mx_strcmp(dirent_new->d_name, "..") == 0){
                        continue;
                    }  
                } 
                if(flag.a !=2 && flag.A != 2){
                    if(dirent_new->d_name[0] == '.'){
                        continue;
                    }
                }
                if(mx_strcmp(dirent_new->d_name, "uls") == 0){
                    continue;
                }
                strarr[counter] = mx_strdup(dirent_new->d_name);
                counter++;
            }
        }
        else {
            arg_trans = true;
            mx_sort_args(argv, argc, temp_check_num);
            for(int i = 1, j = 0; i < argc; i++) {
                struct stat buff;
                int check = stat(argv[i], &buff);
                bool check_ch_dir = true;
                if(((buff.st_mode) & S_IFMT) == S_IFDIR) {
                    DIR* dir_temp = opendir(argv[i]);
                    if(dir_temp == NULL) {
                        mx_printerr("uls: ");
                        mx_printerr(argv[i]);
                        mx_printerr(": ");
                        mx_printerr(strerror(errno)); 
                        mx_printerr("\n");
                        error = EXIT_FAILURE;
                        check_ch_dir = false;
                    }
                    else {
                        closedir(dir_temp);
                    }
                }
                if(mx_strcmp(argv[i], "-") == 0 && check != 0) {
                    mx_printerr("uls: ");
                    mx_printerr(argv[i]);
                    mx_printerr(": ");
                    mx_printerr(strerror(errno)); 
                    mx_printerr("\n");
                    error = EXIT_FAILURE;
                }
                if((argv[i][0] != '-' || (argv[i][0] == '-' && mx_strlen(argv[i]) > 1)) && check != 0 && temp_check_num <= i) {
                    mx_printerr("uls: ");
                    mx_printerr(argv[i]);
                    mx_printerr(": ");
                    mx_printerr(strerror(errno)); 
                    mx_printerr("\n");
                    error = EXIT_FAILURE;
                    check_count++;
                }
                if((argv[i][0] != '-' || (argv[i][0] == '-' && mx_strlen(argv[i]) == 1)) && check == 0 && check_ch_dir) {
                    strarr[j] = mx_strdup(argv[i]);
                    j++;
                    counter++;
                }
            }
        }
        closedir(dir);
        if(counter > 0) {
            mx_bubble_sort(strarr, counter);
            if(check_value) {
                mx_sort_files(strarr, counter);
            }
            mx_sort_link(strarr, counter);
            if(flag.t == 2) {
                ls_time_sort(strarr, counter, ((flag.u == 2) ? 1 : ((flag.c == 2) ? 2 : 0)));
            }
            if(flag.r == 2) {
                reverse_sort(strarr, counter);
            }
            if(flag.l != 2 && flag.R !=2) {
                standart_ls(argc, argv, strarr, counter, flag);
            }
            if(flag.l == 2 && flag.R != 2) {
                ls_long(strarr, counter, flag, arg_trans, check_count);
            }
            if(flag.R == 2) {
                ls_R(argc, argv, counter, path, flag, len_dir, arg_trans);
            }
        }
    }
    for(int i = 0; i < counter; i++) {
        free(strarr[i]);
    }
    free(strarr);

    return error;
}