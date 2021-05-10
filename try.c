/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:37:22 by ehelmine          #+#    #+#             */
/*   Updated: 2021/05/10 18:31:37 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int		open_and_write_directory(t_all *all, char *directory, char *path)
{
	char			list[100][100];
	DIR				*dir;
	struct dirent	*dp;
	int i;
	int x;
	int ii;
	int y;
	int **other_dirrs;
	int o;
	int in;
	int intti;
	int check;
	char *tmp;

	i = 0;
	y = 0;
	ii = 0;
	o = 0;
	tmp = NULL;
//	ft_printf("dir very begin %s and path %s\n", directory, path);
	if (path == NULL)
		dir = opendir(directory);
	if (path != NULL)
	{
		if (path[0] == '.' && path[1] == '\0')
			path = ft_strcat(path, "/");
		else if (path[ft_strlen(path) - 1] != '/')
			path = ft_strcat(path, "/");
		tmp = ft_strjoin(path, directory);
		dir = opendir(tmp);
	}
//	ft_printf("begin path %s dir %s tmp %s\n\n", path, directory, tmp);
	if (dir == NULL)
	{
		if (path != NULL)
			free(tmp);
		return (1);
	}
	if (all->big_r_flag)
	{
		other_dirrs = (int**)malloc(sizeof(int*) * 1);
		if (other_dirrs == NULL)
			return (-1);
		other_dirrs[o] = (int*)malloc(sizeof(int) * 1000);
		if (other_dirrs[o] == NULL)
			return (-1);
	}
	while (((dp = readdir(dir)) != NULL))
	{
		if (dp->d_name[0] != '.' || (dp->d_name[0] == '.' && all->a_flag))
			ft_strcpy(list[ii++], dp->d_name);
	}
	list[ii][0] = '\0';
	if (ii != 0)
	{
		if (all->t_flag)
		{
			if (path != NULL)
				sort_mod_time(list, ii, path, all);
			else
				sort_mod_time(list, ii, directory, all);
		}
		else
			sort_asc(list, ii);
	}
	x = 0;
	check = 0;
	if (path != NULL)
	{
		ft_putstr(tmp);
		write(1, ":\n", 3);
	}
//	ft_printf("directory %s tmp %s path %s\n", directory, tmp, path);
	while (x < ii)
	{
		if (all->big_r_flag)
		{
			if (check_directory(list[x], all, path) != 0)
				other_dirrs[0][o++] = x;
		}
// TASSA KOHTI MENE HAKEMAAN LISATIETOJA KIRJOITETTAVAKSI ENNEN
// SEURAAVAN RIVIN TOTEUTTAMISTA, JOS PIKKU_L ON OLEMASSA! 
// eli if (all->l == 1)
//			long_output(list[x]);
// HUOLESTU MYOS char list[][] MYOHEMMIN!!!
		ft_printf("%s\n", list[x++]);
	}
//	ft_printf("before loop i %i o %o ii %i path %s dir %s tmp %s\n", i, o, ii, path, directory, tmp);
	in = 0;
	if (all->big_r_flag)
	{
		ft_putstr("\n");
		while (in < o)
		{
			intti = other_dirrs[0][in];
//			ft_printf("in the loop in %i and o %o and tmp %s\n", in, o, tmp);
			if (path == NULL)
				open_and_write_directory(all, list[intti], directory);
			if (path != NULL)
				open_and_write_directory(all, list[intti], tmp);
//			ft_printf("back from openwrite\n");
			in++;
		}
	}
	x = 0;
//	ft_printf("i %i and o %i\n", i, o);
	if (all->big_r_flag)
	{
		while (x < 1)
			free(other_dirrs[x++]);
		free(other_dirrs);
	}
// TAALLA PITAA JOTENKI VAPAUTTAA TMP ILMAN ET KAIKKI MENEE VITUIKSI
	return (1);
}