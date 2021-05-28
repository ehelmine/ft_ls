# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/17 12:59:07 by ehelmine          #+#    #+#              #
#    Updated: 2021/05/28 14:10:50 by ehelmine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRCS = exit_function.c main.c print_array.c sort_functions.c stat_checks.c \
try.c check_files.c write_long_output.c

LIBFT_SRCS = $(addprefix libft/, ft_putchar.c ft_putstr.c ft_atoi.c \
ft_strlen.c ft_strcmp.c ft_putnbr.c ft_strdup.c ft_strcpy.c ft_strncpy.c \
ft_strclr.c ft_strcat.c ft_strncmp.c ft_putendl.c ft_strlcat.c ft_bzero.c \
ft_strncat.c ft_strchr.c ft_strrchr.c ft_isalpha.c ft_isdigit.c ft_isascii.c \
ft_isprint.c ft_strstr.c ft_strnstr.c ft_tolower.c ft_toupper.c ft_isalnum.c \
ft_memset.c ft_memcpy.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memmove.c \
ft_strequ.c ft_strnequ.c ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c \
ft_strtrim.c ft_strjoin.c ft_striter.c ft_striteri.c ft_strsplit.c \
ft_strsub.c ft_strmap.c ft_strmapi.c ft_itoa.c ft_putchar_fd.c \
ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstadd.c \
ft_lstdelone.c ft_lstdel.c ft_lstiter.c ft_lstmap.c ft_check_int_len.c \
ft_islower.c ft_isupper.c ft_isspace.c ft_strndup.c get_next_line.c)

OBJS = exit_function.o main.o print_array.o sort_functions.o stat_checks.o \
try.o check_files.o write_long_output.o

LIB = libft/

LIB_A = libft/libft.a

LIBFT_OBJS = $(LIBFT_SRCS:%.c=%.o)

INCLUDES = includes/ft_printf.h

CFLAGS = -g -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	make -C libft
	@gcc $(CFLAGS) -c $(SRCS) -I includes
	@echo "Sources to objects done"
#	gcc -fsanitize=address $(CFLAGS) -o ft_ls $(OBJS) ft_printf/libftprintf.a
	gcc $(CFLAGS) -o ft_ls $(OBJS) ft_printf/libftprintf.a
	@echo "Compiling ft_ls done"

clean:
	make clean -C libft
	@echo "Removing .o files"
	@rm -f $(OBJS)

fclean: clean
	make -C libft fclean
	@echo "Removing .a files"
	@rm -f $(NAME)

re: fclean all