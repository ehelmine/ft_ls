/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 19:04:42 by ehelmine          #+#    #+#             */
/*   Updated: 2021/06/01 19:35:55 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <stdarg.h>
# include <string.h>
# include <stdlib.h>
# include "../libft/includes/libft.h"
# include "../ft_printf/includes/ft_printf.h"
#include <sys/stat.h>
#include <sys/param.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <dirent.h>
#include <time.h>
#include <errno.h>
#define MAX_LINES 10000

typedef	struct s_all
{
		char input_arr[MAX_LINES][500];
		char **not_exist;
		char **files;
		char **directories;
		int a_flag;
		int l_flag;
		int reverse_flag;
		int big_r_flag;
		int t_flag;
		int no_flags;
		int x;
		int xx;
		int num_no;
		int num_file;
		int num_dir;
		int p;
		char *tmp;
		int i;
		int links_len;
		int size_len;
		char *empty;
		char *empty2;
		int blocks;
		int check;
		int files_in_dir;
		char *temp;
		int o;
}				t_all;

int		ft_exit_call(int i, char c);

int		check_regular_file(const char *str);

int		check_directory(const char *file, const char *path, t_all *all);

void	set_values_to_zero(t_all *all);

int	check_flags(t_all *all, int argc);

void	check_if_null(void *ptr);

int	malloc_for_other_input(t_all *all, int i, int argc);

int loop_other_input(t_all *all, int i, int argc);

int	open_and_write_directory(t_all *all, const char *directory,
	const char *path);

char	**open_directory(const char *directory, const char *path, char *dir_tmp,
	t_all *all);

int	empty_dir(const char *directory, const char *path, char *dir_tmp,
	char **list);

int	continue_with_dir(char **list, const char *directory, t_all *all,
	const char *path);

void	sort_list(char **list, char *dir_tmp, t_all *all, const char *directory,
	const char *path);

void	sort_asc(char **list, int ii, char *tmp);

void	sort_mod_time(char **list, int ii, const char *path, t_all *all);

void	sort_asc_arr(char **list, int ii);

int	count_num_of_files(DIR *dir, t_all *all);

int	**malloc_int_array(void);

void	call_check_num_of_links(t_all *all, char **list, const char *directory);

void	check_number_of_links(char **list, t_all *all, const char *path, int ii);

void	total_number_of_blocks(t_all *all);

void	print_array(char **arr, int i, int no, t_all *all);

void	write_only_ls(t_all *all);

void	write_long_output(char *file, t_all *all, const char *path);

#endif