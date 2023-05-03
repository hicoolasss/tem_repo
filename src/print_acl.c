#include "header.h"

bool check_blk(mode_t check) { return ((check) & S_IFMT) == S_IFBLK; }
bool check_chr(mode_t check) { return ((check) & S_IFMT) == S_IFCHR; }
bool check_dir(mode_t check) { return ((check) & S_IFMT) == S_IFDIR; }
bool check_lnk(mode_t check) { return ((check) & S_IFMT) == S_IFLNK; }
bool check_sock(mode_t check) { return ((check) & S_IFMT) == S_IFSOCK; }
bool check_fifo(mode_t check) { return ((check) & S_IFMT) == S_IFIFO; }
bool check_wht(mode_t check) { return ((check) & S_IFMT) == S_IFWHT; }

bool check_irusr(mode_t check) { return (S_IRUSR & check); }
bool check_iwusr(mode_t check) { return (S_IWUSR & check); }
bool check_ixusr(mode_t check) { return (S_IXUSR & check); }
bool check_irgrp(mode_t check) { return (S_IRGRP & check); }
bool check_iwgrp(mode_t check) { return (S_IWGRP & check); }
bool check_ixgrp(mode_t check) { return (S_IXGRP & check); }
bool check_iroth(mode_t check) { return (S_IROTH & check); }
bool check_iwoth(mode_t check) { return (S_IWOTH & check); }
bool check_ixoth(mode_t check) { return (S_IXOTH & check); }

bool check_isuid(mode_t check) { return (S_ISUID & check); }
bool check_isgid(mode_t check) { return (S_ISGID & check); }
bool check_isvtx(mode_t check) { return (S_ISVTX & check); }

static char check_file_acl(char *name_file) {
    acl_t check_acl;
    if ((check_acl = acl_get_file(name_file, ACL_TYPE_EXTENDED))) {
        acl_free(check_acl);
        return ('+');
    }
    if (listxattr(name_file, NULL, 0, XATTR_NOFOLLOW) > 0) {
        return ('@');
    }
    return (' ');
}

static char check_file_per(char *print) {
    struct stat buff;
    lstat(print, &buff);
    if (check_dir(buff.st_mode)) {
        return 'd';
    }
    else if (check_lnk(buff.st_mode)) {
        return 'l';
    }
    else if (check_blk(buff.st_mode)) {
        return 'b';
    }
    else if (check_chr(buff.st_mode)) {
        return 'c';
    }
    else if (check_fifo(buff.st_mode)) {
        return 'p';
    }
    else if (check_sock(buff.st_mode)) {
        return 's';
    }
    else if (check_wht(buff.st_mode)) {
        return 'w';
    }
    else {
        return '-';
    }
}

static char check_file_s_chmode(char temp_char) {
    if(temp_char != '-') {
        return temp_char = 's';
    }
    else {
        return temp_char = 'S';
    }
}

static char check_file_t_chmode(char temp_char) {
    if(temp_char != '-') {
        return temp_char = 't';
    }
    else {
        return temp_char = 'T';
    }
}

void print_acl(char *print) {
    struct stat buff;
    int i = lstat(print, &buff);
    char acl_of_file[12];
    acl_of_file[0] = check_file_per(print);
    acl_of_file[1] = check_irusr(buff.st_mode) ? 'r' : '-';
    acl_of_file[2] = check_iwusr(buff.st_mode) ? 'w' : '-';
    acl_of_file[3] = check_ixusr(buff.st_mode) ? 'x' : '-';
    acl_of_file[4] = check_irgrp(buff.st_mode) ? 'r' : '-';
    acl_of_file[5] = check_iwgrp(buff.st_mode) ? 'w' : '-';
    acl_of_file[6] = check_ixgrp(buff.st_mode) ? 'x' : '-';
    acl_of_file[7] = check_iroth(buff.st_mode) ? 'r' : '-';
    acl_of_file[8] = check_iwoth(buff.st_mode) ? 'w' : '-';
    acl_of_file[9] = check_ixoth(buff.st_mode) ? 'x' : '-';
    acl_of_file[10] = check_file_acl(print);
    acl_of_file[11] = '\0';
    check_isuid(buff.st_mode) ? acl_of_file[3] = check_file_s_chmode(acl_of_file[3]) : 0;
    check_isgid(buff.st_mode) ? acl_of_file[6] = check_file_s_chmode(acl_of_file[6]) : 0;
    check_isvtx(buff.st_mode) ? acl_of_file[9] = check_file_t_chmode(acl_of_file[9]) : 0;
    while(acl_of_file[i]) {
        mx_printchar(acl_of_file[i]);
        i++;
    }
    mx_printchar(' ');
}
