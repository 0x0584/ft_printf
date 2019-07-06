/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_utf8tostr.c										:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <marvin@42.fr>						+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/06/28 23:08:36 by archid-		   #+#	  #+#			  */
/*	 Updated: 2019/07/02 17:08:56 by archid-		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

t_int64		ft_utf8tostr(t_int8 *dest, size_t destsz,
						 const t_int32 *wsrc, size_t srcsz)
{
	t_int64 i;
	t_int64 n_bytes[2];

	i = 0;
	ft_bzero(n_bytes, 2 * sizeof(t_int64));
	ft_bzero(dest, destsz);
	while (wsrc[i] && srcsz - i && destsz - n_bytes[1])
	{
		n_bytes[0] = ft_utf8tostr_ch(dest + n_bytes[1], wsrc[i++]);
		if (n_bytes[0] < 0)
		{
			ft_bzero(dest, destsz - n_bytes[1]);
			return (-1);
		}
		n_bytes[1] += n_bytes[0];
	}
	return (n_bytes[1]);
}
