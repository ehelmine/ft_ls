/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 19:04:42 by ehelmine          #+#    #+#             */
/*   Updated: 2021/05/05 19:38:39 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <stdarg.h>
# include <string.h>
# include <stdlib.h>
# include "../libft/includes/libft.h"
# include "../ft_printf/includes/ft_printf.h"

typedef	struct s_struct
{
		char **not_exist;
		int a_flag;
		int l_flag;
		int reverse_flag;
		int big_r_flag;
		int t_flag;
}				t_struct;

#endif