/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_bls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:59:08 by archid-           #+#    #+#             */
/*   Updated: 2019/09/28 19:32:33 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

t_bigint	bigint_bls(t_bigint u, t_u32 shift)
{
	t_bigint	result;
	t_u32		i;

	if (!shift)
		return (bigint_dup(u));
	i = BLOCK_MAX;
	ft_bzero(&result, sizeof(t_bigint));
	if (!(shift % BLOCK_SIZE))
		while (--i >= (shift / BLOCK_SIZE))
			result.block[i] = u.block[i - (shift / BLOCK_SIZE)];
	else
	{
		while (--i >= (shift / BLOCK_SIZE + 1))
			result.block[i] = (u.block[i - (shift / BLOCK_SIZE + 1)]
								>> (BLOCK_SIZE - (shift % BLOCK_SIZE)))
				| (u.block[i - (shift / BLOCK_SIZE)]
					<< (shift % BLOCK_SIZE));
		result.block[i] = u.block[i - (shift / BLOCK_SIZE)]
			<< (shift % BLOCK_SIZE);
	}
	result.size = bigint_size(result);
	return (result);
}

t_bigint	bigint_inbls(t_bigint *u, t_u32 shift)
{
	return (*u = bigint_bls(*u, shift));
}
