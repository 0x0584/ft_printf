/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:45:29 by archid-           #+#    #+#             */
/*   Updated: 2019/04/07 06:53:40 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
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
		i++;
	}
	return (dbuff);
}
