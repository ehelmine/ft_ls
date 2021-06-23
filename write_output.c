/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:37:22 by ehelmine          #+#    #+#             */
/*   Updated: 2021/06/23 15:19:27 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	call_other_directories(char **list, const char *directory,
	int **other_dirrs, t_all *all)
{
	char	*tmp;
	int		x;
	int		ii;

	tmp = NULL;
	tmp = ft_strjoin(directory, "/");
	check_if_null((void *)tmp);
	x = 0;
	ii = other_dirrs[1][0];
	all->loop_call = 1;
	while (x < ii)
	{
		write(1, "\n", 1);
		if (open_and_write_directory(all, list[other_dirrs[0][x]], tmp) == 0)
			write(1, "\n", 1);
		x++;
	}
	free(other_dirrs[0]);
	free(other_dirrs[1]);
	free(other_dirrs);
	other_dirrs = NULL;
	free(tmp);
	tmp = NULL;
}

static void	loop_dir_content2(char **list, const char *directory, t_all *all,
	int **other_dirrs)
{
	int	x;
	int	o;

	x = 0;
	o = 0;
	while (list[x] != NULL)
	{
		if (all->big_r_flag)
		{
			if (check_directory(list[x], directory, all) != 0)
				other_dirrs[0][o++] = x;
			other_dirrs[1][0] = o;
		}
		if (all->l_flag)
			start_long_output(list[x], all, directory, x);
		if (!all->l_flag)
			ft_printf("%s\n", list[x]);
		x++;
	}
}

static int	loop_dir_content(char **list, const char *directory, t_all *all,
	const char *path)
{
	int	**other_dirrs;
	int	x;

	other_dirrs = NULL;
	if (all->big_r_flag)
		other_dirrs = malloc_int_array();
	loop_dir_content2(list, directory, all, other_dirrs);
	if (all->big_r_flag)
		call_other_directories(list, directory, other_dirrs, all);
	if (ft_strcmp(path, "") != 0)
	{
		free((void *)directory);
		directory = NULL;
	}
	x = 0;
	while (list[x] != NULL)
		free(list[x++]);
	free(list);
	list = NULL;
	return (1);
}

int	continue_with_dir(char **list, const char *directory, t_all *all,
	const char *path)
{
	struct stat	buf;
	int			ii;

	if ((!all->n_fs && (ft_strcmp(path, "") != 0 || directory != NULL))
		|| (all->n_fs && (all->num_dir > 1 || all->num_file || all->num_no)))
	{
		ft_putstr(directory);
		write(1, ":\n", 2);
	}
	if (lstat(directory, &buf) == 0 && buf.st_mode & S_IXUSR)
		ii = 0;
	else
	{
		ii = 0;
		if (ft_strcmp(path, "") != 0)
			free((void *)directory);
		while (list[ii] != NULL)
			free(list[ii++]);
		free(list);
		return (0);
	}
	if (all->l_flag)
		call_check_num_of_links(all, list, directory);
	loop_dir_content(list, directory, all, path);
	return (1);
}
