/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_long_output.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 14:08:48 by ehelmine          #+#    #+#             */
/*   Updated: 2021/06/03 18:12:55 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"
#include <stdio.h>

void	print_long_output(struct stat buf, t_all *all, struct passwd *pwd,
	struct group *grp)
{
	if (grp == NULL && pwd != NULL)
		ft_printf("  %*i %s  %llu  ", all->links_len, buf.st_nlink,
			pwd->pw_name, (unsigned long long)buf.st_gid);
	else if (grp != NULL && pwd == NULL)
		ft_printf("  %*i %llu  %s  ", all->links_len, buf.st_nlink,
			(unsigned long long)buf.st_uid, grp->gr_name);
	else if (grp == NULL && pwd == NULL)
		ft_printf("  %*i %llu  %llu  ", all->links_len, buf.st_nlink,
			(unsigned long long)buf.st_uid, (unsigned long long)buf.st_gid);
	else
		ft_printf("  %*i %s  %s  ", all->links_len, buf.st_nlink,
			pwd->pw_name, grp->gr_name);
	if (all->if_device)
		ft_printf(" %d, %d ", my_major(buf.st_rdev), my_minor(buf.st_rdev));
	else if (grp == NULL)
		ft_printf(" %*llu ", all->size_len + (all->group_len
				- ft_check_int_len(buf.st_gid)),
			(unsigned long long)buf.st_size);
	else
		ft_printf(" %*llu ", all->size_len + (all->group_len
				- ft_strlen(grp->gr_name)), (unsigned long long)buf.st_size);
}

void	finish_long_output(struct stat buf, t_all *all, char *path, char *file)
{
	struct passwd	*pwd;
	struct group	*grp;
	char			*str;
	char			*link;
	char			*arrow;

	pwd = getpwuid(buf.st_uid);
	grp = getgrgid(buf.st_gid);
	str = ctime(&buf.st_mtime);
	check_if_null((void *)str);
	modify_time(str, time(0), buf.st_mtime);
	link = "";
	arrow = "";
	if (S_ISLNK(buf.st_mode) != 0)
	{
		link = get_link_name(path, buf, all);
		arrow = ft_strdup("->");
	}
	print_long_output(buf, all, pwd, grp);
	print_time_and_name(str, file, arrow, link);
	if (S_ISLNK(buf.st_mode) != 0)
	{
		free(link);
		free(arrow);
	}		
}

/* 
S_ISREG(m) is it a regular file?					- - Regular file.
S_ISDIR(m) directory?								d - Directory.
S_ISCHR(m) character device?						c - Character special file.
S_ISBLK(m) block device?							b - Block special file.
S_ISFIFO(m) FIFO (named pipe)?						p - FIFO.
S_ISLNK(m) symbolic link? (Not in POSIX.1-1996.)	l - Symbolic link.
S_ISSOCK(m) socket? (Not in POSIX.1-1996.)			s - Socket.

n - Network file.
st_rdev


*/

void	set_permission_to_output(char output[11], struct stat buf, t_all *all)
{
	all->if_device = 0;
	check_file_type(output, buf, all);
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

void	lstat_long_output(t_all *all, char *path, char *file, int x)
{
	struct stat	buf;
	int			i;
	char		output[11];

	i = lstat(path, &buf);
	if (i == -1 && S_ISDIR(buf.st_mode) == 0)
	{
		i = stat(path, &buf);
		if (buf.st_mode & !S_IXUSR)
			exit (1);
		return ;
	}
	if (x == 0)
		total_number_of_blocks(all);
	i = 0;
	while (i < 10)
		output[i++] = '-';
	output[10] = '\0';
	set_permission_to_output(output, buf, all);
	write(1, output, 11);
	finish_long_output(buf, all, path, file);
}

void	start_long_output(char *file, t_all *all, const char *path, int x)
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
	lstat_long_output(all, tmp, file, x);
}
