/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_long_output_help.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:19:30 by ehelmine          #+#    #+#             */
/*   Updated: 2021/06/03 18:13:08 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	total_number_of_blocks(t_all *all)
{
	write(1, "total ", 7);
	ft_putnbr(all->blocks);
	write(1, "\n", 2);
}

void	print_time_and_name(char *str, char *file, char *arrow, char *link)
{
	ft_printf("%s %s %s %s\n", str + 4, file, arrow, link);
}

char	*get_link_name(char *path, struct stat buf, t_all *all)
{
	char	*ptr;

	ptr = (char *)malloc(sizeof(char) * 256);
	if (ptr == NULL)
		exit(1);
	readlink(path, ptr, buf.st_size + 1);
	if (all->check == 1)
		free(path);
	return (ptr);
}

void	modify_time(char *str, time_t now, time_t mod_time)
{
	if (now - mod_time < 15778463)
		str[16] = '\0';
	else
	{
		str[10] = ' ';
		str[11] = ' ';
		str[12] = str[20];
		str[13] = str[21];
		str[14] = str[22];
		str[15] = str[23];
		str[16] = '\0';
	}
}

void	check_file_type(char output[11], struct stat buf, t_all *all)
{
	if (S_ISDIR(buf.st_mode) != 0)
		output[0] = 'd';
	else if (S_ISREG(buf.st_mode) != 0)
		output[0] = '-';
	else if (S_ISLNK(buf.st_mode) != 0)
		output[0] = 'l';
	else if (S_ISCHR(buf.st_mode) != 0)
	{
		output[0] = 'c';
		all->if_device = 1;
	}
	else if (S_ISBLK(buf.st_mode) != 0)
	{
		output[0] = 'b';
		all->if_device = 1;
	}
	else if (S_ISFIFO(buf.st_mode) != 0)
		output[0] = 'p';
	else if (S_ISSOCK(buf.st_mode) != 0)
		output[0] = 's';
}
