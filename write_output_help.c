/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_output_help.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:57:34 by ehelmine          #+#    #+#             */
/*   Updated: 2021/07/15 15:32:14 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int	**malloc_int_array(t_all *all)
{
	int	**other_dirrs;

	all->e = 0;
	other_dirrs = NULL;
	other_dirrs = (int **)malloc(sizeof(int *) * 2);
	if (other_dirrs == NULL)
		exit (1);
	other_dirrs[0] = (int *)malloc(sizeof(int) * (all->len_of_list + 1000));
	if (other_dirrs[0] == NULL)
		exit (1);
	other_dirrs[1] = (int *)malloc(sizeof(int) * 100);
	if (other_dirrs[1] == NULL)
		exit (1);
	other_dirrs[1][0] = 0;
	return (other_dirrs);
}

int	empty_dir(const char *directory, const char *path, char *dir_tmp,
	t_all *all)
{
	int	x;

	x = 0;
	if (all->len_of_list == 0)
	{
		if (all->val == 1)
			free(dir_tmp);
		free(all->list);
		all->val = 0;
		return (-1);
	}
	if (ft_strcmp(path, "") == 0)
		ft_putstr(directory);
	else
	{
		ft_putstr(dir_tmp);
		free(dir_tmp);
		dir_tmp = NULL;
		while (all->list[x] != NULL)
			free(all->list[x++]);
	}
	free(all->list);
	all->list = NULL;
	write(1, ":\n", 2);
	return (-1);
}

void	initialize_print_array_values(t_all *all)
{
	all->group_len = 0;
	all->size_len = 0;
	all->links_len = 0;
	all->blocks = 0;
	all->user_len = 0;
}

void	open_dir_values(t_all *all)
{
	all->dir = NULL;
	all->len_of_list = 0;
	all->val = 0;
	all->list = NULL;
}
