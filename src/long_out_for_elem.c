#include "header.h"

void long_out_for_elem(char* name_file, t_flags flag, int max_len_size, int max_len_links, int max_len_usid, int max_len_grid) {
    print_acl(name_file);
    struct stat buff;
    lstat(name_file, &buff);
    char* temp_str1 = mx_itoa(buff.st_nlink);
    for(int i = 0; i < max_len_links - mx_strlen(temp_str1); i++) {
        mx_printstr(" ");
    }
    mx_printstr(temp_str1);
    mx_printstr(" ");
    while(mx_get_char_index(name_file, '/') != -1) {
        name_file = mx_strchr(name_file, '/');
        name_file++;
    }
    struct passwd* temp = getpwuid(buff.st_uid);
    char* temp_us_id = mx_itoa(buff.st_uid);
    
    if(temp) {
        for(int i = 0; i < max_len_usid - mx_strlen(temp->pw_name); i++ ) {
            mx_printchar(' ');
        }
        mx_printstr(temp->pw_name);
    }
    else {
        for(int i = 0; i < max_len_usid - mx_strlen(temp_us_id); i++) {
            mx_printchar(' ');
        }
        mx_printstr(temp_us_id);
    }
    mx_printstr("  ");
    struct group* temp1 = getgrgid(buff.st_gid);
    char* temp_str2 = mx_itoa(buff.st_gid);
    if(temp1) {
        for(int i = 0; i < max_len_grid - mx_strlen(temp1->gr_name); i++) {
            mx_printchar(' ');
        }
        mx_printstr(temp1->gr_name);
    }
    else {
        for(int i = 0; i < max_len_grid - mx_strlen(temp_str2); i++) {
            mx_printchar(' ');
        }
        mx_printstr(temp_str2);
    }
    char* temp_str3 = mx_itoa(buff.st_size);
    mx_printstr("  ");
    for(int i = 0; i < max_len_size - mx_strlen(temp_str3); i++) {
        mx_printstr(" ");
    }
    mx_printstr(temp_str3);
    mx_printstr(" ");
    char* temp_str = mx_strnew(mx_strlen(ctime((flag.u == 2) ? (&buff.st_atime) : ((flag.c == 2) ? (&buff.st_ctime) : (&buff.st_mtime)))) - ((flag.T == 2) ? 1 : 1));
    temp_str = mx_strncpy(temp_str, ctime((flag.u == 2) ? (&buff.st_atime) : ((flag.c == 2) ? (&buff.st_ctime) : (&buff.st_mtime))), mx_strlen(ctime((flag.u == 2) ? (&buff.st_atime) : ((flag.c == 2) ? (&buff.st_ctime) : (&buff.st_mtime)))) - ((flag.T == 2) ? 1 : 1));
    int temp_counter = 0;
    while(*temp_str != ' ') {
        temp_str++;
        temp_counter++;
    }
    temp_str++;
    temp_counter++;
    for(int i = 0; i < 7; i++) {
        mx_printchar(*temp_str);
        temp_str++;
        temp_counter++;
    }
    for(int i = 0; i < 9; i++) {
        temp_str++;
        temp_counter++;
    }
    mx_printstr(" ");
    mx_printstr(temp_str);
    mx_printstr(" ");
    mx_printstr(name_file);
    char *temp_buf = NULL;
    ssize_t check_num = 0;
    ssize_t len_buf = 0;

    len_buf = buff.st_size == 0 ? 100 : buff.st_size + 1;
    temp_buf = mx_strnew(len_buf);
    check_num = readlink(name_file, temp_buf, len_buf);
    if (check_num >= 0)
        mx_printstr(" -> ");
        mx_printstr(temp_buf);
    mx_strdel(&temp_buf);
    mx_printstr("\n");
    for(int i = 0; i < temp_counter; i++) {
        temp_str--;
    }
    free(temp_str);
    free(temp_str1);
    free(temp_str2);
    free(temp_str3);
    free(temp_us_id);
}
