/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 14:11:24 by ehelmine          #+#    #+#             */
/*   Updated: 2021/05/12 16:46:39 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	write_only_ls(t_all *all)
{
	DIR				*dir;
	int				i;
	char			list[100][100];
	struct dirent	*dp;

	dir = opendir(".");
	if (dir == NULL)
	{
		ft_putstr("can't open");
		exit (1);
	}
	i = 0;
	while (((dp = readdir(dir)) != NULL))
	{
		if (dp->d_name[0] != '.')
			ft_strcpy(list[i++], dp->d_name);
	}
	list[i][0] = '\0';
	sort_asc(list, i);
	all->x = 0;
	while (all->x < i)
		ft_printf("%s\n", list[all->x++]);
}

void	print_output(t_all *all)
{
	int	y;

	if (all->num_no > 0)
		print_and_free_array(all->not_exist, all->num_no, 1, all);
	if (all->num_file > 0)
		print_and_free_array(all->files, all->num_file, 0, all);
	if (all->num_dir > 0)
		print_and_free_array(all->directories, all->num_dir, 2, all);
	y = 0;
	while (y < all->num_no)
		free(all->not_exist[y++]);
	free(all->not_exist);
	y = 0;
	while (y < all->num_file)
		free(all->files[y++]);
	free(all->files);
	y = 0;
	while (y < all->num_dir)
		free(all->directories[y++]);
	free(all->directories);
}

/*
** If there is more arguments and the first one of those starts with something
** else than '-', we loop this function. We check the arguments: if it is a
** file, we put in in the char **files. If it is a directory, we put it in
** char **directories. If it is neither, we put it in char **no_exist.
*/

int	check_other_input(t_all *all, int i, int argc)
{
	int				ii;
	struct stat		buf;

	ii = 0;
	all->files = (char **)malloc(sizeof(char *) * (argc + 1));
	if (all->files == NULL)
		return (-1);
	all->not_exist = (char **)malloc(sizeof(char *) * (argc + 1));
	if (all->not_exist == NULL)
		return (-1);
	all->directories = (char **)malloc(sizeof(char *) * (argc + 1));
	if (all->directories == NULL)
		return (-1);
	while (i < argc)
	{
		if (stat(all->input_arr[i], &buf) == -1)
			all->not_exist[all->num_no++] = ft_strdup(all->input_arr[i]);
		else if (!(S_ISDIR(buf.st_mode)))
		{
			if (S_ISREG(buf.st_mode))
				all->files[all->num_file++] = ft_strdup(all->input_arr[i]);
		}
		else
		{
			all->directories[all->num_dir++] = ft_strdup(all->input_arr[i]);
		}
		i++;
	}
	return (1);
}

/*
** Loop from the argv[1] and try to find flags (- with Ralrt) and set
** true if found. If something else is found, call error function.
** If there is still arguments left that are not starting with -, 
** call check_other_input -function.
*/

int	check_flags(t_all *all, int argc)
{
	int	i;
	int	ii;
	int	x;

	i = 1;
	x = 0;
	ii = 1;
	if (all->input_arr[i][0] != '-')
		all->no_flags = 1;
	while (i < argc)
	{
		if (all->input_arr[i][0] != '-')
			break ;
		while (all->input_arr[i][0] == '-' && all->input_arr[i][ii] != '\0')
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
		i++;
	}
	if (i < argc)
		return (check_other_input(all, i, argc));
	return (1);
}

/*
** Copy input arguments to an array. Call a function that checks input.
*/

void	set_values_to_zero(t_all *all)
{
	all->a_flag = 0;
	all->l_flag = 0;
	all->reverse_flag = 0;
	all->big_r_flag = 0;
	all->t_flag = 0;
	all->no_flags = 0;
	all->num_file = 0;
	all->num_no = 0;
	all->num_dir = 0;
	all->p = 0;
	all->links_len = 0;
	all->tmp = NULL;
}

int	main(int argc, char **argv)
{
	t_all	all;
	int		i;
	int		ii;

	i = 0;
	ii = 0;
	set_values_to_zero(&all);
	if (argc == 1)
		write_only_ls(&all);
	else
	{
		all.not_exist = NULL;
		all.files = NULL;
		all.directories = NULL;
		while (i < argc)
			ft_strcpy(all.input_arr[i++], argv[ii++]);
		all.input_arr[i][0] = '\0';
		if (check_flags(&all, argc) == -1)
			return (-1);
		print_output(&all);
	}
//	system ("leaks ft_ls");
	return (0);
}


// MIKSI ME VALILLA SEGFAULTATAAN KUN ANTAA
// ft_ls -Rla libft MUTTEI AINA???