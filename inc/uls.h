#include "../libmx/inc/libmx.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <uuid/uuid.h>
#include <pwd.h>
#include <grp.h>
#include <sys/xattr.h>
#include <sys/ioctl.h>
#include <sys/acl.h>
#include <sys/errno.h>
#include <time.h>
#include <string.h>

typedef struct dirent t_dirent;
typedef struct stat t_stat;
typedef struct passwd t_passwd;
typedef struct group t_group;
typedef struct winsize t_winsize;

typedef struct s_file
{
	char *permission;
	char *links;
	char *owner;
	char *group;
	char *bytes;
	char *time;
	
    char* name;
    char* path;
    t_stat stat;
    struct s_file* next; 
}t_file;

t_file *mx_create_node_f(t_stat *statistics, char*permiss, char*name, char*path);
void mx_push_back_f(t_file **files, t_stat *statistics, char*permiss, char*name, char*path);
int mx_list_size_f(t_file *files);
t_file *mx_sort_list_f(t_file *lst, int(*cmp)(const char*, const char*));
t_file* mx_duplicate_list_f(t_file* list);
void mx_clear_list_f(t_file **list);

typedef struct s_flags {
    int a;
    int A;
    int G;
    int l;
    int r;
    int t;
    int c;
    int u;
    int S;
    int T;
    int h;
    int at;
    int e;
    int R;
    int C;
    int one;
    int F;
    int f;
    int m;
}              t_flags;

void mx_output_for_L(char **argv, int fils, int dirs, int*exit_value);
void mx_standart_output(char **argv, int fils, int dirs, int*exit_value);
char* get_permission(t_stat* stat, char* path);
void format_output(t_file *files_s, int show);
