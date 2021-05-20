/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:53:31 by ehelmine          #+#    #+#             */
/*   Updated: 2021/05/20 17:40:25 by ehelmine         ###   ########.fr       */
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

void	sort_mod_time(char **list, int ii, const char *path, t_all *all)
{
	struct	stat first;
	struct	stat second;
	char	*tmp;
	char	*tmp2;
	char	*cur_dir1;
	char	*cur_dir2;
	time_t	first_t;
	time_t	second_t;
	int		check;

	all->i = 0;
	check = 0;
//	ft_printf("here amount of lines ii %i path %s\n", ii, path);
	if (path != NULL && path[ft_strlen(path) - 1] != '/')
	{
		tmp2 = ft_strjoin(path, "/");
		check = 1;
	}
	else
		tmp2 = (char *)path;
	tmp = (char *)malloc(sizeof(char) * 1000);
	if (tmp == NULL)
		exit (1);
	while (all->i + 1 < ii)
	{
		if (path != NULL)
		{
//			ft_printf("list1 %s list+1 %s ii %i all->i %i\n", list[all->i], list[all->i + 1], ii, all->i);
			cur_dir1 = ft_strjoin(tmp2, list[all->i]);
			if (cur_dir1 == NULL)
				exit (1);
			cur_dir2 = ft_strjoin(tmp2, list[all->i + 1]);
			if (cur_dir2 == NULL)
				exit (1);
		}
		else if (path == NULL)
		{
			cur_dir1 = list[all->i];
			cur_dir2 = list[all->i + 1];
		}
//		ft_printf("curdir1 %s curdir2 %s ii %i all->i %i\n", cur_dir1, cur_dir2, ii, all->i);
		if (lstat(cur_dir1, &first) == -1)
		{
			ft_putstr("stat fail in modt\n");
			exit (1);
		}
		if (lstat(cur_dir2, &second) == -1)
		{
			ft_putstr("stat fail in modt\n");
			exit (1);
		}
		if (path != NULL)
		{
			free(cur_dir1);
			free(cur_dir2);
		}
		first_t = first.st_mtime;
		second_t = second.st_mtime;
		if (first_t < second_t)
		{
			ft_strcpy(tmp, list[all->i]);
			ft_strcpy(list[all->i], list[all->i + 1]);
			ft_strcpy(list[all->i + 1], tmp);
			all->i = -1;
		}
		else if (first_t == second_t)
		{
			if (ft_strcmp(list[all->i], list[all->i + 1]) > 0)
			{
				ft_strcpy(tmp, list[all->i]);
				ft_strcpy(list[all->i], list[all->i + 1]);
				ft_strcpy(list[all->i + 1], tmp);
				all->i = -1;	
			}
		}
		all->i++;
	}
	free(tmp);
	if (check == 1)
		free(tmp2);
	return ;
//	ft_printf("here counter %i amount of lines ii %i path %s\n", i, ii, path);
}

/*
** Sorting function, which checks the list of files and directories
** and checks it is in order by the ascending order.
*/

void	sort_asc(char **list, int ii)
{
	char	temp[800];
	int		i;
	int		x;

	i = 0;
	while (i < ii - 1)
	{
		x = ft_strcmp(list[i], list[i + 1]);
		if (x > 0)
		{
			ft_strcpy(temp, list[i]);
			ft_strcpy(list[i], list[i + 1]);
			ft_strcpy(list[i + 1], temp);
			i = -1;
		}
		i++;
	}

}