/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:37:22 by ehelmine          #+#    #+#             */
/*   Updated: 2021/05/20 17:53:17 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	total_number_of_blocks(t_all *all)
{
	write(1, "total ", 7);
	ft_putnbr(all->blocks);
	write(1, "\n", 2);
}

void	check_number_of_links(char **list, t_all *all, const char *path, int ii)
{
	int len;
	struct stat buf;
	char		*tmp1;
	char		*tmp2;
	int i;
	int x;

	x = 0;
	tmp1 = NULL;
	tmp2 = NULL;
	if (path != NULL)
	{
		if (path[ft_strlen(path) - 1] != '/')
		{
			tmp1 = ft_strjoin(path, "/");
			if (tmp1 == NULL)
				exit (1);
		}
	}
	while (x < ii)
	{
		if (path != NULL)
		{
			if (tmp1 != NULL)
				tmp2 = ft_strjoin(tmp1, list[x]);
			else
				tmp2 = ft_strjoin(path, list[x]);
			if (tmp2 == NULL)
				exit (1);
		}
		if (path == NULL)
			tmp2 = list[x];
		i = lstat(tmp2, &buf);
		if (path != NULL)
			free(tmp2);
		if (i == -1 && !S_IFDIR)
		{
			ft_putstr("stat fail1\n");
			exit (1);
		}
		if (i == 0)
		{
//			ft_printf("tmp %s    ", tmp);
			len = ft_check_int_len(buf.st_nlink);
			if (len > all->links_len)
				all->links_len = len;
			len = ft_check_int_len(buf.st_size);
			if (len > all->size_len)
				all->size_len = len;
			all->blocks += buf.st_blocks;
//			ft_putnbr(buf.st_blocks);
		}
		x++;
	}
	if (tmp1 != NULL)
		free(tmp1);
}

void	print_link_name(char *path)
{
	char buf[80];
	
	readlink(path, buf, sizeof(buf));
	ft_printf(" -> %s", buf);
}

void	write_long_output3(struct stat buf, t_all *all, char *path)
{
	int links;
	int len;
	int i;
	struct passwd *pwd;
	struct group *grp;
	time_t mod_time;
	time_t now;
	int real_len;
	char *empty;
	char *empty2;
	char *str;

	links = buf.st_nlink;
	len = ft_check_int_len(links);
	real_len = all->links_len - len;
	empty = (char *)malloc(sizeof(char) * real_len + 1);
	if (empty == NULL)
		exit(1);
	i = 0;
	while (i < real_len)
		empty[i++] = ' ';
	empty[real_len] = '\0';
	len = ft_check_int_len(buf.st_size);
	real_len = all->size_len - len;
	empty2 = (char *)malloc(sizeof(char) * real_len + 1);
	if (empty2 == NULL)
		exit(1);
	i = 0;
	while (i < real_len)
		empty2[i++] = ' ';
	empty2[real_len] = '\0';
	pwd = getpwuid(buf.st_uid);
	grp = getgrgid(buf.st_gid);
	mod_time = buf.st_mtime;
	now = time(0);
	str = ctime(&mod_time);
	if (str == NULL)
		exit (1);
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
	if (grp == NULL && pwd != NULL)
		ft_printf("  %s%i %s %llu %s %lli %s ", empty, links, pwd->pw_name, (unsigned long long)buf.st_gid, empty2, buf.st_size, str + 4);
	else if (grp != NULL && pwd == NULL)
		ft_printf("  %s%i %llu %s %s %lli %s ", empty, links, (unsigned long long)buf.st_uid, grp->gr_name, empty2, buf.st_size, str + 4);
	else if (grp == NULL && pwd == NULL)
		ft_printf("  %s%i %llu %llu %s %lli %s ", empty, links, (unsigned long long)buf.st_uid, (unsigned long long)buf.st_gid, empty2, buf.st_size, str + 4);
	else
		ft_printf("  %s%i %s %s %s %lli %s ", empty, links, pwd->pw_name, grp->gr_name, empty2, buf.st_size, str + 4);
	if (S_ISLNK(buf.st_mode) != 0)
		print_link_name(path);
	if (all->check == 1)
		free(path);
	free(empty);
	free(empty2);
}

//		./ft_ls -lRa ../../  3.04s user 1.88s system 41% cpu 11.953 total
//	printf change
//		./ft_ls -lRa ../../  2.93s user 1.74s system 41% cpu 11.166 total
// after i and d
//		./ft_ls -lRa ../../  2.91s user 1.68s system 41% cpu 11.114 total

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
	int i;
	char output[11];

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

void	set_long_output_vals(t_all *all)
{
	all->check = 0;
	all->i = 0;
}

void	write_long_output(char *file, t_all *all, const char *path)
{
	char		*tmp;
	char		*tmp2;

	tmp = NULL;
	tmp2 = NULL;
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

int		open_and_write_directory(t_all *all, const char *directory, const char *path)
{
	char			**list;
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
	char *dir_tmp;

	i = 0;
	y = 0;
	ii = 0;
	o = 0;
	tmp = NULL;
	list = NULL;
	dir_tmp = NULL;
	other_dirrs = NULL;
	dir = NULL;
	dp = NULL;
//	ft_printf("dir very begin %s and path %s\n", directory, path);
	if (path == NULL)
		dir = opendir(directory);
	if (path != NULL)
	{
		dir_tmp = ft_strjoin(path, directory);
		if (dir_tmp == NULL)
			return (0);
		dir = opendir(dir_tmp);
	}
//	ft_printf("begin path %s dir %s tmp %s\n\n", path, directory, tmp);
	if (dir == NULL)
	{
		ft_printf("%s\nls: %s: %s\n", dir_tmp, directory, strerror(errno));
		if (path != NULL)
		{
			free(dir_tmp);
			dir_tmp = NULL;
		}
		return (0);
	}
	list = (char **)malloc(sizeof(char *) * 3000);
	if (list == NULL)
		exit (1);
	while ((dp = readdir(dir)))
	{
		if (dp->d_name[0] != '.')
		{
			list[ii] = ft_strnew(256);
			if (list[ii] == NULL)
				exit(1);
			ft_strcpy(list[ii++], dp->d_name);
		}
		else if (dp->d_name[0] == '.')
		{
			if (all->a_flag == 1)
			{
				list[ii] = ft_strnew(256);
				if (list[ii] == NULL)
					exit(1);
				ft_strcpy(list[ii++], dp->d_name);
			}
		}
	}
	closedir(dir);
	if (ii == 0)
	{
		if (path == NULL)
			ft_putstr(directory);
		else
		{
			ft_putstr(dir_tmp);
			free(dir_tmp);
			dir_tmp = NULL;
		}
		write(1, ":\n", 3);
		return (0);
	}
	list[ii] = NULL;
	if (all->big_r_flag)
	{
		other_dirrs = (int**)malloc(sizeof(int*) * 1);
		if (other_dirrs == NULL)
			exit (1);
		other_dirrs[o] = (int*)malloc(sizeof(int) * 800);
		if (other_dirrs[o] == NULL)
			exit (1);
	}
	if (ii > 1)
	{
		if (all->t_flag)
		{
			if (path != NULL)
				sort_mod_time(list, ii, dir_tmp, all);
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
		ft_putstr(dir_tmp);
		write(1, ":\n", 3);
	}
	if (all->l_flag)
	{
		all->links_len = 0;
		all->size_len = 0;
		all->blocks = 0;
		if (path != NULL)
			check_number_of_links(list, all, dir_tmp, ii);
		else
			check_number_of_links(list, all, directory, ii);
	}
	x = 0;
	while (x < ii)
	{
		if (all->big_r_flag)
		{
			if (path == NULL)
			{
				if (check_directory(list[x], directory, all) != 0)
					other_dirrs[0][o++] = x;
			}
			else
			{
				if (check_directory(list[x], dir_tmp, all) != 0)
					other_dirrs[0][o++] = x;
			}
		}
		if (all->l_flag)
		{
			if (x == 0)
				total_number_of_blocks(all);
			if (path == NULL)
				write_long_output(list[x], all, directory);
			else
				write_long_output(list[x], all, dir_tmp);
		}
		ft_printf("%s\n", list[x++]);
	}
	in = 0;
	check = 0;
	if (all->big_r_flag)
	{
		if (path == NULL)
			tmp = ft_strjoin(directory, "/");
		else
			tmp = ft_strjoin(dir_tmp, "/");
	}
	x = 0;
	while (in < ii)
	{
		if (all->big_r_flag && other_dirrs[0][x] == in && x < o)
		{
			intti = other_dirrs[0][x];
			write(1, "\n", 2);
			open_and_write_directory(all, list[intti], tmp);
			x++;
		}
		in++;
	}
	if (all->big_r_flag)
	{
		free(other_dirrs[0]);
		other_dirrs[0] = NULL;
		free(other_dirrs);
		other_dirrs = NULL;
		free(tmp);
		tmp = NULL;
	}
	if (path != NULL)
	{
		free(dir_tmp);
		dir_tmp = NULL;
	}
	x = 0;
	while (x < ii)
		free(list[x++]);
	free(list);
	return (1);
}
/*
while (any_array[y] != NULL)
	{
		free(any_array[y]);
		y++;
	}
	free(any_array);
	any_array = NULL;
	*/