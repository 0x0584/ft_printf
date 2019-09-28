/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:59:08 by archid-           #+#    #+#             */
/*   Updated: 2019/09/28 19:44:02 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

t_bigint	bigint_sub(t_bigint u, t_bigint v)
{
	t_bigint	result;
	t_bigint	order[2];
	t_u64		carry;
	t_u64		tmp;
	t_u32		i;

	i = 0;
	carry = 0UL;
	order[0] = bigint_maxof(u, v);
	order[1] = bigint_minof(u, v);
	ft_bzero(&result, sizeof(t_bigint));
	while (i < order[0].size)
	{
		tmp = (t_u64)order[0].block[i] - carry;
		carry = ((order[0].block[i] > 0 || (!order[0].block[i] && !carry))
					&& tmp >= (t_u64)order[1].block[i]) ? 0UL : 1UL;
		result.block[i] = (t_u32)((tmp + (carry ? 1UL << 32 : 0UL)
							- (t_u64)order[1].block[i]) & BLOCK_MASK);
		i++;
	}
	result.size = bigint_size(result);
	return (result);
}

t_bigint	bigint_insub(t_bigint *u, t_bigint v)
{
	return (*u = bigint_sub(*u, v));
}
