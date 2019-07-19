/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_digitcount_128bit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 03:23:56 by archid-           #+#    #+#             */
/*   Updated: 2019/07/19 03:26:48 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_int32		ft_digitcount_128bit(t_int128 n)
{
	t_int32		count;
	t_uint128	u;

	if (n == 0)
		return (1);
	u = (n < 0) ? -n : n;
	count = 1 + (n < 0);
	while (u / 10)
	{
		u /= 10;
		count++;
	}
	return (count);
}