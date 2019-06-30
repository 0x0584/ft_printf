/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:45:29 by archid-           #+#    #+#             */
/*   Updated: 2019/06/30 01:30:31 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
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
		i++;
	}
	return (dbuff);
}
