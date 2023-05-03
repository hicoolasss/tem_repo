#include "header.h"
static int total_for_long(char* name_file, int* max_len_size, int* max_len_links, int* max_len_usid, int* max_len_grid) {
    struct stat buff;
    lstat(name_file, &buff);
    struct passwd* temp_usid = getpwuid(buff.st_uid);
    if(temp_usid) {
        if(*max_len_usid < mx_strlen(temp_usid->pw_name)) {
            *max_len_usid = mx_strlen(temp_usid->pw_name);
        }
    }
    else {
        char* temp_us_str = mx_itoa(buff.st_uid);
        if(*max_len_usid < mx_strlen(temp_us_str)) {
            *max_len_usid = mx_strlen(temp_us_str);
        }
        free(temp_us_str);
    }
    struct group* temp_grid = getgrgid(buff.st_gid);
    if(temp_grid) {
        if(*max_len_grid < mx_strlen(temp_grid->gr_name)) {
            *max_len_grid = mx_strlen(temp_grid->gr_name);
        }
    }
    else {
        char* temp_gr_str = mx_itoa(buff.st_gid);
        if(*max_len_grid < mx_strlen(temp_gr_str)) {
            *max_len_grid = mx_strlen(temp_gr_str);
        }
        free(temp_gr_str);
    }
    char* temp1 = mx_itoa(buff.st_size);
    char* temp2 = mx_itoa(buff.st_nlink);
    if(*max_len_size < mx_strlen(temp1)) {
        *max_len_size = mx_strlen(temp1);
    }
    if(*max_len_links < mx_strlen(temp2)) {
        *max_len_links = mx_strlen(temp2);
    }
    free(temp1);
    free(temp2);
    return buff.st_blocks;
}

void ls_long(char **strarr, int counter, t_flags flag, bool arg_trans, int check_out) {
    if(!arg_trans) {
        int total = 0;
        int max_len_size = 0;
        int max_len_links = 0;
        int max_len_usid = 0;
        int max_len_grid = 0;
        for(int i = 0; i < counter; i++) {
            total += total_for_long(strarr[i], &max_len_size, &max_len_links, &max_len_usid, &max_len_grid);
        }
        if(counter != 0) {
            mx_printstr("total ");
            mx_printint(total);
            mx_printstr("\n");
        }
        for(int i = 0; i < counter; i++) {
            long_out_for_elem(strarr[i], flag, max_len_size, max_len_links, max_len_usid, max_len_grid);
        }
    }
    else {
        for(int i = 0; i < counter; i++) {
            DIR* dir;
            if((dir = opendir(strarr[i])) != NULL) {
                struct stat some_dir;
                lstat(strarr[i], &some_dir);
                if( !(((some_dir.st_mode) & S_IFMT) == S_IFLNK) ) {
                    int temp_counter = 0;
                    struct dirent *dirent_new;
                    char **temp_strarr = (char **)malloc((100) * sizeof(char *));
                    for(int j = 0; j < 100; j++) {
                        temp_strarr[j] = malloc( 50 * sizeof(char) );
                    }
                    if(i != 0) {
                        mx_printstr("\n");
                    }
                    if(counter != 1 || check_out > 0) {
                        mx_printstr(strarr[i]);
                        mx_printstr(":\n");
                    }
                    while((dirent_new = readdir(dir)) != NULL) {   
                        if(dirent_new->d_name[0] == '.') {
                            continue;
                        }
                        mx_strcpy(temp_strarr[temp_counter], strarr[i]);
                        temp_strarr[temp_counter] = mx_strcat(temp_strarr[temp_counter], "/");
                        temp_strarr[temp_counter] = mx_strcat(temp_strarr[temp_counter], dirent_new->d_name);
                        temp_counter++;
                    } 
                    closedir(dir);
                    mx_bubble_sort(temp_strarr, temp_counter);
                    if(flag.t == 2) {
                        ls_time_sort(temp_strarr, temp_counter, ((flag.u == 2) ? 1 : 0) );
                    }
                    if(flag.r == 2) {
                        reverse_sort(temp_strarr, temp_counter);
                    }
                    ls_long(temp_strarr, temp_counter, flag, 0, ((temp_counter) ? (1) : (0)));
                    for(int j = 0; j < 100; j++) {
                        free(temp_strarr[j]);
                    }
                    free(temp_strarr);
                    temp_strarr = NULL;
                }
                else {
                    long_out_for_elem(strarr[i], flag, -1, -1, -1, -1);
                }
            }
            else {
                long_out_for_elem(strarr[i], flag, -1, -1, -1, -1);
            }
        }
    }
}
