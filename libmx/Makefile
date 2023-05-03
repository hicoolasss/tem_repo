CFLG	=	-std=c11 -Wall -Wextra -Werror -Wpedantic -g

SRCD	=	src
INCD	=	inc
OBJD	=	obj

INC		=	libmx.h
INCS	=	inc/libmx.h

SRC		= 	mx_printerr.c mx_bubble_sort.c  \
			mx_del_strarr.c mx_file_to_str.c mx_foreach.c \
			mx_hex_to_nbr.c mx_isalpha.c mx_isdigit.c mx_islower.c mx_itoa.c \
			mx_isspace.c mx_isupper.c \
			mx_pow.c mx_print_strarr.c mx_print_unicode.c mx_printchar.c mx_printint.c mx_printstr.c \
			mx_quicksort.c mx_get_char_index.c \
			mx_sqrt.c mx_str_reverse.c mx_strcat.c mx_strcmp.c mx_strcpy.c mx_strdel.c \
			mx_strdup.c mx_strjoin.c mx_strlen.c mx_strncmp.c mx_strncpy.c mx_strndup.c mx_strnew.c \
			mx_strstr.c mx_strchr.c mx_strtrim.c mx_swap_char.c
	
SRCS	=	src/*.c
OBJS	=	$(addprefix $(OBJD)/, $(SRC:%.c=%.o))

all: install
	
install: libmx.a

libmx.a: $(OBJS)
	@ar rcs $@ $^

$(OBJD)/%.o: $(SRCD)/%.c $(INCS)
	@clang $(CFLG) -c $< -o $@ -I$(INCD)

$(OBJS): | $(OBJD)

$(OBJD):
	@mkdir -p $@

clean:
	@rm -rf $(OBJD)

uninstall: clean
	@rm -rf libmx.a

reinstall: uninstall install