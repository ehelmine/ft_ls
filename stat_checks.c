/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:27:41 by ehelmine          #+#    #+#             */
/*   Updated: 2021/05/11 15:34:19 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int	check_directory(char *file, t_all *all, char *path)
{
	struct stat buf;
	char *tmp;
	int i;
	
	tmp = NULL;
	if (path != NULL)
		tmp = ft_strjoin(path, file);
	if (path == NULL)
		tmp = file;
	i = stat(tmp, &buf);
	if (path != NULL)
		free(tmp);
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