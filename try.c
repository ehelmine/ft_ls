/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:37:22 by ehelmine          #+#    #+#             */
/*   Updated: 2021/05/28 14:22:09 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"
//		./ft_ls -lRa ../../  3.04s user 1.88s system 41% cpu 11.953 total
//	printf change
//		./ft_ls -lRa ../../  2.93s user 1.74s system 41% cpu 11.166 total
// after i and d
//		./ft_ls -lRa ../../  2.91s user 1.68s system 41% cpu 11.114 total

int	**malloc_int_array()
{
	int	**other_dirrs;
	
	other_dirrs = NULL;
	other_dirrs = (int **)malloc(sizeof(int *) * 1);
	if (other_dirrs == NULL)
		exit (1);
	other_dirrs[0] = (int *)malloc(sizeof(int) * 800);
	if (other_dirrs[0] == NULL)
		exit (1);
	return (other_dirrs);
}

int	loop_dir_content(char **list, const char *directory, t_all *all, const char *path)
{
	int x;
	int o;
	int **other_dirrs;

	other_dirrs = NULL;
	if (all->big_r_flag)
		other_dirrs = malloc_int_array();
	x = 0;
	o = 0;
	while (list[x] != NULL)
	{
		if (all->big_r_flag)
		{
			if (check_directory(list[x], directory, all) != 0)
				other_dirrs[0][o++] = x;
		}
		if (all->l_flag)
		{
			if (x == 0)
				total_number_of_blocks(all);
			write_long_output(list[x], all, directory);
		}
		ft_printf("%s\n", list[x++]);
	}
	char *tmp;
	tmp = NULL;
	if (all->big_r_flag)
	{
		tmp = ft_strjoin(directory, "/");;
		if (tmp == NULL)
			exit (1);
		x = 0;
		while (x < o)
		{
			write(1, "\n", 2);
			open_and_write_directory(all, list[other_dirrs[0][x]], tmp);
			x++;
		}
		free(other_dirrs[0]);
		other_dirrs[0] = NULL;
		free(other_dirrs);
		other_dirrs = NULL;
		free(tmp);
		tmp = NULL;
	}
	if (path != NULL)
	{
		free((void*)directory);
		directory = NULL;
	}
	x = 0;
	while (list[x] != NULL)
		free(list[x++]);
	free(list);
	list = NULL;
	return (1);
}

int	continue_with_dir(char **list, const char *directory, t_all *all, const char *path)
{
	int	ii;

	ii = 0;
	while (list[ii] != NULL)
		ii++;
	if (path != NULL)
	{
		ft_putstr(directory);
		write(1, ":\n", 3);
	}
	if (all->l_flag)
		call_check_num_of_links(all, list, directory);
	loop_dir_content(list, directory, all, path);
	return (1);
}

int	empty_dir(const char *directory, const char *path, char *dir_tmp)
{
	if (path == NULL)
		ft_putstr(directory);
	else
	{
		ft_putstr(dir_tmp);
		free(dir_tmp);
		dir_tmp = NULL;
	}
	write(1, ":\n", 3);
	return (0);
}

/*
**	Read the directory content and copy all the files/dirs to char **list. 
**	If we have -a flag, copy also the . -files. Put NULL to end of list and
**	return **list.
*/

char	**read_directory(DIR *dir, t_all *all)
{
	int				i;
	int				ii;
	struct dirent	*dp;
	char			**list;

	i = 9000;
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

char	**open_directory(const char *directory, const char *path, char *dir_tmp, t_all *all)
{
	DIR		*dir;
	
	dir = NULL;
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
	return (read_directory(dir, all));
}

int		open_and_write_directory(t_all *all, const char *directory, const char *path)
{	
	char	*dir_tmp;
	char	**list;
	int		ii;

//	ft_printf("dir %s path %s\n", directory, path);
	dir_tmp = NULL;
	if (path != NULL)
	{
		dir_tmp = ft_strjoin(path, directory);
		if (dir_tmp == NULL)
			exit (1);
	}
	list = open_directory(directory, path, dir_tmp, all);
//	ft_printf("dir %s path %s d_t %s\n", directory, path, dir_tmp);
	if (list == NULL)
		return (0);
	ii = 0;
	while (list[ii] != NULL)
		ii++;
	if (ii == 0)
		return (empty_dir(directory, path, dir_tmp));
	if (ii > 1)
		sort_list(list, dir_tmp, all, directory, path);
	if (path != NULL)
		continue_with_dir(list, dir_tmp, all, path);
	else
		continue_with_dir(list, directory, all, path);
	return (1);
}
