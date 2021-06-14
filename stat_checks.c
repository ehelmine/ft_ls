/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:27:41 by ehelmine          #+#    #+#             */
/*   Updated: 2021/06/14 16:20:53 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

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
		if (tmp == NULL)
			exit (1);
		free(path_slash);
	}
	all->i = lstat(tmp, &buf);
	free(tmp);
	if (all->i == 0 && S_ISDIR(buf.st_mode))
		return (1);
	return (0);
}

/*int	check_regular_file(const char *str)
{
	struct	stat buf;
	
	stat(str, &buf);
	return (S_ISREG(buf.st_mode));
}*/