/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_output_help.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:57:34 by ehelmine          #+#    #+#             */
/*   Updated: 2021/07/14 11:47:00 by ehelmine         ###   ########.fr       */
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
	other_dirrs[1] = (int *)malloc(sizeof(int) * 50);
	if (other_dirrs[1] == NULL)
		exit (1);
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
		return (0);
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
	return (0);
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
