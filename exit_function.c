/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:15:24 by ehelmine          #+#    #+#             */
/*   Updated: 2021/05/14 15:54:17 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int		ft_exit_call(int i, char c)
{
	if (i == 1)
	{
		write(1, "ls: illegal option -- ", 23);
		write(1, &c, 1);
		write(1, "\nusage: ls [-Ralrt] [file ...]\n", 32);
	}
	else if (i == 2)
		write(1, "malloc fail\n", 13);
	exit (1);
}