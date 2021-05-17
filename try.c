/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:37:22 by ehelmine          #+#    #+#             */
/*   Updated: 2021/05/17 13:17:56 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	total_number_of_blocks(t_all *all)
{
	write(1, "total ", 7);
	ft_putnbr(all->blocks);
	write(1, "\n", 2);
}

void	check_number_of_links(char list[800][600], t_all *all, char *path, int ii)
{
	int len;
	struct stat buf;
	char		*tmp;
	int i;
	int x;

	x = 0;
	if (path != NULL)
	{
		if (path[ft_strlen(path) - 1] != '/')
			path = ft_strcat(path, "/");
	}
	while (x < ii)
	{
		tmp = NULL;
		if (path != NULL)
		{
			tmp = ft_strjoin(path, list[x]);
			if (tmp == NULL)
				exit (1);
		}
		if (path == NULL)
			tmp = list[x];
		i = stat(tmp, &buf);
		if (i == -1)
			exit (1);
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
		if (path != NULL)
			free(tmp);
		x++;
	}
}

void	write_long_output3(struct stat buf, t_all *all, char *output)
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
//		ft_printf("real len 2 %i\n", real_len);
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
		ft_printf("%s  %s%i %s %llu %s %lli %s ", output, empty, links, pwd->pw_name, (unsigned long long)buf.st_gid, empty2, buf.st_size, str + 4);
	else if (grp != NULL && pwd == NULL)
		ft_printf("%s  %s%i %llu %s %s %lli %s ", output, empty, links, (unsigned long long)buf.st_uid, grp->gr_name, empty2, buf.st_size, str + 4);
	else if (grp == NULL && pwd == NULL)
		ft_printf("%s  %s%i %llu %llu %s %lli %s ", output, empty, links, (unsigned long long)buf.st_uid, (unsigned long long)buf.st_gid, empty2, buf.st_size, str + 4);
	else
		ft_printf("%s  %s%i %s %s %s %lli %s ", output, empty, links, pwd->pw_name, grp->gr_name, empty2, buf.st_size, str + 4);
	free(empty);
	free(output);
	free(empty2);
}

void	set_permission_to_output(struct stat buf, char *output, int i)
{
	while (i < 10)
		output[i++] = '-';
	if (S_ISDIR(buf.st_mode))
		output[0] = 'd';
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
	output[10] = '\0';
}

void	write_long_output2(struct stat buf, t_all *all)
{
	int i;
	char *output;

	i = 0;
	output = (char *)malloc(sizeof(char) * 15);
	if (output == NULL)
		ft_exit_call(2, '0');
	set_permission_to_output(buf, output, i);
	write_long_output3(buf, all, output);
}

void	write_long_output(char *file, t_all *all, char *path)
{
	struct stat	buf;
	char		*tmp;
	int			i;

	tmp = NULL;
	if (path != NULL)
	{
		if (path[ft_strlen(path) - 1] != '/')
			path = ft_strcat(path, "/");
		tmp = ft_strjoin(path, file);
		if (tmp == NULL)
			return ;
	}
	if (path == NULL)
		tmp = file;
	i = stat(tmp, &buf);
	if (tmp != NULL)
		free(tmp);
	if (i == -1 && !S_IFDIR)
		exit (1);
	write_long_output2(buf, all);
}

int		open_and_write_directory(t_all *all, char *directory, char *path)
{
	char			list[800][600];
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
		if (tmp == NULL)
			return (0);
		dir = opendir(tmp);
	}
//	ft_printf("begin path %s dir %s tmp %s\n\n", path, directory, tmp);
	if (dir == NULL)
	{
		if (path != NULL)
			free(tmp);
		exit(1);
	}
	if (all->big_r_flag)
	{
		other_dirrs = (int**)malloc(sizeof(int*) * 1);
		if (other_dirrs == NULL)
			exit (1);
		other_dirrs[o] = (int*)malloc(sizeof(int) * 1000);
		if (other_dirrs[o] == NULL)
			exit (1);
	}
	while ((dp = readdir(dir)))
	{
		if (dp == NULL)
		{
			if (ii == 0)
			{
				perror("couldn't open dir\n");
				exit (1);
			}
			else
				break ;
		}
		if (!all->a_flag)
		{
			if (dp->d_name[0] != '.')
				ft_strcpy(list[ii++], dp->d_name);
		}
		else
			ft_strcpy(list[ii++], dp->d_name);
	}
	closedir(dir);
	if (ii == 0)
	{
		if (path != NULL)
		{
			ft_putstr(tmp);
			free(tmp);
		}
		else
			ft_putstr(directory);
		write(1, ":\n", 3);
		return (0);
	}
	list[ii][0] = '\0';
	if (ii > 1)
	{
		if (all->t_flag)
		{
			if (path != NULL)
				sort_mod_time(list, ii, tmp, all);
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
	if (all->l_flag)
	{
		all->links_len = 0;
		all->size_len = 0;
		all->blocks = 0;
		if (path != NULL)
			check_number_of_links(list, all, tmp, ii);
		else
			check_number_of_links(list, all, directory, ii);
	}
	x = 0;
	while (x < ii)
	{
//		ft_printf("x %i ii %i before loop\n", x, ii);
		if (all->big_r_flag)
		{
			if (path == NULL)
			{
				if (check_directory(list[x], directory) != 0)
					other_dirrs[0][o++] = x;
			}
			else
			{
				if (check_directory(list[x], tmp) != 0)
					other_dirrs[0][o++] = x;
			}
		}
		if (all->l_flag)
		{
			if (x == 0)
				total_number_of_blocks(all);
			if (path == NULL)
			{
//				ft_printf("NULL dir %s tmp %s path %s   ", directory, tmp, path);
				write_long_output(list[x], all, directory);
			}
			else
			{
//				ft_printf("NO NULL thisdir %s dir %s tmp %s path %s   ", list[x], directory, tmp, path);
				write_long_output(list[x], all, tmp);
			}
		}
		ft_printf("%s\n", list[x++]);
	}
	in = 0;
	if (all->big_r_flag)
	{
//		ft_printf("in %i o %i\n", in, o);
		ft_putstr("\n");
		while (in < o)
		{
//			ft_printf("in %i o %i\n", in, o);
//			ft_printf("in %i other_dirrs[0][in] %i\n", in, other_dirrs[0][in]);
			intti = other_dirrs[0][in];
//			ft_printf("curdirectory %s tmp %s list_dir %s\n", directory, tmp, list[intti + 1]);
			if (path == NULL)
			{
//				ft_printf("null h\n");
				open_and_write_directory(all, list[intti], directory);
			}
			else if (path != NULL)
			{
//				ft_printf("not null h\n");
				open_and_write_directory(all, list[intti], tmp);
			}
//			ft_printf("back\n");
			in++;
		}
//		ft_printf("here\n");
	}
	if (all->big_r_flag)
	{
		free(other_dirrs[0]);
		free(other_dirrs);
	}
	if (path != NULL)
		free(tmp);
// TAALLA PITAA JOTENKI VAPAUTTAA TMP ILMAN ET KAIKKI MENEE VITUIKSI
//	ft_printf("hhh\n");
	return (1);
}