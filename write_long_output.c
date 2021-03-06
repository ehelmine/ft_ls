/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_long_output.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 14:08:48 by ehelmine          #+#    #+#             */
/*   Updated: 2021/07/14 17:59:32 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void	finish_long_output(struct stat buf, t_all *all, char *path,
	char *file)
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
	link = NULL;
	arrow = NULL;
	if (S_ISLNK(buf.st_mode) != 0)
	{
		link = get_link_name(path, buf);
		arrow = ft_strdup("->");
		check_if_null((void *)arrow);
	}
	if (all->check == 1)
		free(path);
	print_long_output(buf, all, pwd, grp);
	print_time_and_name(str, file, arrow, link);
	if (S_ISLNK(buf.st_mode) != 0)
		free_two((void *)link, (void *)arrow);
}

static void	set_permission_to_output2(char output[11], struct stat buf)
{
	if (buf.st_mode & S_ISGID)
	{
		output[6] = 'S';
		if (buf.st_mode & S_IXGRP)
			output[6] = 's';
	}
	else if (buf.st_mode & S_IXGRP)
		output[6] = 'x';
	if (buf.st_mode & S_IROTH)
		output[7] = 'r';
	if (buf.st_mode & S_IWOTH)
		output[8] = 'w';
	if (buf.st_mode & S_ISVTX)
	{
		output[9] = 'T';
		if (buf.st_mode & S_IXOTH)
			output[9] = 't';
	}
	else if (buf.st_mode & S_IXOTH)
		output[9] = 'x';
}

static void	set_permission_to_output(char output[11], struct stat buf,
	t_all *all, char *path)
{
	check_file_type(output, buf, all);
	if (buf.st_mode & S_IRUSR)
		output[1] = 'r';
	if (buf.st_mode & S_IWUSR)
		output[2] = 'w';
	if (buf.st_mode & S_ISUID)
	{
		if (buf.st_mode & S_IXUSR)
			output[3] = 's';
		else
			output[3] = 'S';
	}
	else if (buf.st_mode & S_IXUSR)
		output[3] = 'x';
	if (buf.st_mode & S_IRGRP)
		output[4] = 'r';
	if (buf.st_mode & S_IWGRP)
		output[5] = 'w';
	all->xattr = (int)listxattr(path, NULL, 10000, XATTR_NOFOLLOW);
	if (all->xattr > 0)
		output[10] = '@';
	set_permission_to_output2(output, buf);
}

static void	lstat_long_output(t_all *all, char *path, char *file, int x)
{
	all->e = lstat(path, &all->b_s);
	if (all->e == -1 && S_ISDIR(all->b_s.st_mode) == 0)
	{
		all->e = stat(path, &all->b_s);
		if (all->b_s.st_mode & !S_IXUSR)
			exit (1);
		if (all->big_r_flag || all->e == -1)
		{
			if (all->check == 1)
				free(path);
			return ;
		}
	}
	if (x == 0)
		total_number_of_blocks(all);
	all->e = 0;
	while (all->e < 10)
		all->output[all->e++] = '-';
	all->output[10] = ' ';
	all->output[11] = '\0';
	set_permission_to_output(all->output, all->b_s, all, path);
	write(1, all->output, 11);
	all->e = 0;
	finish_long_output(all->b_s, all, path, file);
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
