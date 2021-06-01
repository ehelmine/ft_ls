/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_long_output.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 14:08:48 by ehelmine          #+#    #+#             */
/*   Updated: 2021/06/01 20:17:47 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	total_number_of_blocks(t_all *all)
{
	write(1, "total ", 7);
	ft_putnbr(all->blocks);
	write(1, "\n", 2);
}

void	print_link_name(char *path)
{
	char	buf[80];

	readlink(path, buf, sizeof(buf));
	ft_printf(" -> %s", buf);
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

char	*malloc_empty(struct stat buf, int first_len, int x)
{
	int		real_len;
	char	*str;
	int		i;
	int		len;

	len = 0;
	if (x == 0)
		len = ft_check_int_len(buf.st_nlink);
	if (x == 1)
		len = ft_check_int_len(buf.st_size);
	real_len = first_len - len;
	str = (char *)malloc(sizeof(char) * (real_len + 1));
	check_if_null((void *)str);
	i = 0;
	while (i < real_len)
		str[i++] = ' ';
	str[real_len] = '\0';
	return (str);
}

void	write_long_output3(struct stat buf, t_all *all, char *path)
{
	struct passwd	*pwd;
	struct group	*grp;
	time_t			mod_time;
	time_t			now;
	char			*empty;
	char			*empty2;
	char			*str;

	empty = malloc_empty(buf, all->links_len, 0);
	empty2 = malloc_empty(buf, all->size_len, 1);
	pwd = getpwuid(buf.st_uid);
	grp = getgrgid(buf.st_gid);
	mod_time = buf.st_mtime;
	now = time(0);
	str = ctime(&mod_time);
	check_if_null((void *)str);
	modify_time(str, now, mod_time);
	if (grp == NULL && pwd != NULL)
		ft_printf("  %s%i %s %llu %s %lli %s ", empty, buf.st_nlink,
			pwd->pw_name, (unsigned long long)buf.st_gid, empty2, buf.st_size,
			str + 4);
	else if (grp != NULL && pwd == NULL)
		ft_printf("  %s%i %llu %s %s %lli %s ", empty, buf.st_nlink,
			(unsigned long long)buf.st_uid, grp->gr_name, empty2, buf.st_size,
			str + 4);
	else if (grp == NULL && pwd == NULL)
		ft_printf("  %s%i %llu %llu %s %lli %s ", empty, buf.st_nlink,
			(unsigned long long)buf.st_uid, (unsigned long long)buf.st_gid,
			empty2, buf.st_size, str + 4);
	else
		ft_printf("  %s%i %s %s %s %lli %s ", empty, buf.st_nlink, pwd->pw_name,
			grp->gr_name, empty2, buf.st_size, str + 4);
	if (S_ISLNK(buf.st_mode) != 0)
		print_link_name(path);
	if (all->check == 1)
		free(path);
	free(empty);
	free(empty2);
}

void	set_permission_to_output(char output[11], struct stat buf)
{
	if (S_ISDIR(buf.st_mode) != 0)
		output[0] = 'd';
	else if (S_ISREG(buf.st_mode) != 0)
		output[0] = '-';
	else if (S_ISLNK(buf.st_mode) != 0)
		output[0] = 'l';
	if (buf.st_mode & S_IRUSR)
		output[1] = 'r';
	if (buf.st_mode & S_IWUSR)
		output[2] = 'w';
	if (buf.st_mode & S_IXUSR)
		output[3] = 'x';
	if (buf.st_mode & S_IRGRP)
		output[4] = 'r';
	if (buf.st_mode & S_IWGRP)
		output[5] = 'w';
	if (buf.st_mode & S_IXGRP)
		output[6] = 'x';
	if (buf.st_mode & S_IROTH)
		output[7] = 'r';
	if (buf.st_mode & S_IWOTH)
		output[8] = 'w';
	if (buf.st_mode & S_IXOTH)
		output[9] = 'x';
}

void	write_long_output2(t_all *all, char *path)
{
	struct stat	buf;
	int			i;
	char		output[11];

	i = lstat(path, &buf);
	if (i == -1 && S_ISDIR(buf.st_mode) == 0)
		exit (1);
	i = 0;
	while (i < 10)
		output[i++] = '-';
	output[10] = '\0';
	set_permission_to_output(output, buf);
	write(1, output, 11);
	write_long_output3(buf, all, path);
}

void	write_long_output(char *file, t_all *all, const char *path)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	all->check = 0;
	if (path != NULL)
	{
		if (path[ft_strlen(path) - 1] != '/')
		{
			tmp2 = ft_strjoin(path, "/");
			if (tmp2 == NULL)
				exit (1);
			tmp = ft_strjoin(tmp2, file);
			free(tmp2);
		}
		else
			tmp = ft_strjoin(path, file);
		if (tmp == NULL)
			exit (1);
		all->check = 1;
	}
	else if (path == NULL)
		tmp = file;
	write_long_output2(all, tmp);
}
