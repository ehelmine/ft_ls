/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 14:11:24 by ehelmine          #+#    #+#             */
/*   Updated: 2021/06/02 17:55:00 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"


void	print_array(char **arr, int i, int no, t_all *all)
{
	char	*path;
	int		numbers[1][2];

	path = NULL;
	path = (char *)malloc(sizeof(char) * 1000);
	if (path == NULL)
		exit(1);
	path = NULL;
	if (i > 1 && all->t_flag)
		sort_mod_time(arr, i, path, all);
	else if (i > 1 && !all->t_flag)
		sort_asc(arr, i);
	numbers[0][0] = i;
	numbers[0][1] = no;
	if (all->reverse_flag)
		reverse_loop_print_array(arr, numbers, path, all);
	else
		loop_print_array(arr, numbers, path, all);
	free(path);
	return ;
}

void	print_output(t_all *all)
{
	int	y;

	if (all->num_no > 0)
		print_array(all->not_exist, all->num_no, 1, all);
	y = 0;
	while (y < all->num_no)
		free(all->not_exist[y++]);
	free(all->not_exist);
	if (all->num_file > 0)
		print_array(all->files, all->num_file, 0, all);
	y = 0;
	while (y < all->num_file)
		free(all->files[y++]);
	free(all->files);
	if (all->num_dir > 0)
		print_array(all->directories, all->num_dir, 2, all);
	y = 0;
	while (y < all->num_dir)
		free(all->directories[y++]);
	free(all->directories);
}

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
	all->size_len = 0;
	all->tmp = NULL;
	all->blocks = 0;
}

/*
**	First lets set some values to zero.
** If number of argument is one (so only ft_ls), then we call function
** that outputs the current directory content.
** If argument count is more, then we copy the arguments to input_arr
** and continue to check flags.
*/

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
			return (1);
		print_output(&all);
	}
//	system ("leaks ft_ls");
	return (0);
}
