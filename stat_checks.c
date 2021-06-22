/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:27:41 by ehelmine          #+#    #+#             */
/*   Updated: 2021/06/22 20:16:59 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int	check_my_rights(const char *directory, const char *path, char *dir_tmp,
		t_all *all)
{
	struct stat	buf;

	all->val = 0;
	if (ft_strcmp(path, "") == 0)
		all->xx = lstat(directory, &buf);
	else
	{
		all->val = 1;
		all->xx = lstat(dir_tmp, &buf);
	}
	if (all->xx == 0 && buf.st_mode & S_IXUSR)
		return (1);
	else
	{
		if ((all->big_r_flag && all->num_dir > 1) || all->num_dir > 1
			|| (all->num_dir == 1 && (all->num_no || all->num_file)))
		{
			if (all->val == 0)
				ft_putstr(directory);
			else if (all->val == 1)
				ft_putstr(dir_tmp);
			write(1, ":\n", 2);
		}
		return (0);
	}
}

void	check_if_null(void *ptr)
{
	if (ptr == NULL)
		exit(1);
	else
		return ;
}

int	check_directory(const char *file, const char *path, t_all *all)
{
	struct stat	buf;
	char		*tmp;
	char		*path_slash;

	all->i = 0;
	path_slash = NULL;
	if (file[0] == '.' && (file[1] == '.' || file[1] == '\0'))
		return (0);
	if (ft_strcmp(path, "") == 0)
		tmp = ft_strdup(file);
	else
	{
		path_slash = ft_strjoin(path, "/");
		if (path_slash == NULL)
			exit (1);
		tmp = ft_strjoin(path_slash, file);
		free(path_slash);
	}
	if (tmp == NULL)
		exit (1);
	all->i = lstat(tmp, &buf);
	free(tmp);
	if (all->i == 0 && S_ISDIR(buf.st_mode))
		return (1);
	return (0);
}
