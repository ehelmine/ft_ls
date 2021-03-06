/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 19:02:36 by ehelmine          #+#    #+#             */
/*   Updated: 2022/03/24 11:24:07 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

/*
** If there is more arguments and the first one of those starts with something
** else than '-', we loop this function. We check the arguments: if it is a
** file, we put in in the char **files. If it is a directory, we put it in
** char **directories. If it is neither, we put it in char **no_exist.
*/

static void	loop_other_input(t_all *all, int i, int argc)
{
	while (++i < argc)
	{
		if (lstat(all->input_arr[i], &all->b_s) == -1)
			all->not_exist[all->num_no++] = ft_strdup(all->input_arr[i]);
		else if (S_ISLNK(all->b_s.st_mode))
		{
			if (!all->l_flag)
			{
				all->s = get_link_name(all->input_arr[i], all->b_s);
				if (lstat(all->s, &all->b_s) == 0 && S_ISDIR(all->b_s.st_mode))
					all->directories[all->num_dir++]
						= ft_strdup(all->input_arr[i]);
				else
					all->files[all->num_file++] = ft_strdup(all->input_arr[i]);
				if (all->s != NULL)
					free(all->s);
			}
			else
				all->files[all->num_file++] = ft_strdup(all->input_arr[i]);
		}
		else if (S_ISDIR(all->b_s.st_mode))
			all->directories[all->num_dir++] = ft_strdup(all->input_arr[i]);
		else
			all->files[all->num_file++] = ft_strdup(all->input_arr[i]);
	}
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
	loop_other_input(all, i - 1, argc);
	return (1);
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

	i = 1;
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
