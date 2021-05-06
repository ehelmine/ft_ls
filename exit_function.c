/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:15:24 by ehelmine          #+#    #+#             */
/*   Updated: 2021/05/06 14:42:06 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int		ft_exit_call(int i)
{
	if (i == 1)
		ft_putstr("ls: not valid flag\nusage: ls [-Ralrt] [file ...]\n");
	exit (1);
}