/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:27:41 by ehelmine          #+#    #+#             */
/*   Updated: 2021/05/12 16:35:59 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int	check_directory(char *file, t_all *all, char *path)
{
	struct stat buf;
	char *tmp;
	int i;
	char *path_slash;
	int len;
	
	tmp = NULL;
	len = 0;
	path_slash = NULL;
	if (file[0] == '.')
		return (0);
	if (path != NULL)
		len = ft_strlen(path);
	if (len > 0 && path[len - 1] != '/' && path != NULL)
	{
		path_slash = ft_strjoin(path, "/");
		tmp = ft_strjoin(path_slash, file);
	}
	else if (path != NULL)
		tmp = ft_strjoin(path, file);
	else if (path == NULL)
		tmp = file;
	i = stat(tmp, &buf);
	if (path != NULL)
		free(tmp);
	if (path_slash != NULL)
		free(path_slash);
//	ft_printf("string %s \n", tmp);
	if (i < 0 && !S_IFDIR)
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