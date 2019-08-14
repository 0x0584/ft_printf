/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 22:47:50 by archid-           #+#    #+#             */
/*   Updated: 2019/07/26 16:46:10 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

t_bigint		*bigint_bigadd(t_bigint *big1, t_bigint *big2)
{
	t_bigint		*bigint;
	t_bigint		*big[2];
	char			*added;

	big[0] = bigint_cmp(big1, big2, BIGINT_MAXOF);
	big[1] = (big[0] == big1) ? big2 : big1;
	added = sum_as_str(big[0]->base, big[1]->base);
	bigint = bigint_new(added);
	ft_strdel(&added);
	return (bigint);
}

t_bigint		*bigint_bigmul(t_bigint *big1, t_bigint *big2)
{
	t_bigint		*bigint;
	char			*buff;

	if (!ft_strcmp(big1->base, "0") || !ft_strcmp(big2->base, "0"))
		bigint = bigint_new("0");
	else
	{
		buff = mul_as_str(big1->base, big2->base);
		bigint = bigint_new(buff);
		bigint->sign = (big1->sign ^ big2->sign);
		ft_strdel(&buff);
	}
	return (bigint);
}

t_bigint		*bigint_bigpow(t_bigint *big1, t_int32 power)
{
	t_bigint *big;
	t_bigint *tmp;

	if (power <= 0)
		return (bigint_init(1));
	else if (power == 1)
		return (bigint_new(big1->base));
	big = bigint_init(1);
	while (power--)
	{
		tmp = bigint_bigmul(big1, big);
		bigint_free(&big);
		big = tmp;
	}
	return (big);
}
