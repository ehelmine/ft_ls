/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_no_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:22:07 by ehelmine          #+#    #+#             */
/*   Updated: 2021/05/20 15:49:02 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		write_no_flags(t_val *all)
{
	int i;

	i = 0;
	if (all->conv == 's')
	{
		if (all->str == NULL)
			write(1, "(null)", 7);
		else
		{
			while (all->str[i] != '\0')
				i++;
			write(1, all->str, i);
		}
	}
	else if (all->conv == 'i' || all->conv == 'd')
		ft_putnbr(all->num);
	return (1);
}