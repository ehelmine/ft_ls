/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_array_help_functions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 15:46:53 by ehelmine          #+#    #+#             */
/*   Updated: 2021/07/14 17:18:47 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

char	**open_directory_is_null(t_all *all, const char *directory, const char
	*path, char *dir_tmp)
{
	if (dir_tmp && (all->num_dir > 1 || all->big_r_flag || all->num_file
			|| all->num_no))
		ft_printf("%s:\n", dir_tmp);
	else if (directory && (all->num_dir > 1 || all->big_r_flag
			|| all->num_file || all->num_no))
		ft_printf("%s:\n", directory);
	ft_printf("ft_ls: %s: %s\n", directory, strerror(errno));
	if (ft_strcmp(path, "") != 0)
		free(dir_tmp);
	return (NULL);
}

int	check_if_link_and_rights(t_all *all, const char *directory, char *dir_tmp,
	const char *path)
{
	char		*new_dir;

	if (all->l_flag)
		return (1);
	if (ft_strcmp(path, "") == 0)
	{
		if (lstat(directory, &all->b_s) == -1)
			return (1);
		new_dir = get_link_name((char *)directory, all->b_s);
	}
	else
	{
		if (lstat(dir_tmp, &all->b_s) == -1)
			return (1);
		new_dir = get_link_name(dir_tmp, all->b_s);
	}
	if (new_dir == NULL)
		return (1);
	if (lstat(new_dir, &all->b_s) == -1 || (all->b_s.st_mode & S_IXUSR))
	{
		free(new_dir);
		return (1);
	}
	free(new_dir);
	return (-1);
}
