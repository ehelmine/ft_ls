/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 09:06:37 by ehelmine          #+#    #+#             */
/*   Updated: 2021/05/01 16:30:47 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Takes as a parameter the address of a string that need to be
** freed with free(3), then sets its pointer to NULL.
*/

#include "libft.h"

void	ft_strdel(char **as)
{
	free(*as);
	*as = NULL;
	return ;
}
