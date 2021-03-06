/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:15:24 by ehelmine          #+#    #+#             */
/*   Updated: 2021/07/14 15:54:42 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int	ft_exit_call(int i, char c)
{
	if (i == 1)
	{
		write(1, "ft_ls: illegal option -- ", 26);
		write(1, &c, 1);
		write(1, "\nusage: ft_ls [-Ralrt] [file ...]\n", 34);
	}
	exit (1);
}
