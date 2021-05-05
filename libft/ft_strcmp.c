/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 12:36:56 by ehelmine          #+#    #+#             */
/*   Updated: 2021/05/01 15:58:33 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	int				x;
	int				i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	x = 0;
	while (s1[x] == s2[x] && s1[x] != '\0' && s2[x] != '\0')
	{
		x++;
	}
	i = (s1[x] - s2[x]);
	return (i);
}
