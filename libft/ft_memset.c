/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 11:50:28 by ehelmine          #+#    #+#             */
/*   Updated: 2021/05/01 16:28:26 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**  DESCRIPTION
**  The memset() function writes len bytes of value c (converted to an
**  unsigned char) to the string b.
**  RETURN VALUES
**  The memset() function returns its first argument.
*/

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*p;
	size_t	y;

	y = c;
	i = 0;
	p = b;
	while (i < len)
	{
		p[i] = y;
		i++;
	}
	return (b);
}
