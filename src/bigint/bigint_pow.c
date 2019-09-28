/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_pow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:59:08 by archid-           #+#    #+#             */
/*   Updated: 2019/09/28 19:33:04 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

t_bigint		bigint_pow(t_bigint u, t_u32 exp)
{
	t_bigint	tmp;
	t_u32		exp2;

	tmp = bigint_init(1);
	if (exp == 0)
		return (tmp);
	exp2 = exp / 2;
	while (exp2--)
		tmp = bigint_mul(tmp, u);
	bigint_inmul(&tmp, tmp);
	if (exp % 2)
		bigint_inmul(&tmp, u);
	return (tmp);
}
