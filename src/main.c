#include <../inc/header.h>

int main(int argc, char *argv[]) {
    char current_dir[256];
    const char *dir_path = ".";
    int dir_len = mx_strlen(dir_path) + 1;
    DIR *directory;
    char **file_array = (char **)malloc((100 + 1) * sizeof(char *));
    int file_count = 0;
    int exit_code = 0;
    struct dirent *entry;
    t_flags flag;
    int flag_num_temp = 0;
    int flag_check = check_flag(argc, argv, &flag, &flag_num_temp);
    bool arg_switch = false;

    if ((directory = opendir(dir_path)) != NULL) {
        mx_strcpy(current_dir, dir_path);
        int check_counter = 0;
        if (!flag_check) {
            read_dir(directory, &entry, &flag, file_array, &file_count);
        } else {
            arg_switch = true;
            sort_args_and_count_errors(argc, argv, file_array, flag_num_temp, &file_count, &check_counter, &exit_code);
        }
        closedir(directory);

        if (file_count > 0) {
            sort_files_and_links(file_array, file_count, flag_check, &flag);
            print_output(argc, argv, file_array, file_count, flag, arg_switch, check_counter);
        }
    }
    free_file_array(file_array, file_count);

    return exit_code;
}

void read_dir(DIR *directory, struct dirent **entry, t_flags *flag, char **file_array, int *file_count) {
    while ((*entry = readdir(directory)) != NULL) {
        if (flag->A == 2) {
            if (mx_strcmp((*entry)->d_name, ".") == 0 || mx_strcmp((*entry)->d_name, "..") == 0) {
                continue;
            }
        }
        if (flag->a != 2 && flag->A != 2) {
            if ((*entry)->d_name[0] == '.') {
                continue;
            }
        }
        if (mx_strcmp((*entry)->d_name, "uls") == 0) {
            continue;
        }
        file_array[*file_count] = mx_strdup((*entry)->d_name);
        (*file_count)++;
    }
}

void sort_args_and_count_errors(int argc, char *argv[], char **file_array, int flag_num_temp, int *file_count, int *check_counter, int *exit_code) {
    mx_sort_args(argv, argc, flag_num_temp);
    for (int i = 1, j = 0; i < argc; i++) {
        struct stat buff;
        int check = stat(argv[i], &buff);
        bool check_ch_dir = true;

        check_ch_dir = handle_dir_check(argv, i, &buff, exit_code, check_ch_dir);

        if (mx_strcmp(argv[i], "-") == 0 && check != 0) {
            print_error(argv[i], errno, exit_code);
        }

        handle_check_value(argv, i, &buff, check, file_array, &j, file_count, check_counter, exit_code, check_ch_dir, flag_num_temp);
    }
}

bool handle_dir_check(char *argv[], int index, struct stat *buff, int *exit_code, bool check_ch_dir) {
    if (((buff->st_mode) & S_IFMT) == S_IFDIR) {
        DIR *dir_temp = opendir(argv[index]);
        if (dir_temp == NULL) {
            print_error(argv[index], errno, exit_code);
            check_ch_dir = false;
        } else {
            closedir(dir_temp);
        }
    }
    return check_ch_dir;
}

void handle_check_value(char *argv[], int index, struct stat *buff, int check, char **file_array, int *j, int *file_count, int *check_counter, int *exit_code, bool check_ch_dir, int flag_num_temp) {
    if ((argv[index][0] != '-' || (argv[index][0] == '-' && mx_strlen(argv[index]) > 1)) && check != 0 && flag_num_temp <= index) {
        print_error(argv[index], errno, exit_code);
        (*check_counter)++;
    }
    if ((argv[index][0] != '-' || (argv[index][0] == '-' && mx_strlen(argv[index]) == 1)) && check == 0 && check_ch_dir) {
        file_array[*j] = mx_strdup(argv[index]);
        (*j)++;
        (*file_count)++;
    }
}

void print_error(char *arg, int errnum, int *exit_code) {
    mx_printerr("uls: ");
    mx_printerr(arg);
    mx_printerr(": ");
    mx_printerr(strerror(errnum));
    mx_printerr("\n");
    *exit_code = EXIT_FAILURE;
}

void sort_files_and_links(char **file_array, int file_count, int flag_check, t_flags *flag) {
    mx_bubble_sort(file_array, file_count);
    if (flag_check) {
        mx_sort_files(file_array, file_count);
    }
    mx_sort_link(file_array, file_count);
    if (flag->t == 2) {
        ls_time_sort(file_array, file_count, ((flag->u == 2) ? 1 : ((flag->c == 2) ? 2 : 0)));
    }
    if (flag->r == 2) {
        reverse_sort(file_array, file_count);
    }
}

void print_output(int argc, char *argv[], char **file_array, int file_count, t_flags flag, bool arg_switch, int check_counter) {
    if (flag.l != 2 && flag.R != 2) {
        standart_ls(argc, argv, file_array, file_count, flag);
    }
    if (flag.l == 2 && flag.R != 2) {
        ls_long(file_array, file_count, flag, arg_switch, check_counter);
    }
    if (flag.R == 2) {
        ls_R(argc, argv, file_count, dir_path, flag, dir_len, arg_switch);
    }
}

void free_file_array(char **file_array, int file_count) {
    for (int i = 0; i < file_count; i++) {
        free(file_array[i]);
    }
    free(file_array);
}
