/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 19:02:36 by ehelmine          #+#    #+#             */
/*   Updated: 2021/06/23 15:12:27 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

/*
** If there is more arguments and the first one of those starts with something
** else than '-', we loop this function. We check the arguments: if it is a
** file, we put in in the char **files. If it is a directory, we put it in
** char **directories. If it is neither, we put it in char **no_exist.
*/

static int	loop_other_input(t_all *all, int i, int argc)
{
	struct stat	buf;

	while (i < argc)
	{
		if (lstat(all->input_arr[i], &buf) == -1)
		{
			all->not_exist[all->num_no++] = ft_strdup(all->input_arr[i]);
			check_if_null((void *)all->not_exist[all->num_no - 1]);
		}
		else if (S_ISDIR(buf.st_mode) || (S_ISLNK(buf.st_mode) && !all->l_flag))
		{
			all->directories[all->num_dir++] = ft_strdup(all->input_arr[i]);
			check_if_null((void *)all->directories[all->num_dir - 1]);
		}
		else
		{
			all->files[all->num_file++] = ft_strdup(all->input_arr[i]);
			check_if_null((void *)all->files[all->num_file - 1]);
		}
		i++;
	}
	return (1);
}

static int	malloc_for_other_input(t_all *all, int i, int argc)
{
	if (i == argc)
	{
		all->directories = (char **)malloc(sizeof(char *) * 2);
		if (all->directories == NULL)
			return (-1);
		all->directories[all->num_dir++] = ft_strdup(".");
		return (1);
	}
	all->files = (char **)malloc(sizeof(char *) * (argc + 1));
	if (all->files == NULL)
		return (-1);
	all->not_exist = (char **)malloc(sizeof(char *) * (argc + 1));
	if (all->not_exist == NULL)
		return (-1);
	all->directories = (char **)malloc(sizeof(char *) * (argc + 1));
	if (all->directories == NULL)
		return (-1);
	return (loop_other_input(all, i, argc));
}

/*
** Loop from the argv[1] and try to find flags (- with Ralrt) and set
** true if some flag is found. If something else is found, call error function.
** If there is still arguments left that are not starting with -, 
** call check_other_input -function.
*/

static void	flags_loop(t_all *all, int i, int ii)
{
	while (all->input_arr[i][ii] != '\0')
	{
		if (all->input_arr[i][ii] == 'a')
			all->a_flag = 1;
		else if (all->input_arr[i][ii] == 'l')
			all->l_flag = 1;
		else if (all->input_arr[i][ii] == 'r')
			all->reverse_flag = 1;
		else if (all->input_arr[i][ii] == 'R')
			all->big_r_flag = 1;
		else if (all->input_arr[i][ii] == 't')
			all->t_flag = 1;
		else
			ft_exit_call(1, all->input_arr[i][ii]);
		ii++;
	}	
}

int	check_flags(t_all *all, int argc)
{
	int	i;
	int	ii;
	int	x;

	i = 1;
	x = 0;
	ii = 1;
	if (all->input_arr[i][0] != '-')
		all->n_fs = 1;
	while (i < argc)
	{
		if (all->input_arr[i][0] != '-')
			break ;
		flags_loop(all, i, ii);
		ii = 1;
		i++;
	}
	return (malloc_for_other_input(all, i, argc));
}
