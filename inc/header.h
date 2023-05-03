#ifndef HEADER_H
#define HEADER_H

#include "../inc/libmx.h"
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/ioctl.h>
#include <sys/acl.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>

typedef struct s_flags{
    int without_flags;
    int l;
    int R;
    int one;
    int r;
    int a; 
    int A;
    int T;
    int t;
    int u;
    int c;
    /*int a;
    int A;
    int G;
    int at;
    int e;
    int C;
    int S;*/
}   t_flags;


void standart_ls(int argc, char *argv[], char **strarr, int counter, t_flags flag);
int check_flag(int argc, char*argv[], t_flags *flag, int *temp_check_num);
void ls_R(int argc, char *argv[], int counter, char *path, t_flags flag, int len_dir, bool arg_trans);
void get_cols_rows(char **arr, int counter, int *cols, int * rows, int max_size);
void print_rows(char ** arr, int counter, int rows, int max);
void reverse_sort(char ** arr, int size);
int get_max(char ** arr, int counter);
void ls_long(char **strarr, int counter, t_flags flag, bool arg_trans, int check_count);
void long_out_for_elem(char* name_file, t_flags flag, int max_len_size, int max_len_links, int max_len_usid, int max_len_grid);
void print_acl(char *print);
void ls_time_sort(char **arr, int size, int type_sort);
int mx_sort_args(char **arr, int size, int start);
int mx_sort_link(char **arr, int size);
int mx_sort_files(char **arr, int size);

#endif
