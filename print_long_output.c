/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long_output.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 13:30:20 by ehelmine          #+#    #+#             */
/*   Updated: 2021/06/22 13:30:37 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	print_long_output(struct stat buf, t_all *all, struct passwd *pwd,
	struct group *grp)
{
	if (grp == NULL && pwd != NULL)
		ft_printf(" %*i %s  %llu  ", all->links_len, buf.st_nlink,
			pwd->pw_name, (unsigned long long)buf.st_gid);
	else if (grp != NULL && pwd == NULL)
		ft_printf(" %*i %llu  %s  ", all->links_len, buf.st_nlink,
			(unsigned long long)buf.st_uid, grp->gr_name);
	else if (grp == NULL && pwd == NULL)
		ft_printf(" %*i %llu  %llu  ", all->links_len, buf.st_nlink,
			(unsigned long long)buf.st_uid, (unsigned long long)buf.st_gid);
	else
		ft_printf(" %*i %s  %s  ", all->links_len, buf.st_nlink,
			pwd->pw_name, grp->gr_name);
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
}