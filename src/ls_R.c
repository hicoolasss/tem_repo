#include <../inc/header.h>


static void recursivly_function(char *namedir, t_flags flag, int len_dir, bool arg_trans, int temp_counter){
    char * current_namedir = NULL;
    char namedir_print[256];
    bool is_slash = false;
    namedir_print[0] = '.';
    bool is_open = false;
    int rows = 0;
    int cols = 0;
    int max = 0;
    struct winsize ws;
    bool need_rec;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
    int counter_namedir_print = 1;
    namedir_print[counter_namedir_print] = '\0';
    if(namedir[0] == '.' && namedir[1] == '.' && namedir[2] == '/'){
        for (int i = 3; i < mx_strlen(namedir); i++) {
            if(namedir[i] == '/'){
                is_slash = true;
            }
            if(!is_slash){
                continue;
            }      
            namedir_print[counter_namedir_print] = namedir[i];
            counter_namedir_print++;
            namedir_print[counter_namedir_print] = '\0';
        }
    }
    else{
        mx_strcpy(namedir_print, namedir);
    }
    DIR *dir;
    char **strarr = (char **)malloc((1000 + 1) * sizeof(char *));
    int counter = 0;
    struct dirent *dirent_new;
    //mx_printstr("\n");
    //mx_printstr(namedir);
    //mx_printstr("\n");
    if((dir = opendir(namedir)) != NULL) {
        while((dirent_new = readdir(dir)) != NULL){   
            //if(dirent_new->d_name[0] == '.'){
            //    continue;
            //}
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
        closedir(dir);
        if(flag.r == 2){
            reverse_sort(strarr, counter);
        }
        else{
            mx_bubble_sort(strarr, counter);
        }
        is_open = true;
    }
    if(!is_open){
        closedir(dir);
    }

    if(mx_strcmp(namedir_print, ".") != 0 && temp_counter > 1){
        mx_printstr(namedir_print);     
        mx_printchar(':');   
        mx_printchar('\n');
    }
    if(counter != 0){
        get_cols_rows(strarr, counter, &cols, &rows, ws.ws_col);
    }
    if(flag.l == 2) {
        if(mx_strlen(namedir) >= len_dir) {
            if(!arg_trans) {
                for(int i = 0; i < len_dir; i++) {
                    namedir++;
                }
            }
            char** temp_strarr = malloc((1000) * sizeof(char *));
            for(int i = 0; i < counter; i++) {
                temp_strarr[i] = mx_strnew((mx_strlen(strarr[i]) + mx_strlen(namedir) + 1) * 100);
                temp_strarr[i] = mx_strcpy(temp_strarr[i], namedir);
            }
            for(int i = 0; i < counter; i++) {
                temp_strarr[i] = mx_strcat(temp_strarr[i], "/");
                temp_strarr[i] = mx_strcat(temp_strarr[i], strarr[i]);
            }
            if(!arg_trans) {
                for(int i = 0; i < len_dir; i++) {
                    namedir--;
                }
            }
            ls_long(temp_strarr, counter, flag, 0, 0);
            for(int i = 0; i < counter; i++) {
                free(temp_strarr[i]);
            }
            free(temp_strarr);
        }
        else {
            ls_long(strarr, counter, flag, 0, 0);
        }
    }
    else if(flag.one == 2){
        for (int i = 0; i < counter; i++) {
            mx_printstr(strarr[i]);
            if(i != counter - 1){
                mx_printstr("\n");
            }
            if(i == counter - 1){
                mx_printchar('\n');
            }
        }
    }
    else{
        max = get_max(strarr, counter);
        print_rows(strarr, counter, rows, max); 
        if(cols != 0 || rows !=0){
            mx_printchar('\n');
        }
    }
    char *temp_namedir = NULL;
    for (int i = 0; i < counter; i++) {
        is_open = false;
        if(namedir[mx_strlen(namedir) - 1] != '/'){
            temp_namedir = mx_strjoin(namedir, "/");
            current_namedir = mx_strjoin(temp_namedir, strarr[i]);
            free(temp_namedir);
        }
        else{
            current_namedir = mx_strjoin(namedir, strarr[i]);
        }
        //mx_printstr(current_namedir);
        
        if((dir = opendir(current_namedir)) != NULL){
            need_rec = true;
            if(current_namedir[mx_strlen(current_namedir) - 1] == '.'
            && current_namedir[mx_strlen(current_namedir) - 2] == '/'){
                need_rec = false;
            }
            if (current_namedir[mx_strlen(current_namedir) - 1] == '.' 
            && current_namedir[mx_strlen(current_namedir) - 2] == '.'
            && current_namedir[mx_strlen(current_namedir) - 3] == '/'){
                need_rec = false; 
            
            }
            if(need_rec){
                mx_printchar('\n');
                recursivly_function(current_namedir, flag, len_dir, arg_trans, temp_counter);
                is_open = true;
            }
        }
        if(is_open){
            closedir(dir);
        }
        
    }
    free(current_namedir);
    for(int i = 0; i < counter; i++) {
        free(strarr[i]);
    }
    free(strarr);
}








void ls_R(int argc, char *argv[], int counter, char *path, t_flags flag, int len_dir, bool arg_trans){
    bool is_open = false;
    bool check = false;
    char **arrfiles = (char **)malloc((counter + 1) * sizeof(char *));
    char **arrdir = (char **)malloc((counter + 1) * sizeof(char *));
    struct stat buff;
    DIR *dir;
    bool is_directory = false;
    int counter_dir = 0;
    int counter_files = 0;
    int rows = 0;
    int cols = 0;
    int max = 0;
    struct winsize ws;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
    for(int i = 1; i < argc; i++){
        is_directory = false;
        if(argv[i][0] == '-' && mx_strlen(argv[i]) > 1){
            continue;
        }
        check = true;
        if((dir = opendir(argv[i])) != NULL){
            is_directory = true;
            arrdir[counter_dir] = mx_strdup(argv[i]);
            counter_dir++;
            is_open = true;
            closedir(dir);
        }
        if(is_directory){
            continue;
        }
        if(stat(argv[i], &buff) != -1){
            arrfiles[counter_files] = mx_strdup(argv[i]);
            counter_files++;
            
        }   
    }
    if(counter_files > 0){
        if(flag.r == 2){
            reverse_sort(arrfiles, counter_files);
        }
        else{
            mx_bubble_sort(arrfiles, counter_files);
        }
    }
    if(counter_dir > 0){
        if(flag.r == 2){
            reverse_sort(arrdir, counter_dir);
        }
        else{
            mx_bubble_sort(arrdir, counter_dir);
        }
    }
    if(counter_files != 0){
        get_cols_rows(arrfiles, counter_files, &cols, &rows, ws.ws_col);
    }
    if(flag.one == 2){
        for (int i = 0; i < counter_files; i++) {
            mx_printstr(arrfiles[i]);
            if(i != counter_files - 1){
                mx_printstr("\n");
            }
        }
    }
    else{
        max = get_max(arrfiles, counter_files);
        print_rows(arrfiles, counter_files, rows, max); 
    }
    if(counter_files != 0 && counter_dir != 0){
        mx_printchar('\n');
        mx_printchar('\n');
    }
    if(counter_files != 0 && counter_dir == 0){
        mx_printchar('\n');
    }
    if(!check){
        recursivly_function(path, flag, len_dir, arg_trans, counter);
    }
    else {
        if(counter_dir > 0) {
            for (int i = 0; i < counter_dir; i++) {
                recursivly_function(arrdir[i], flag, len_dir, arg_trans, counter);
                if(counter_dir > 1 && counter_dir - 1 != i){
                    mx_printchar('\n');
                }
            }
        }
    }
}
