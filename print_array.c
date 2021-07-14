/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:29:45 by ehelmine          #+#    #+#             */
/*   Updated: 2021/07/14 11:27:05 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

/*
**	Read the directory content and copy all the files/dirs to char **list. 
**	If we have -a flag, copy also the . -files. Put NULL to end of list and
**	return **list.
*/

static char	**read_directory(DIR *dir, t_all *all, int i)
{
	struct dirent	*dp;
	char			**list;

	dp = NULL;
	list = (char **)malloc(sizeof(char *) * (i + 1));
	if (list == NULL)
		exit (1);
	dp = readdir(dir);
	all->len_of_list = 0;
	while (dp)
	{
		if (dp->d_name[0] != '.' || (dp->d_name[0] == '.' && all->a_flag == 1))
		{
			list[all->len_of_list] = (char *)malloc(sizeof(char) * (1000));
			if (list[all->len_of_list] == NULL)
				exit(1);
			ft_strcpy(list[all->len_of_list++], dp->d_name);
		}
		dp = readdir(dir);
	}
	closedir(dir);
	list[all->len_of_list] = NULL;
	all->list = list;
	return (list);
}

/*
** If path == NULL it means that we're inside the directory where we want to 
** open that file. So if we have a path (and then path != NULL), we need to
** put path & directory together. Check that, and after that open directory.
** If we can't open in, write error message and return (NULL). 
** If we can open it, continue to read_directory -function.
*/

static char	**open_directory(const char *directory, const char *path,
	char *dir_tmp, t_all *all)
{
	open_dir_values(all);
	if (ft_strcmp(path, "") == 0)
		all->dir = opendir(directory);
	else
		all->dir = opendir(dir_tmp);
	if (all->dir == NULL)
		return (open_directory_is_null(all, directory, path, dir_tmp));
	all->ii = count_num_of_files(all->dir, all);
	if (ft_strcmp(path, "") == 0)
		all->dir = opendir(directory);
	else
		all->dir = opendir(dir_tmp);
	if (check_my_rights(directory, path, dir_tmp, all) == 0)
	{
		closedir(all->dir);
		return (NULL);
	}
	return (read_directory(all->dir, all, all->ii));
}

int	open_and_write_directory(t_all *all, const char *directory,
	const char *path, int i)
{	
	char	*dir_tmp;
	char	**list;

	dir_tmp = NULL;
	if (ft_strcmp(path, "") != 0)
	{
		dir_tmp = ft_strjoin(path, directory);
		check_if_null((void *)dir_tmp);
		i = 1;
	}
	if (check_if_link_and_rights(all, directory, dir_tmp, path) == -1)
		return (empty_dir(directory, path, dir_tmp, all));
	list = open_directory(directory, path, dir_tmp, all);
	if (list == NULL)
		return (empty_dir(directory, path, dir_tmp, all));
	if (i == 1)
		all->p = sort_list(list, all, dir_tmp);
	else
		all->p = sort_list(list, all, directory);
	if (all->p == -1)
		return (empty_dir(directory, path, dir_tmp, all));
	if (i == 1)
		return (continue_with_dir(list, dir_tmp, all, path));
	else
		return (continue_with_dir(list, directory, all, path));
}

void	loop_print_array(char **arr, int numbers[1][2], char *path, t_all *all)
{
	while (++all->y < numbers[0][0])
	{
		if (numbers[0][1] == 2)
		{
			open_and_write_directory(all, arr[all->y], path, 0);
			if (all->y + 1 != numbers[0][0])
				write(1, "\n", 1);
		}
		else if (numbers[0][1] == 1)
		{
			lstat(arr[all->y], &all->b_s);
			ft_printf("ls: %s: %s\n", arr[all->y], strerror(errno));
		}
		else if (numbers[0][1] == 0)
		{
			if (all->l_flag)
				start_long_output(arr[all->y], all, NULL, -1);
			else
				ft_printf("%s\n", arr[all->y]);
			if (all->num_dir && all->y + 1 == numbers[0][0])
				write(1, "\n", 1);
		}
	}
	initialize_print_array_values(all);
}

void	reverse_loop_print_array(char **arr, int numbers[1][2], char *path,
	t_all *all)
{
	while (all->counter >= 0)
	{
		if (numbers[0][1] == 2)
		{
			open_and_write_directory(all, arr[all->counter], path, 0);
			if (all->counter != 0)
				write(1, "\n", 1);
		}
		if (numbers[0][1] == 1)
		{
			lstat(arr[all->counter], &all->b_s);
			ft_printf("ls: %s: %s\n", arr[all->counter], strerror(errno));
		}
		else if (numbers[0][1] == 0)
		{
			if (all->l_flag)
				start_long_output(arr[all->counter], all, NULL, -1);
			else
				ft_printf("%s\n", arr[all->counter]);
			if (all->num_dir && all->counter - 1 == -1)
				write(1, "\n", 1);
		}
		all->counter--;
	}
	initialize_print_array_values(all);
}
