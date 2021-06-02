/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:53:31 by ehelmine          #+#    #+#             */
/*   Updated: 2021/06/02 17:52:50 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

/*
** Sorting function, which checks the list of files and directories
** and checks it is in order by the last modification time.
*/

// MUISTA TEHDA
// SE ETTA KUN ON MUOKATTU LAST MOD -TIMEN MUKAAN,
// NIIN JOS NE ON TASMALLEEN SAMAAN AIKAAN
// NIIN SITTEN ASCENDING ORDER PITAA TEHDA NIILLE TIEDOSTOILLE.

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

void	sort_mod_time(char **list, int ii, const char *path, t_all *all)
{
	struct stat	first;
	struct stat	second;
	char		*tmp2;
	char		*cur_dir1;
	char		*cur_dir2;

	tmp2 = initialize_sort_tmp(path);
	while (all->i + 1 < ii)
	{
		cur_dir1 = list[all->i];
		cur_dir2 = list[all->i + 1];
		if (path != NULL)
		{
			cur_dir1 = call_strjoin(tmp2, list[all->i]);
			cur_dir2 = call_strjoin(tmp2, list[all->i + 1]);
		}
		if (lstat(cur_dir1, &first) == -1 || lstat(cur_dir2, &second) == -1)
			exit (1);
		if (path != NULL)
			free_two((void *)cur_dir1, (void *)cur_dir2);
		compare_times(first, second, list, all);
		all->i++;
	}
	free(tmp2);
	return ;
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

void	sort_list(char **list, char *dir_tmp, t_all *all, const char *directory,
	const char *path)
{
	int		ii;

	ii = 0;
	all->i = 0;
	while (list[ii] != NULL)
		ii++;
	if (all->t_flag)
	{
		if (path != NULL)
			sort_mod_time(list, ii, dir_tmp, all);
		else
			sort_mod_time(list, ii, directory, all);
	}
	else
		sort_asc(list, ii);
	if (all->reverse_flag)
		sort_reverse(list);
	return ;
}
