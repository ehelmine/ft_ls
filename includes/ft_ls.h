/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 19:04:42 by ehelmine          #+#    #+#             */
/*   Updated: 2021/07/02 16:26:56 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/ft_printf/includes/ft_printf.h"
# include <sys/stat.h>
# include <sys/xattr.h>
# include <pwd.h>
# include <grp.h>
# include <dirent.h>
# include <time.h>
# include <errno.h>
# define MAX_LINES 10000

typedef struct s_all
{
	char		input_arr[MAX_LINES][500];
	char		**not_exist;
	char		**files;
	char		**directories;
	int			a_flag;
	int			l_flag;
	int			reverse_flag;
	int			big_r_flag;
	int			t_flag;
	int			n_fs;
	int			x;
	int			xx;
	int			num_no;
	int			num_file;
	int			num_dir;
	int			p;
	int			i;
	int			links_len;
	int			size_len;
	int			group_len;
	int			user_len;
	int			blocks;
	int			check;
	int			len_of_list;
	int			if_device;
	int			y;
	int			xattr;
	int			loop_call;
	int			ii;
	int			val;
	int			counter;
	struct stat	buf_s;
	char		output[12];
	char		tmp[3];
	int			e;
	char		**list;
	DIR			*dir;
}				t_all;

int		ft_exit_call(int i, char c);

int		check_directory(const char *file, const char *path, t_all *all);

int		check_flags(t_all *all, int argc);

void	check_if_null(void *ptr);

void	reverse_loop_print_array(char **arr, int numbers[1][2], char *path,
			t_all *all);

void	loop_print_array(char **arr, int numbers[1][2], char *path, t_all *all);

void	open_dir_values(t_all *all);

int		open_and_write_directory(t_all *all, const char *directory,
			const char *path);

int		empty_dir(const char *directory, const char *path, char *dir_tmp,
			t_all *all);

int		continue_with_dir(char **list, const char *directory, t_all *all,
			const char *path);

int		sort_list(char **list, t_all *all, const char *directory);

void	sort_asc(char **list, int ii);

int		sort_mod_time(char **list, int ii, const char *path, t_all *all);

int		count_num_of_files(DIR *dir, t_all *all);

int		**malloc_int_array(void);

void	call_check_num_of_links(t_all *all, char **list, const char *directory);

void	total_number_of_blocks(t_all *all);

void	check_num_of_links_with_files(char **files, t_all *all);

void	write_only_ls(t_all *all);

int		check_my_rights(const char *directory, const char *path, char *dir_tmp,
			t_all *all);

void	start_long_output(char *file, t_all *all, const char *path, int x);

void	check_file_type(char output[11], struct stat buf, t_all *all);

void	modify_time(char *str, time_t now, time_t mod_time);

void	num_of_links_loop(char *tmp2, t_all *all);

char	*get_link_name(char *path, struct stat buf);

void	print_time_and_name(char *str, char *file, char *arrow, char *link);

void	total_number_of_blocks(t_all *all);

void	free_two(void *ptr1, void *ptr2);

void	initialize_print_array_values(t_all *all);

void	compare_times(struct stat first, struct stat second, char **list,
			t_all *all);

char	*initialize_sort_tmp(const char *path);

char	*call_strjoin(char *path, char *file);

void	print_long_output(struct stat buf, t_all *all, struct passwd *pwd,
			struct group *grp);

#endif