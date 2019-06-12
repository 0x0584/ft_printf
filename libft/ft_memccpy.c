/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 22:53:32 by archid-           #+#    #+#             */
/*   Updated: 2019/04/07 06:53:51 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;
	t_byte	*dbuff;
	t_byte	*sbuff;

	i = 0;
	dbuff = (t_byte *)dest;
	sbuff = (t_byte *)src;
	while (i < n)
	{
		dbuff[i] = sbuff[i];
		if (sbuff[i] == (t_byte)c)
			return (dbuff + i + 1);
		i++;
	}
	return (NULL);
}
