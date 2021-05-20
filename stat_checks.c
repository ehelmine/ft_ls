/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:27:41 by ehelmine          #+#    #+#             */
/*   Updated: 2021/05/20 17:44:18 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int	check_directory(char *file, const char *path, t_all *all)
{
	struct stat buf;
	char *tmp;
	int i;
	char *path_slash;
	int len;
	
	len = 0;
	all->i = 0;
	path_slash = NULL;
	if (file[0] == '.' && (file[1] == '.' || file[1] == '\0'))
		return (0);
	if (path != NULL)
		len = ft_strlen(path);
	if (path == NULL)
	{
		tmp = ft_strnew(len + 1);
		if (tmp == NULL)
			exit(1);
		ft_strcpy(tmp, file);
	}
	else if (len > 0 && path[len - 1] != '/' && path != NULL)
	{
		path_slash = ft_strjoin(path, "/");
		if (path_slash == NULL)
			exit (1);
		tmp = ft_strjoin(path_slash, file);
		free(path_slash);
		if (tmp == NULL)
			exit (1);
	}
	else
	{
		tmp = ft_strjoin(path, file);
		if (tmp == NULL)
			exit (1);
	}
	i = lstat(tmp, &buf);
	free(tmp);
	if (i == -1 && !(S_ISDIR(buf.st_mode)))
		return (0);
	if (S_ISDIR(buf.st_mode))
		return (1);
	return (0);
}

int	check_regular_file(const char *str)
{
	struct stat buf;
	
	stat(str, &buf);
	return (S_ISREG(buf.st_mode));
}