/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 14:11:24 by ehelmine          #+#    #+#             */
/*   Updated: 2021/05/05 19:26:08 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"
#include <sys/stat.h>
#include <dirent.h>
#define MAX_LINES 10000

/*
** Sorting function, which checks the list of files and directories
** and checks it is ascending sort.
*/

void	sort_asc(char list[MAX_LINES][__DARWIN_MAXNAMLEN], int ii)
{
	char temp[__DARWIN_MAXNAMLEN];
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

int	main(int argc, char **argv)
{
	DIR				*dir;
	struct dirent	*dp;
	struct stat		buf;
	char			list[MAX_LINES][__DARWIN_MAXNAMLEN];
	int i;
	int ii;
	int x;
	char input_arr[MAX_LINES][__DARWIN_MAXNAMLEN];

	i = 0;
	ii = 0;
	while (i < argc)
		ft_strcpy(input_arr[i++], argv[ii++]);
	input_arr[i][0] = '\0';
	i = 1;
	while (i < argc)
	{
		ii = 0;
		stat(argv[i], &buf);
		dir = opendir(argv[i]);
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
	return (0);
}
