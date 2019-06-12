/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_memdup.c										:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <marvin@42.fr>						+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/04/07 07:06:13 by archid-		   #+#	  #+#			  */
/*	 Updated: 2019/04/08 10:37:29 by archid-		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(const void *mem, size_t n)
{
	t_byte *buff;

	if (!(buff = ALLOC(t_byte *, n, sizeof(t_byte))))
		return (NULL);
	return (ft_memcpy(buff, mem, n));
}
