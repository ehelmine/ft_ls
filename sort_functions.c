/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:53:31 by ehelmine          #+#    #+#             */
/*   Updated: 2021/06/23 16:34:44 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

/*
** Sorting function, which checks the list of files and directories
** and checks it is in order by the last modification time.
*/

void	sort_reverse(char **list)
{
	int		start;
	int		end;
	int		i;
	char	*temp;

	i = 0;
	while (list[i] != NULL)
		i++;
	start = 0;
	end = i - 1;
	temp = NULL;
	while (start < end)
	{
		temp = list[start];
		list[start] = list[end];
		list[end] = temp;
		start++;
		end--;
	}
}

static int	free_mod_time(const char *path, char *d1, char *d2, char *str)
{
	if (ft_strcmp(path, "") != 0)
	{
		free(d1);
		free(d2);
	}
	free(str);
	return (-1);
}

int	sort_mod_time(char **list, int ii, const char *path, t_all *all)
{
	struct stat	first;
	struct stat	second;
	char		*tmp2;
	char		*cur_dir1;
	char		*cur_dir2;

	tmp2 = initialize_sort_tmp(path);
	while (all->i + 1 < ii)
	{
//		ft_printf("path %s eka %s toka %s all->i %i and ii %i\n", path, list[all->i], list[all->i + 1], all->i, ii);
		cur_dir1 = list[all->i];
		cur_dir2 = list[all->i + 1];
		if (ft_strcmp(path, "") != 0)
		{
			cur_dir1 = call_strjoin(tmp2, list[all->i]);
			cur_dir2 = call_strjoin(tmp2, list[all->i + 1]);
		}
		if (lstat(cur_dir1, &first) == -1 || lstat(cur_dir2, &second) == -1)
			return (free_mod_time(path, cur_dir1, cur_dir2, tmp2));
		compare_times(first, second, list, all);
		if (ft_strcmp(path, "") != 0)
			free_two((void *)cur_dir1, (void *)cur_dir2);
		all->i++;
	}
	free(tmp2);
	return (1);
}

/*
** Sorting function, which checks the list of files and directories
** and checks it is in order by the ascending order.
*/

void	sort_asc(char **list, int ii)
{
	int		i;
	int		x;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (i < ii - 1)
	{
		x = ft_strcmp(list[i], list[i + 1]);
		if (x > 0)
		{
			tmp = list[i];
			list[i] = list[i + 1];
			list[i + 1] = tmp;
			i = i - 2;
			if (i < -1)
				i = -1;
		}
		i++;
	}
}

int	sort_list(char **list, t_all *all, const char *directory)
{
	int	x;

	all->i = 0;
	x = 0;
	if (all->t_flag)
		x = sort_mod_time(list, all->len_of_list, directory, all);
	else
		sort_asc(list, all->len_of_list);
	if (x == -1)
		return (-1);
	if (all->reverse_flag)
		sort_reverse(list);
	return (0);
}
