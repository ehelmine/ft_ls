/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 19:04:42 by ehelmine          #+#    #+#             */
/*   Updated: 2021/05/10 11:47:46 by ehelmine         ###   ########.fr       */
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
#include <dirent.h>
#define MAX_LINES 10000

typedef	struct s_all
{
		char input_arr[MAX_LINES][__DARWIN_MAXNAMLEN];
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
		char *path;
		char **path_arr;
		int p;
		char *tmp;
}				t_all;

int		ft_exit_call(int i);

int		check_regular_file(const char *str);

int		check_directory(char *str, t_all *all, char *path);

int		open_and_write_directory(t_all *all, char *directory, char *path);

void	sort_asc(char list[100][100], int ii);

void	sort_asc_arr(char **list, int ii);

void	print_and_free_array(char **arr, int i, int no, t_all *all);

#endif