/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 12:39:09 by ehelmine          #+#    #+#             */
/*   Updated: 2021/05/01 16:48:27 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** DESCRIPTION
**   The strdup() function allocates sufficient memory for a copy of the
**   string s1, does the copy, and returns a pointer to it.  The pointer may
**   subsequently be used as an argument to the function free(3).
**
**   If insufficient memory is available, NULL is returned and errno is set to
**   ENOMEM.
*/

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	src_sze;
	size_t	i;
	char	*dupstr;

	src_sze = ft_strlen(s);
	dupstr = (char *)malloc(sizeof(*dupstr) * (src_sze + 1));
	if (dupstr == NULL)
		return (NULL);
	i = 0;
	while (i < src_sze)
	{
		dupstr[i] = s[i];
		i++;
	}
	dupstr[i] = '\0';
	return (dupstr);
}
