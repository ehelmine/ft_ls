/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_functions_help.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:49:26 by ehelmine          #+#    #+#             */
/*   Updated: 2021/06/28 14:06:23 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

char	*call_strjoin(char *path, char *file)
{
	char	*str;

	str = ft_strjoin(path, file);
	if (str == NULL)
		exit(1);
	return (str);
}

char	*initialize_sort_tmp(const char *path)
{
	char	*tmp;

	if (ft_strcmp(path, "") == 0)
		tmp = ft_strdup("");
	else if (ft_strcmp(path, "") != 0 && path[ft_strlen(path) - 1] != '/')
		tmp = ft_strjoin(path, "/");
	else
		tmp = ft_strdup(path);
	if (tmp == NULL)
		exit(1);
	return (tmp);
}

static void	swap_and_move_index_two_back(char **list, t_all *all)
{
	char	*tmp;

	tmp = NULL;
	tmp = list[all->i];
	list[all->i] = list[all->i + 1];
	list[all->i + 1] = tmp;
	all->i = all->i - 2;
	if (all->i < -1)
		all->i = -1;
}

void	compare_times(struct stat first, struct stat second, char **list,
	t_all *all)
{
	if (first.st_mtime < second.st_mtime)
		swap_and_move_index_two_back(list, all);
	else if (first.st_mtime == second.st_mtime)
	{
		if (first.st_mtimespec.tv_nsec < second.st_mtimespec.tv_nsec)
			swap_and_move_index_two_back(list, all);
		else
		{
			if (ft_strcmp(list[all->i], list[all->i + 1]) > 0
				&& first.st_mtimespec.tv_nsec
				== second.st_mtimespec.tv_nsec)
				swap_and_move_index_two_back(list, all);
		}
	}
}

void	free_two(void *ptr1, void *ptr2)
{
	if (ptr1 != NULL)
		free(ptr1);
	if (ptr2 != NULL)
		free(ptr2);
}
