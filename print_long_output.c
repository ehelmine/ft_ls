/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long_output.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 13:30:20 by ehelmine          #+#    #+#             */
/*   Updated: 2021/06/30 15:32:58 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	print_long_output(struct stat buf, t_all *all, struct passwd *pwd,
	struct group *grp)
{
	int i;

	if (pwd != NULL)
	{
		ft_printf(" %*i %s  ", all->links_len, buf.st_nlink,
			pwd->pw_name);
		i = ft_strlen(pwd->pw_name);
		while (i++ < all->user_len)
			write(1, " ", 1);
	}
	else
	{
		ft_printf(" %*i %llu  ", all->links_len, buf.st_nlink,
			(unsigned long long)buf.st_uid);
		i = ft_check_int_len(buf.st_uid);
		while (i++ < all->user_len)
			write(1, " ", 1);
	}
	if (grp == NULL)
	{
		ft_printf("%llu  ", (unsigned long long)buf.st_gid);
		i = ft_check_int_len(buf.st_gid);
		while (i++ < all->group_len)
			write(1, " ", 1);
	}
	else
	{
		ft_printf("%s  ", grp->gr_name);
		i = ft_strlen(grp->gr_name);
		while (i++ < all->group_len)
			write(1, " ", 1);
	}		
	if (all->if_device)
		ft_printf(" %d, %d ", my_major(buf.st_rdev), my_minor(buf.st_rdev));
	else if (grp == NULL)
		ft_printf("%*i ", all->size_len + (all->group_len
				- (int)ft_check_int_len(buf.st_gid)),
			(unsigned long long)buf.st_size);
	else
		ft_printf("%*i ", all->size_len + (all->group_len
				- (int)ft_strlen(grp->gr_name)),
			(unsigned long long)buf.st_size);
	all->tmp[0] = ' ';
	all->tmp[1] = ' ';
}
