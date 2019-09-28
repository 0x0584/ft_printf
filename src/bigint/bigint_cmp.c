/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_cmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:59:08 by archid-           #+#    #+#             */
/*   Updated: 2019/09/28 19:32:03 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

#define CMP(a, b)			(a > b ? 1 : -1)

int			bigint_cmp(t_bigint u, t_bigint v)
{
	t_u32 index;

	if (u.size != v.size)
		return (CMP(u.size, v.size));
	index = u.size;
	while (index--)
	{
		if (u.block[index] != v.block[index])
			return (CMP(u.block[index], v.block[index]));
	}
	return (0);
}

t_bigint	bigint_maxof(t_bigint u, t_bigint v)
{
	return (bigint_cmp(u, v) >= 0 ? u : v);
}

t_bigint	bigint_minof(t_bigint u, t_bigint v)
{
	return (bigint_cmp(u, v) >= 0 ? v : u);
}
