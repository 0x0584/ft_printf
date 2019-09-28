/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:59:08 by archid-           #+#    #+#             */
/*   Updated: 2019/09/28 19:31:18 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

t_bigint	bigint_init(uintmax_t val)
{
	t_bigint	big;
	t_s32		index;

	index = 0;
	ft_bzero(&big, sizeof(t_bigint));
	while (val && index < BLOCK_MAX)
	{
		big.block[index++] = (t_u32)(val & BLOCK_MASK);
		val >>= BLOCK_SIZE;
	}
	big.size = bigint_size(big);
	return (big);
}
