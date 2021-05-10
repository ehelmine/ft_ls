/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:29:45 by ehelmine          #+#    #+#             */
/*   Updated: 2021/05/10 17:39:38 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	sort_asc_arr(char **list, int ii)
{
	char temp[__DARWIN_MAXNAMLEN];
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

void	loop_directories(t_all *all)
{
	char			list[100][100];
	DIR				*dir;
	struct dirent	*dp;
	int i;
	int x;
	int ii;
	int y;
	
	i = 0;
	y = 0;
	while (i < all->num_dir)
	{
		ii = 0;
		dir = opendir(all->directories[i]);
		if (dir == NULL)
		{
			ft_putstr("can't open");
			exit (1);
		}
		while (((dp = readdir(dir)) != NULL))
		{
			if (dp->d_name[0] != '.')
				ft_strcpy(list[ii++], dp->d_name);
		}
		list[ii][0] = '\0';
		sort_asc(list, ii);
		x = 0;
		ft_putstr(all->directories[i]);
		free(all->directories[i]);
		ft_putstr(":\n");
		while (x < ii)
		{
//			if (check_directory(list[x]))
//				int_arr[0][y++] = x;
			ft_printf("%s\n", list[x++]);
		}
		if (i + 1 != all->num_dir)
			ft_putstr("\n");
		if (all->big_r_flag && y > 0)
			ft_putstr("there is more directories\n");
		i++;
	}
}

void	print_and_free_array(char **arr, int i, int no, t_all *all)
{
	int x;
	char *tmp;
	int check;

	tmp = NULL;
	x = 0;
	if (i > 1 && !all->t_flag)
		sort_asc_arr(arr, i);
	if (i == 0 && no == 2)
	{
		tmp = (char*)malloc(sizeof(char) * 1000);
		tmp[0] = '.';
		check = 1;
		i++;
	}
	while (x < i)
	{
		if (no == 2)
		{
			if (check == 1)
				open_and_write_directory(all, tmp, NULL);
			else
				open_and_write_directory(all, arr[x], NULL);
		}
		else if (no == 1)
			ft_printf("ls: %s: No such file or directory\n", arr[x]);
		else if (no == 0)
		{
			ft_printf("%s\n", arr[x]);
			if (x + 1 == i)
				write(1, "\n", 2);
		}
		x++;
	}
	if (check == 1)
		free(tmp);
	return ;
}