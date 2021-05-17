/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:29:45 by ehelmine          #+#    #+#             */
/*   Updated: 2021/05/17 12:48:22 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	sort_asc_arr(char **list, int ii)
{
	char temp[500];
	int i;
	int x;

	i = 0;
	while (i < ii - 1)
	{
		x = ft_strcmp(list[i], list[i + 1]);
		if (x > 0)
		{
			ft_strcpy(temp, list[i]);
			ft_strcpy(list[i], list[i + 1]);
			ft_strcpy(list[i + 1], temp);
			i = -1;
		}
		i++;
	}
}

void	print_and_free_array(char **arr, int i, int no, t_all *all)
{
	int x;
	char *tmp;
	int check;
	char *path;

	tmp = NULL;
	check = 0;
	x = 0;
	path = NULL;
	path = (char *)malloc(sizeof(char) * 2000);
	if (path == NULL)
		exit(1);
	path = NULL;
	if (i > 1 && !all->t_flag)
		sort_asc_arr(arr, i);
	if (i == 0 && no == 2)
	{
		tmp = (char *)malloc(sizeof(char) * 1000);
		tmp[0] = '.';
		tmp[1] = '\0';
		check = 1;
		i++;
	}
	while (x < i)
	{
		ft_printf("x %i\n", x);
		if (no == 2)
		{
			if (check == 1)
				open_and_write_directory(all, tmp, path);
			else
				open_and_write_directory(all, arr[x], path);
		}
		if (no == 1)
			ft_printf("ls: %s: No such file or directory\n", arr[x]);
		else if (no == 0)
		{
			ft_printf("%s\n", arr[x]);
			if (x + 1 == i)
				write(1, "\n", 2);
		}
		x++;
	}
	free(path);
	if (check == 1)
		free(tmp);
	return ;
}