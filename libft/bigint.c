/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 01:01:43 by archid-           #+#    #+#             */
/*   Updated: 2019/07/26 20:35:00 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

static char		*escape_unwanted(const char *str)
{
	size_t index;

	index = 0;
	UNLESS_RET(str, NULL);
	while (str[index] && str[index] != '-'
				&& (!ft_isdigit(str[index])
					|| (str[index] == '0' && str[index + 1])))
		index++;	
	return ((char *)str + index);
}

static t_bigint		*bigint_maxof(t_bigint *big1, t_bigint *big2)
{
	t_uint32		index;
	t_int8			diff;

	index = 0;
	while (index < big1->ten_exp)
	{
		diff = (big1->base[index] - big2->base[index]);
		ASSERT_RET(diff < 0, big2);
		ASSERT_RET(diff > 0, big1);
		ASSERT_RET(big1->base[index] && !big2->base[index], big1);
		ASSERT_RET(big2->base[index] && !big1->base[index], big2);
		index++;
	}
	return (big1);
}

t_bigint        *bigint_new(const char *big_number)
{
    t_bigint        *big;
	char			*biggy;

    UNLESS_RET(big_number, NULL);
    UNLESS_RET(big = ALLOC(t_bigint *, 1, sizeof(t_bigint)), NULL);
	biggy = escape_unwanted(big_number);
	if (*biggy && *biggy == '-')
	{
		big->sign = true;
		biggy++;
	}
    big->ten_exp = ft_strlen(biggy);
	big->base = ft_strdup(biggy);	
    return (big);
}

t_bigint		*bigint_cmp(t_bigint *b1, t_bigint *b2, t_bigint_cmp cmp)
{
	t_bigint *big[2];
	
	UNLESS_RET(b1 && b2, NULL);
	ASSERT_RET(b1->ten_exp > b2->ten_exp, b1);
	ASSERT_RET(b2->ten_exp > b1->ten_exp, b2);
	big[0] = bigint_maxof(b1, b2);
	big[1] = (big[0] == b1) ? b2 : b1;
	return (big[cmp == BIGINT_MAXOF ? 0 : 1]);
}

void			bigint_free(t_bigint **big_number)
{
	if (*big_number)
	{
		free((*big_number)->base);
		free(*big_number);
		*big_number = NULL;
	}
}
