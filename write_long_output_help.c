/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_long_output_help.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:19:30 by ehelmine          #+#    #+#             */
/*   Updated: 2021/06/30 14:49:29 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	total_number_of_blocks(t_all *all)
{
	write(1, "total ", 6);
	ft_putnbr(all->blocks);
	write(1, "\n", 1);
}

void	print_time_and_name(char *str, char *file, char *arrow, char *link)
{
	if (ft_strcmp(link, "") != 0)
		ft_printf("%s %s %s %s\n", str + 4, file, arrow, link);
	else
		ft_printf("%s %s\n", str + 4, file);
}

char	*get_link_name(char *path, struct stat buf)
{
	char	*ptr;

	ptr = (char *)malloc(sizeof(char) * (buf.st_size + 1));
	if (ptr == NULL)
		exit(1);
	readlink(path, ptr, buf.st_size + 1);
	ptr[buf.st_size] = '\0';
	return (ptr);
}

void	modify_time(char *str, time_t now, time_t mod_time)
{
	char tmp[3];
	
//	ft_printf("this is time |%s|\n", str);
	if (str[4] >= 'A' && str[4] <= 'S')
	{
		tmp[0] = ' ';
		if (str[8] >= '1' && str[8] <= '3')
			tmp[0] = str[8];
		tmp[1] = str[9];
		str[7] = str[4];
		str[8] = str[5];
		str[9] = str[6];
		str[4] = tmp[0];
		str[5] = tmp[1];
		str[6] = ' ';
	}
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
	all->if_device = 0;
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
