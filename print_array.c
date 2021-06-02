/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:29:45 by ehelmine          #+#    #+#             */
/*   Updated: 2021/06/02 17:54:57 by ehelmine         ###   ########.fr       */
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
	while ((dp = readdir(dir)))
	{
		if (dp->d_name[0] != '.' || (dp->d_name[0] == '.' && all->a_flag == 1))
		{
			list[ii] = (char *)malloc(sizeof(char) * (500));
			if (list[ii] == NULL)
				exit(1);
			ft_strcpy(list[ii++], dp->d_name);
		}
	}
	closedir(dir);
	list[ii] = NULL;
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
	if (path == NULL)
		dir = opendir(directory);
	else if (path != NULL)
		dir = opendir(dir_tmp);
	if (dir != NULL)
		i = count_num_of_files(dir, all);
	if (path == NULL)
		dir = opendir(directory);
	else if (path != NULL)
		dir = opendir(dir_tmp);
	if (dir == NULL)
	{
		ft_printf("%s\nls: %s: %s\n", dir_tmp, directory, strerror(errno));
		if (path != NULL)
		{
			free(dir_tmp);
			dir_tmp = NULL;
		}
		return (NULL);
	}
	return (read_directory(dir, all, i));
}

int	open_and_write_directory(t_all *all, const char *directory,
	const char *path)
{	
	char	*dir_tmp;
	char	**list;
	int		ii;

	dir_tmp = NULL;
	if (path != NULL)
	{
		dir_tmp = ft_strjoin(path, directory);
		if (dir_tmp == NULL)
			exit (1);
	}
	list = open_directory(directory, path, dir_tmp, all);
	if (list == NULL)
		return (0);
	ii = 0;
	while (list[ii] != NULL)
		ii++;
	if (ii == 0)
		return (empty_dir(directory, path, dir_tmp, list));
	if (ii > 1)
		sort_list(list, dir_tmp, all, directory, path);
	if (path != NULL)
		return (continue_with_dir(list, dir_tmp, all, path));
	else
		return (continue_with_dir(list, directory, all, path));
}

void	loop_print_array(char **arr, int numbers[1][2], char *path, t_all *all)
{
	int	x;

	x = 0;
	while (x < numbers[0][0])
	{
		if (numbers[0][1] == 2)
		{
			open_and_write_directory(all, arr[x], path);
			if (x + 1 != numbers[0][0])
				write(1, "\n", 2);
		}
		if (numbers[0][1] == 1)
			ft_printf("ls: %s: No such file or directory\n", arr[x]);
		else if (numbers[0][1] == 0)
		{
			ft_printf("%s\n", arr[x]);
			if (x + 1 == numbers[0][0])
				write(1, "\n", 2);
		}
		x++;
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
				write(1, "\n", 2);
		}
		if (numbers[0][1] == 1)
			ft_printf("ls: %s: No such file or directory\n", arr[x]);
		else if (numbers[0][1] == 0)
		{
			ft_printf("%s\n", arr[x]);
			if (x + 1 == 0)
				write(1, "\n", 2);
		}
		x--;
	}	
}
