/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:29:45 by ehelmine          #+#    #+#             */
/*   Updated: 2021/06/16 15:33:13 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

/*
**	Read the directory content and copy all the files/dirs to char **list. 
**	If we have -a flag, copy also the . -files. Put NULL to end of list and
**	return **list.
*/

char	**read_directory(DIR *dir, t_all *all, int i)
{
	int				ii;
	struct dirent	*dp;
	char			**list;

	ii = 0;
	dp = NULL;
	list = (char **)malloc(sizeof(char *) * (i + 1));
	if (list == NULL)
		exit (1);
	dp = readdir(dir);
	while (dp)
	{
		if (dp->d_name[0] != '.' || (dp->d_name[0] == '.' && all->a_flag == 1))
		{
			list[ii] = (char *)malloc(sizeof(char) * (500));
			if (list[ii] == NULL)
				exit(1);
			ft_strcpy(list[ii++], dp->d_name);
		}
		dp = readdir(dir);
	}
	closedir(dir);
	list[ii] = NULL;
	all->len_of_list = ii;
	return (list);
}

/*
** If path == NULL it means that we're inside the directory where we want to 
** open that file. So if we have a path (and then path != NULL), we need to
** put path & directory together. Check that, and after that open directory.
** If we can't open in, write error message and return (NULL). 
** If we can open it, continue to read_directory -function.
*/

char	**open_directory(const char *directory, const char *path, char *dir_tmp,
	t_all *all)
{
	DIR		*dir;
	int		i;

	dir = NULL;
	if (ft_strcmp(path, "") == 0)
		dir = opendir(directory);
	else if (ft_strcmp(path, "") != 0)
		dir = opendir(dir_tmp);
	if (dir != NULL)
		i = count_num_of_files(dir, all);
	if (ft_strcmp(path, "") == 0)
		dir = opendir(directory);
	else if (ft_strcmp(path, "") != 0)
		dir = opendir(dir_tmp);
	if (dir == NULL)
	{
		ft_printf("%s\nls: %s: %s", dir_tmp, directory, strerror(errno));
		if (!all->loop_call)
			write(1, "\n", 1);
		if (ft_strcmp(path, "") != 0)
			free(dir_tmp);
		return (NULL);
	}
	return (read_directory(dir, all, i));
}

int	open_and_write_directory(t_all *all, const char *directory,
	const char *path)
{	
	char	*dir_tmp;
	char	**list;

	dir_tmp = NULL;
	if (ft_strcmp(path, "") != 0)
	{
		dir_tmp = ft_strjoin(path, directory);
		check_if_null((void *)dir_tmp);
	}
	list = open_directory(directory, path, dir_tmp, all);
	if (all->len_of_list == 0 || list == NULL)
		return (empty_dir(directory, path, dir_tmp, list));
	if (all->len_of_list > 1)
	{
		if (ft_strcmp(path, "") != 0)
			all->p = sort_list(list, all, dir_tmp);
		else
			all->p = sort_list(list, all, directory);
		if (all->p == -1)
			return (empty_dir(directory, path, dir_tmp, list));
	}
	if (ft_strcmp(path, "") != 0)
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
			open_and_write_directory(all, arr[all->y], path);
			if (all->y + 1 != numbers[0][0])
				write(1, "\n", 1);
		}
		else if (numbers[0][1] == 1)
			ft_printf("ls: %s: No such file or directory\n", arr[all->y]);
		else if (numbers[0][1] == 0)
		{
			if (all->l_flag)
			{
				num_of_links_loop(arr[all->y], all);
				start_long_output(arr[all->y], all, NULL, -1);
			}
			else
				ft_printf("%s\n", arr[all->y]);
			if (all->num_dir && all->y + 1 == numbers[0][0])
				write(1, "\n", 1);
		}
	}	
}

void	reverse_loop_print_array(char **arr, int numbers[1][2], char *path,
	t_all *all)
{
	int	x;

	x = numbers[0][0] - 1;
	while (x >= 0)
	{
		if (numbers[0][1] == 2)
		{
			open_and_write_directory(all, arr[x], path);
			if (x - 1 != -1)
				write(1, "\n", 1);
		}
		if (numbers[0][1] == 1)
			ft_printf("ls: %s: No such file or directory\n", arr[x]);
		else if (numbers[0][1] == 0)
		{
			ft_printf("%s\n", arr[x]);
			if (x + 1 == 0)
				write(1, "\n", 1);
		}
		x--;
	}	
}
