/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:54:26 by archid-           #+#    #+#             */
/*   Updated: 2019/06/30 01:30:51 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	index;
	t_int8	*dbuff;
	t_int8	*sbuff;

	index = -1;
	dbuff = (t_int8 *)dest;
	sbuff = (t_int8 *)src;
	if (sbuff < dbuff)
		while ((long int)--n >= 0)
			*(dbuff + n) = *(sbuff + n);
	else
		while (++index < n)
			*(dbuff + index) = *(sbuff + index);
	return (dest);
}
