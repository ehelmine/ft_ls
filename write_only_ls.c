/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_only_ls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 19:00:55 by ehelmine          #+#    #+#             */
/*   Updated: 2021/06/22 13:08:13 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	output_and_free_ls(t_all *all, char **list, int i)
{
	sort_asc(list, i);
	all->x = 0;
	while (all->x < i)
	{
		ft_printf("%s\n", list[all->x]);
		free(list[all->x++]);
	}
	free(list);
}

void	write_only_ls(t_all *all)
{
	DIR				*dir;
	int				i;
	char			**list;
	struct dirent	*dp;

	dir = opendir(".");
	check_if_null((void *)dir);
	i = 0;
	list = (char **)malloc(sizeof(char) * 14000);
	if (list == NULL)
		exit (1);
	dp = readdir(dir);
	while (dp)
	{
		if (dp->d_name[0] != '.')
		{
			list[i] = ft_strdup(dp->d_name);
			check_if_null((void *)list[i]);
			i++;
		}
		dp = readdir(dir);
	}
	closedir(dir);
	list[i] = NULL;
	output_and_free_ls(all, list, i);
}
