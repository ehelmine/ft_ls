/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:27:41 by ehelmine          #+#    #+#             */
/*   Updated: 2021/05/06 20:15:55 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int	check_directory(const char *str, t_all *all)
{
	struct stat buf;
	char *tmp;

	tmp = ft_strjoin(all->path, str);
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