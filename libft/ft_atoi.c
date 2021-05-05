/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 10:20:07 by ehelmine          #+#    #+#             */
/*   Updated: 2021/05/01 16:48:16 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	x;
	int	res;

	x = 1;
	i = 0;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			x = -1;
		i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] >= 48 && str[i] <= 57)
			res = res * 10 + (str[i] - 48);
		else
			return (res * x);
		i++;
	}
	return (res * x);
}
