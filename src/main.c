#include "../inc/uls.h"

void handle_l_flag(int argc, const char **argv, int *exit_value);
void handle_no_flag(int argc, const char **argv, int *exit_value);

static int set_no_errors(const char** argv, int argc, int spec, char ***errors, char***correct)
{
    t_stat *statistics1 = NULL;
    int counter = 0;

    for (int i = spec; i < argc; i++) {
        statistics1 = (t_stat *)malloc(sizeof(t_stat));
        if (lstat(argv[i], statistics1) == -1) {
            counter++;
        }
        free(statistics1);
        statistics1 = NULL;
    }

    if (counter == 0) {
        return 0;
    }

    int correct_size = argc - spec - counter;
    if (correct_size != 0) {
        *correct = (char**)malloc(sizeof(char*) * correct_size);
        for (int i = 0; i < correct_size; ++i) {
            (*correct)[i] = mx_strnew(256);
        }
    }

    *errors = (char**)malloc(sizeof(char*) * counter);
    for (int i = 0; i < counter; ++i) {
        (*errors)[i] = mx_strnew(256);
    }

    int fd_correct = 0;
    int fd_error = 0;
    for (int i = spec; i < argc; i++) {
        statistics1 = (t_stat *)malloc(sizeof(t_stat));
        if (lstat(argv[i], statistics1) != -1) {
            if (correct_size != 0) {
                (*correct)[fd_correct++] = mx_strdup(argv[i]);
            }
        } else {
            (*errors)[fd_error++] = mx_strdup(argv[i]);
        }
        free(statistics1);
        statistics1 = NULL;
    }

    return counter;
}

static char** get_file_array(int argc, const char** argv, int spec, int* fils, int* dirs, int iflnk)
{
    int size = argc - spec;
    char** files = malloc(sizeof(char*) * (size + 1));
    t_stat * statistics1 = NULL;
    t_stat * statistics2 = NULL;

    for (int i = 0; i < size; i++) {
        files[i] = mx_strdup(argv[i + spec]);
    }
    files[size] = NULL;

    for (int i = 0; i < size; ++i) {
        statistics1 = (t_stat *)malloc(sizeof(t_stat));
        lstat(files[i], statistics1);

        if (iflnk == 0 ? !S_ISDIR(statistics1->st_mode) : !S_ISDIR(statistics1->st_mode) && !S_ISLNK(statistics1->st_mode)) {
            (*fils)++;
        } else {
            (*dirs)++;
        }

        free(statistics1);
        statistics1 = NULL;
    }

    for (int j = 0; j < size; j++) {
        for (int i = 0; i < size - 1; ++i) {
            statistics1 = (t_stat *)malloc(sizeof(t_stat));
            lstat(files[i], statistics1);
            statistics2 = (t_stat *)malloc(sizeof(t_stat));
            lstat(files[i + 1], statistics2);

            if (iflnk == 0 ? S_ISDIR(statistics1->st_mode) && !S_ISDIR(statistics2->st_mode) :
                (S_ISDIR(statistics1->st_mode) || S_ISLNK(statistics1->st_mode)) && (!S_ISDIR(statistics2->st_mode) && !S_ISLNK(statistics2->st_mode))) {
                char* temp = files[i];
                files[i] = files[i + 1];
                files[i + 1] = temp;
            }

            free(statistics1);
            statistics1 = NULL;
            free(statistics2);
            statistics2 = NULL;
        }
    }

    for (int j = 0; j < *fils; j++) {
        for (int i = 0; i < *fils - 1; i++) {
            if (mx_strcmp(files[i], files[i + 1]) > 0) {
                char* temp = files[i];
                files[i] = files[i + 1];
                files[i + 1] = temp;
            }
        }
    }

    for (int j = 0; j < *dirs; j++) {
        for (int i = *fils; i < size - 1; i++) {
            if (mx_strcmp(files[i], files[i + 1]) > 0) {
                char* temp = files[i];
                files[i] = files[i + 1];
                files[i + 1] = temp;
            }
        }
    }

    return files;
}

int main(int argc, char const *argv[]) {
    t_flags flags;
    int exit_value = 0;

    int i = 1;
    while (i != argc && argv[i][0] == '-') {
        for (int j = 1; j < mx_strlen(argv[i]); ++j) {
            if (argv[i][j] == 'l')
                flags.l = 1;
            else {
                mx_printerr("uls: illegal option -- ");
                mx_printerr(&argv[i][j]);
                mx_printerr("\nusage: uls [-l] [file ...]\n");
                return 1;
            }
        }
        i++;
    }

    if (flags.l == 1) {
        handle_l_flag(argc, argv, &exit_value);
    } else {
        handle_no_flag(argc, argv, &exit_value);
    }

    return exit_value;
}

void handle_l_flag(int argc, const char **argv, int *exit_value) {
    int fils = 0, dirs = 0;
    char **errors = NULL;
    char **correct = NULL;
    char **files = NULL;

    int is_wrong = set_no_errors(argv, argc, 2, &errors, &correct);
    if (is_wrong == 0) {
        files = get_file_array(argc, argv, 2, &fils, &dirs, 0);
        Flag_l(files, fils, dirs, exit_value);
    } else {
        for (int i = 0; errors[i] != NULL; i++) {
            mx_printerr("uls: ");
            mx_printerr(errors[i]);
            mx_printerr(": No such file or directory\n");
            *exit_value = 1;
        }
    }

    if (files != NULL) mx_del_strarr(&files);
    if (correct != NULL) mx_del_strarr(&correct);
    if (errors != NULL) mx_del_strarr(&errors);
}

void handle_no_flag(int argc, const char **argv, int *exit_value) {
    int fils = 0, dirs = 0;
    char **errors = NULL;
    char **correct = NULL;
    char **files = NULL;

    int is_wrong = set_no_errors(argv, argc, 1, &errors, &correct);
    if (is_wrong == 0) {
        files = get_file_array(argc, argv, 1, &fils, &dirs, 1);
        mx_standart_output(files, fils, dirs, exit_value);
    } else {
        for (int i = 0; errors[i] != NULL; i++) {
            mx_printerr("uls: ");
            mx_printerr(errors[i]);
            mx_printerr(": No such file or directory\n");
            *exit_value = 1;
        }
    }

    if (files != NULL) mx_del_strarr(&files);
    if (correct != NULL) mx_del_strarr(&correct);
    if (errors != NULL) mx_del_strarr(&errors);
}
