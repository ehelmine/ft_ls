/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:37:22 by ehelmine          #+#    #+#             */
/*   Updated: 2021/06/02 17:57:53 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"
//		./ft_ls -lRa ../../  3.04s user 1.88s system 41% cpu 11.953 total
//	printf change
//		./ft_ls -lRa ../../  2.93s user 1.74s system 41% cpu 11.166 total
// after i and d
//		./ft_ls -lRa ../../  2.91s user 1.68s system 41% cpu 11.114 total

void	call_other_directories(char **list, const char *directory,
	int **other_dirrs, t_all *all)
{
	char	*tmp;
	int		x;
	int		ii;

	tmp = NULL;
	tmp = ft_strjoin(directory, "/");
	if (tmp == NULL)
		exit (1);
	x = 0;
	ii = other_dirrs[1][0];
	while (x < ii)
	{
		write(1, "\n", 2);
		open_and_write_directory(all, list[other_dirrs[0][x]], tmp);
		x++;
	}
	free(other_dirrs[0]);
	free(other_dirrs[1]);
	free(other_dirrs);
	other_dirrs = NULL;
	free(tmp);
	tmp = NULL;
}

void	loop_dir_content2(char **list, const char *directory, t_all *all,
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

int	loop_dir_content(char **list, const char *directory, t_all *all,
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
	if (path != NULL)
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
