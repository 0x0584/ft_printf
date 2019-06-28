/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_itoa.c											:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <marvin@42.fr>						+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/04/07 04:00:37 by archid-		   #+#	  #+#			  */
/*   Updated: 2019/06/27 16:41:26 by archid-          ###   ########.fr       */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char		*buff;
	t_int8		index;
	t_uint16	u;

	index = ft_digitcount(n) + 1;
	if (!(buff = ALLOC(char *, index, sizeof(char))))
		return (NULL);
	u = (n < 0) ? -n : n;
	if (n < 0)
		buff[0] = '-';
	while (index-- > 1 + (n < 0))
	{
		buff[index - 1] = u % 10 + '0';
		u /= 10;
	}
	return (buff);
}
