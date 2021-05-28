/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 12:00:11 by ehelmine          #+#    #+#             */
/*   Updated: 2021/05/28 12:46:18 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	check_number_of_links(char **list, t_all *all, const char *path, int ii)
{
	int			len;
	struct stat	buf;
	char		*tmp1;
	char		*tmp2;
	int i;
	int x;

	x = 0;
	tmp1 = NULL;
	tmp2 = NULL;
	if (path != NULL)
	{
		if (path[ft_strlen(path) - 1] != '/')
		{
			tmp1 = ft_strjoin(path, "/");
			if (tmp1 == NULL)
				exit (1);
		}
	}
	while (x < ii)
	{
		if (path != NULL)
		{
			if (tmp1 != NULL)
				tmp2 = ft_strjoin(tmp1, list[x]);
			else
				tmp2 = ft_strjoin(path, list[x]);
			if (tmp2 == NULL)
				exit (1);
		}
		if (path == NULL)
			tmp2 = list[x];
		i = lstat(tmp2, &buf);
		if (path != NULL)
			free(tmp2);
		if (i == -1 && !S_IFDIR)
		{
			ft_putstr("stat fail1\n");
			exit (1);
		}
		if (i == 0)
		{
			len = ft_check_int_len(buf.st_nlink);
			if (len > all->links_len)
				all->links_len = len;
			len = ft_check_int_len(buf.st_size);
			if (len > all->size_len)
				all->size_len = len;
			all->blocks += buf.st_blocks;
		}
		x++;
	}
	if (tmp1 != NULL)
		free(tmp1);
}

void	call_check_num_of_links(t_all *all, char **list, const char *directory)
{
	int ii;

	ii = 0;
	while (list[ii] != NULL)
		ii++;
	all->links_len = 0;
	all->size_len = 0;
	all->blocks = 0;
	check_number_of_links(list, all, directory, ii);
}