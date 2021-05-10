/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:27:41 by ehelmine          #+#    #+#             */
/*   Updated: 2021/05/10 17:42:00 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int	check_directory(char *str, t_all *all, char *path)
{
	struct stat buf;
	char *tmp;
	int i;
	
	tmp = NULL;
	if (path != NULL)
		tmp = ft_strjoin(path, str);
	if (path == NULL)
		tmp = str;
	i = stat(tmp, &buf);
	if (path != NULL)
		free(tmp);
	if (i < 0 && !S_IFDIR)
		return (0);
//	ft_printf("string %s and %i return val\n", tmp, S_ISDIR(buf.st_mode));
	if (S_IFDIR)
		return (1);
	return (S_ISDIR(buf.st_mode));
}

int	check_regular_file(const char *str)
{
	struct stat buf;
	
	stat(str, &buf);
	return (S_ISREG(buf.st_mode));
}