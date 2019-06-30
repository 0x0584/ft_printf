/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_memdup.c										:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <marvin@42.fr>						+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/04/07 07:06:13 by archid-		   #+#	  #+#			  */
/*   Updated: 2019/06/30 01:30:43 by archid-          ###   ########.fr       */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(const void *mem, size_t n)
{
	t_int8 *buff;

	if (!(buff = ALLOC(t_int8 *, n, sizeof(t_int8))))
		return (NULL);
	return (ft_memcpy(buff, mem, n));
}
