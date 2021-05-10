/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:27:41 by ehelmine          #+#    #+#             */
/*   Updated: 2021/05/10 11:47:37 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int	check_directory(char *str, t_all *all, char *path)
{
	struct stat buf;
	char *tmp;
	
	if (path != NULL)
		tmp = ft_strjoin(path, str);
	if (path == NULL)
		tmp = str;
	stat(tmp, &buf);
//	ft_printf("string %s and %i return val\n", tmp, S_ISDIR(buf.st_mode));
	return (S_ISDIR(buf.st_mode));
}

int	check_regular_file(const char *str)
{
	struct stat buf;
	
	stat(str, &buf);
	return (S_ISREG(buf.st_mode));
}