/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:37:22 by ehelmine          #+#    #+#             */
/*   Updated: 2021/05/06 20:42:39 by ehelmine         ###   ########.fr       */
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
	char *tmp;
	
	i = 0;
	y = 0;
	ii = 0;
	o = 0;
	if (path != NULL)
	{
		all->path = ft_strcat(all->path, path);
		all->path = ft_strcat(all->path, "/");
	}
	all->path = ft_strcat(all->path, directory);
//	all->path = ft_strcat(all->path, "/");
	dir = opendir(all->path);
	if (dir == NULL)
		return (1);
	if (all->big_r_flag)
	{
		other_dirrs = (int**)malloc(sizeof(int*) * 2);
		if (other_dirrs == NULL)
			return (-1);
		other_dirrs[o] = (int*)malloc(sizeof(int) * 1000);
		if (other_dirrs[o] == NULL)
			return (-1);
	}
	while (((dp = readdir(dir)) != NULL))
	{
		if (dp->d_name[0] != '.')
			ft_strcpy(list[ii++], dp->d_name);
	}
	list[ii][0] = '\0';
	sort_asc(list, ii);
	x = 0;
	ft_putstr(all->path);
	all->path = ft_strcat(all->path, "/");
	write(1, ":\n", 3);
	while (x < ii)
	{
		if (all->big_r_flag)
		{
			if (check_directory(list[x], all) != 0)
				other_dirrs[0][o++] = x;
		}
// TASSA KOHTI MENE HAKEMAAN LISATIETOJA KIRJOITETTAVAKSI ENNEN
// SEURAAVAN RIVIN TOTEUTTAMISTA, JOS PIKKU_L ON OLEMASSA! 
// eli if (all->l == 1)
//			long_output(list[x]);
// HUOLESTU MYOS char list[][] MYOHEMMIN!!!
		ft_printf("%s\n", list[x++]);
	}
	in = 0;
	if (all->big_r_flag)
	{
		while (in < o)
		{
			ft_printf("in the loop in %i and o %o\n", in, o);
			ft_putstr("\n");
			intti = other_dirrs[0][in];
			open_and_write_directory(all, list[intti], path);
			ft_printf("back from openwrite\n");
			// MIETI MITEN SAAT PATHIN TALTEEN!!! TAMA EI SAATANA TOIMI
			in++;
		}
	}
	ft_printf("i %i and o %i\n", i, o);
	return (1);
}