/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:54:26 by archid-           #+#    #+#             */
/*   Updated: 2019/04/10 00:33:33 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	index;
	t_byte	*dbuff;
	t_byte	*sbuff;

	index = -1;
	dbuff = (t_byte *)dest;
	sbuff = (t_byte *)src;
	if (sbuff < dbuff)
		while ((long int)--n >= 0)
			*(dbuff + n) = *(sbuff + n);
	else
		while (++index < n)
			*(dbuff + index) = *(sbuff + index);
	return (dest);
}
