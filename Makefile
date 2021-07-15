# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/17 12:59:07 by ehelmine          #+#    #+#              #
#    Updated: 2021/07/15 13:27:21 by ehelmine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRCS = exit_function.c main.c print_array.c sort_functions.c stat_checks.c \
write_output.c check_files.c write_long_output.c input_check.c write_only_ls.c \
write_long_output_help.c sort_functions_help.c write_output_help.c \
print_long_output.c print_array_help_functions.c

OBJS = exit_function.o main.o print_array.o sort_functions.o stat_checks.o \
write_output.o check_files.o write_long_output.o input_check.o write_only_ls.o \
write_long_output_help.o sort_functions_help.o write_output_help.o \
print_long_output.o print_array_help_functions.o

INCLUDES = includes/ft_printf.h

CFLAGS = -fsanitize=address -g -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	make -C libft/
	@gcc $(CFLAGS) -c $(SRCS) -I includes
	@echo "Sources to objects done"
	gcc $(CFLAGS) -o ft_ls $(OBJS) libft/libft.a
	@echo "Compiling ft_ls done"

clean:
	make clean -C libft/
	@echo "Removing .o files"
	@rm -f $(OBJS)

fclean: clean
	make -C libft/ fclean
	@echo "Removing .a files"
	@rm -f $(NAME)

re: fclean all