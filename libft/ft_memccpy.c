/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 22:53:32 by archid-           #+#    #+#             */
/*   Updated: 2019/06/30 01:29:34 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;
	t_int8	*dbuff;
	t_int8	*sbuff;

	i = 0;
	dbuff = (t_int8 *)dest;
	sbuff = (t_int8 *)src;
	while (i < n)
	{
		dbuff[i] = sbuff[i];
		if (sbuff[i] == (t_int8)c)
			return (dbuff + i + 1);
		i++;
	}
	return (NULL);
}
