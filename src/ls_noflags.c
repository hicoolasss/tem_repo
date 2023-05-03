#include <../inc/header.h>
#define MAX_SIZE 1000
void standart_ls(int argc, char *argv[], char **strarr, int counter,  t_flags flag){
    bool is_open = false;
    bool check = false;
    int rows = 0;
    int cols = 0;
    int max = 0;
    struct winsize ws;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
    char **arrfiles = (char **)malloc((counter + 1) * sizeof(char *));
    char **arrdir = (char **)malloc((counter + 1) * sizeof(char *));
    char **curdir = (char **)malloc((MAX_SIZE + 1) * sizeof(char *));
    struct stat buff;
    DIR *dir;
    struct dirent *dirent_new;
    bool is_directory = false;
    bool is_add = false;
    bool is_empty = true;
    bool is_error = false;
    int counter_dir = 0;
    int counter_files = 0;
    int counter_curdir = 0;
    for(int i = 1; i < argc; i++){
        is_directory = false;
        check = true;
        is_open = false;
        if((dir = opendir(argv[i])) != NULL){
            is_directory = true;
            arrdir[counter_dir] = mx_strdup(argv[i]);
            counter_dir++;
            is_open = true;
            is_add = true;
        }
        if(is_open){
            closedir(dir);
        }
        if(is_directory){
            continue;
        }
        if(stat(argv[i], &buff) != -1){
            arrfiles[counter_files] = mx_strdup(argv[i]);
            counter_files++;
            is_add = true;
        }
        else{
            is_error = true;
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
    get_cols_rows(arrfiles, counter_files, &cols, &rows, ws.ws_col);
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
    for (int i = 0; i < counter_dir; i++) {
        is_empty = true;
        if(i != 0){
            mx_printchar('\n');
        }
        if(counter_dir > 1 || counter_files >= 1 || is_error){
            mx_printstr(arrdir[i]);     
            mx_printchar(':');   
            mx_printchar('\n');
        }
        counter_curdir = 0;
        is_open = false;
        if((dir = opendir(arrdir[i])) != NULL) {
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
                curdir[counter_curdir] = mx_strdup(dirent_new->d_name);
                counter_curdir++;
            }
            is_open = true;
        }
        if(is_open){
            closedir(dir);
        }
        if(flag.r == 2){
            reverse_sort(curdir, counter_curdir);
        }
        else{
            mx_bubble_sort(curdir, counter_curdir);
        }
        cols = 0;
        rows = 0;
        if(counter_curdir != 0){
            get_cols_rows(curdir, counter_curdir, &cols, &rows, ws.ws_col);
        }
        if(flag.one == 2){
            for (int j = 0; j < counter_curdir; j++) {
                mx_printstr(curdir[j]);
                if(j != counter_curdir - 1){
                    mx_printstr("\n");
                }
                is_empty = false;
            }
        }  
        else{
            max = get_max(curdir, counter_curdir);
            print_rows(curdir, counter_curdir, rows, max);
            if(cols != 0 || rows != 0){
                is_empty = false;
            } 
        }
        if(is_empty){
            continue;
        }
        if(i != counter_dir - 1){
            mx_printchar('\n');
        }
    }
    if(check){
        //mx_del_strarr(&arrdir);
        if(!is_empty)
            mx_printstr("\n");
        return;
    }
    cols = 0;
    rows = 0;
    get_cols_rows(strarr, counter, &cols, &rows, ws.ws_col);
    if(flag.one == 2){
        for (int i = 0; i < counter; i++) {
            mx_printstr(strarr[i]);
            if(i != counter - 1){
                mx_printstr("\n");
            }
        }
    }
    else{
        max = get_max(strarr, counter);
        print_rows(strarr, counter, rows, max); 
    }
    mx_printstr("\n");   
    for(int i = 0; i < counter_files; i++) {
        free(arrfiles[i]);
    }
    free(arrfiles);
    for(int i = 0; i < counter_dir; i++) {
        free(arrdir[i]);
    }
    free(arrdir);
    for(int i = 0; i < counter_curdir; i++) {
        free(curdir[i]);
    }
    free(curdir);
}
