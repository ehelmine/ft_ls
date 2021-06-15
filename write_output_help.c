/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_output_help.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:57:34 by ehelmine          #+#    #+#             */
/*   Updated: 2021/06/15 13:18:10 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int	**malloc_int_array(void)
{
	int	**other_dirrs;

	other_dirrs = NULL;
	other_dirrs = (int **)malloc(sizeof(int *) * 2);
	if (other_dirrs == NULL)
		exit (1);
	other_dirrs[0] = (int *)malloc(sizeof(int) * 800);
	if (other_dirrs[0] == NULL)
		exit (1);
	other_dirrs[1] = (int *)malloc(sizeof(int) * 2);
	return (other_dirrs);
}

int	empty_dir(const char *directory, const char *path, char *dir_tmp,
	char **list)
{
	int	x;

	if (list == NULL)
		return (0);
	x = 0;
	if (ft_strcmp(path, "") == 0)
		ft_putstr(directory);
	else
	{
		ft_putstr(dir_tmp);
		free(dir_tmp);
		dir_tmp = NULL;
		while (list[x] != NULL)
			free(list[x++]);
		free(list);
		list = NULL;
	}
	write(1, ":\n", 1);
	return (0);
}
