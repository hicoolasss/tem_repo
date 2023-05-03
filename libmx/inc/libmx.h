#ifndef LIBMX_H
#define LIBMX_H

#include <unistd.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <malloc/malloc.h>

void mx_printchar(char c); //+
void mx_print_unicode(wchar_t c);//+
void mx_printstr(const char *s); //+
void mx_print_strarr(char **arr, const char *delim);//+
void mx_printint(int num); //+
double mx_pow(double n, unsigned int pow);//+
int mx_sqrt(int x); //+
char *mx_itoa(int number);//+
void mx_foreach(int *arr, int size, void (*f)(int)); //+
int mx_bubble_sort(char** arr, int size); //+
int mx_quicksort(char **arr, int left, int right); //+
void mx_printerr(const char *s);

int mx_strlen(const char *s); //+
void mx_swap_char(char *s1, char *s2);//+
void mx_str_reverse(char *s); //+
void mx_strdel(char **str); //+
void mx_del_strarr(char ***arr); //+
int mx_get_char_index(const char *str, char c); //+
char *mx_strdup(const char *s1); //+
char *mx_strndup(const char *s1, size_t n);//+
char *mx_strcpy(char *dst, const char *src); //+
char *mx_strncpy(char *dst, const char *src, int len); //+
int mx_strcmp(const char *s1, const char *s2); //+
int mx_strncmp(const char *s1, const char *s2, int n); //не треба
char *mx_strcat(char *restrict s1, const char *restrict s2); //+
char *mx_strstr(const char *haystack, const char *needle);//+
char *mx_strnew(const int size); //+
char *mx_strtrim(const char *str); //+
char *mx_del_extra_spaces(const char *str);//+
char **mx_strsplit(const char *s, char c);//+
char *mx_strjoin(const char *s1, const char *s2);//+
char *mx_file_to_str(const char *file); //+
char *mx_strchr(const char *s, int c);//не треба
bool mx_isalpha(int c);//не треба
bool mx_isdigit(int c);// не треба
bool mx_isspace(char c);// не треба
bool mx_islower(int c);// не треба
bool mx_isupper(int c);//не треба

#endif
