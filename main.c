/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 14:11:24 by ehelmine          #+#    #+#             */
/*   Updated: 2021/05/06 20:42:05 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

/*
** Sorting function, which checks the list of files and directories
** and checks it is ascending sort.
*/

void	sort_asc(char list[100][100], int ii)
{
	char temp[100];
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
/*
	char			list[MAX_LINES][__DARWIN_MAXNAMLEN];
	DIR				*dir;
	struct dirent	*dp;
	struct stat		buf;
	int i;
	int ii;
	int x;

	i = 1;
	while (i < argc)
	{
		ii = 0;
		stat(all->input_arr[i], &buf);
		dir = opendir(all->input_arr[i]);
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
		while (x < ii)
			ft_printf("%s\n", list[x++]);
		i++;
	}
	return (1);*/

void	write_only_ls(t_all *all)
{
	DIR				*dir;
	int i;
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
	print_and_free_array(all->not_exist, all->num_no, 1, all);
	print_and_free_array(all->files, all->num_file, 0, all);
	print_and_free_array(all->directories, all->num_dir, 2, all);
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
	all->num_file = 0;
	all->num_no = 0;
	all->num_dir = 0;
	all->p = 0;
	all->path = (char *)malloc(sizeof(char *) * 1000);
	if (all->path == NULL)
		return (-1);
	all->path_arr = (char **)malloc(sizeof(char *) * 1000);
	if (all->path_arr == NULL)
		return (-1);
	all->files = (char**)malloc(sizeof(char*) * (argc + 1));
	if (all->files == NULL)
		return (-1);
	all->not_exist = (char**)malloc(sizeof(char*) * (argc + 1));
	if (all->not_exist == NULL)
		return (-1);
	all->directories = (char**)malloc(sizeof(char*) * (argc + 1));
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
			all->directories[all->num_dir++] = ft_strdup(all->input_arr[i]);
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
	int i;
	int ii;
	int x;

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
				ft_exit_call(1);
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

int	main(int argc, char **argv)
{
	t_all	all;
	int		i;
	int		ii;
	int		x;

	i = 0;
	ii = 0;
	
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
		x = 0;
	//	ft_putnbr(all.num_dir);
	//	while (x < all.num_dir)
	//	{
	//		if (x > 1)
	//			sort_asc_arr(all.directories, all.num_dir);
	//		open_and_write_directory(&all, all.directories[x++]);
	//	}
	}
	/*	stat(argv[1], &buf);
		if (argc < 3)
		{
			if (argc == 2 && !(S_ISDIR(buf.st_mode)))
			{
				if (S_ISREG(buf.st_mode))
					ft_printf("%s\n", argv[1]);
				else
					ft_printf("ls: %s: No such file or directory\n", argv[1]);
				return (0);
			}
			dir = opendir(".");
			if (argc == 2)
				dir = opendir(argv[1]);
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
			x = 0;
			while (x < i)
				ft_printf("%s\n", list[x++]);
		}*/
//	}
//	system("leaks ft_ls");
	return (0);
}
