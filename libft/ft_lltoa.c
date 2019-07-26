/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lltoa.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 04:41:23 by archid-           #+#    #+#             */
/*   Updated: 2019/07/22 04:44:49 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_lltoa(t_int128 n)
{
	char		*buff;
	t_int16		index;
	t_uint128	u;

	index = ft_digitcount_128bit(n) + 1;
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
