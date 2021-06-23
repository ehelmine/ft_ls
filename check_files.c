/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 12:00:11 by ehelmine          #+#    #+#             */
/*   Updated: 2021/06/23 15:22:38 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	len_of_group(struct stat buf, t_all *all)
{
	struct group	*grp;
	int				len;

	grp = getgrgid(buf.st_gid);
	if (grp == NULL)
	{
		len = (int)ft_check_int_len(buf.st_gid);
		if (len > all->group_len)
			all->group_len = len;
	}
	else
	{
		len = ft_strlen(grp->gr_name);
		if (len > all->group_len)
			all->group_len = len;
	}
}

void	num_of_links_loop(char *tmp2, t_all *all)
{
	int			i;
	struct stat	buf;
	int			len;

	i = lstat(tmp2, &buf);
	if (i == -1 && !S_ISDIR(buf.st_mode))
		return ;
	if (i == 0)
	{
		len = (int)ft_check_int_len(buf.st_nlink);
		if (len > all->links_len)
			all->links_len = len;
		len = (int)ft_check_int_len(buf.st_size);
		if (len > all->size_len)
			all->size_len = len;
		all->blocks += buf.st_blocks;
		len_of_group(buf, all);
	}
}

static void	check_number_of_links(char **list, t_all *all,
	const char *path, int ii)
{
	char		*tmp2;
	int			x;

	tmp2 = NULL;
	all->group_len = 0;
	x = -1;
	while (++x < ii)
	{
		if (ft_strcmp(path, "") != 0)
			tmp2 = ft_strjoin(path, list[x]);
		check_if_null((void *)(tmp2));
		if (ft_strcmp(path, "") == 0)
			tmp2 = list[x];
		num_of_links_loop(tmp2, all);
		if (ft_strcmp(path, "") != 0)
			free(tmp2);
	}
}

void	call_check_num_of_links(t_all *all, char **list, const char *directory)
{
	int		ii;
	char	*tmp;

	ii = 0;
	while (list[ii] != NULL)
		ii++;
	all->links_len = 0;
	all->size_len = 0;
	all->blocks = 0;
	if (directory != NULL)
	{
		if (directory[ft_strlen(directory) - 1] != '/')
		{
			tmp = ft_strjoin(directory, "/");
			check_if_null((void *)(tmp));
			check_number_of_links(list, all, tmp, ii);
			free(tmp);
		}
		else
			check_number_of_links(list, all, directory, ii);
	}
	else
		check_number_of_links(list, all, directory, ii);
}

int	count_num_of_files(DIR *dir, t_all *all)
{
	struct dirent	*dp;	
	int				i;

	i = 0;
	dp = readdir(dir);
	while (dp)
	{
		if (dp->d_name[0] != '.' || (dp->d_name[0] == '.' && all->a_flag == 1))
			i++;
		dp = readdir(dir);
	}
	closedir(dir);
	return (i);
}
