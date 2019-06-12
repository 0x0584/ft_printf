/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 22:09:19 by archid-           #+#    #+#             */
/*   Updated: 2019/04/07 06:54:25 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	t_byte	*buff;

	i = 0;
	buff = (t_byte *)s;
	while (i < n)
		if (buff[i] == (t_byte)c)
			return (buff + i);
		else
			i++;
	return (NULL);
}
