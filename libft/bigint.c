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
	while (str[index] && str[index] != '-'
				&& (!ft_isdigit(str[index])
					|| (str[index] == '0' && str[index + 1])))
		index++;
	return ((char *)str + index);
}

t_bigint        *bigint_new(const char *big_number)
{
    t_bigint        *big;
	char			*biggy;
    t_uint32        index;
	bool			flag;

    UNLESS_RET(big_number, NULL);
    UNLESS_RET(big = ALLOC(t_bigint *, 1, sizeof(t_bigint)), NULL);
	biggy = escape_unwanted(big_number);
	if (*biggy && *biggy == '-')
		big->sign = *biggy++ == '-' ? true : false;
    big->ten_exp = ft_strlen(biggy);
    if (!(big->couple_digits = ALLOC(t_uint8 *, BIGINT_COUPLE_SIZE(big),
									 sizeof(t_uint8))))
    {
        bigint_free(&big);
        return (NULL);
    }
    index = 0;
    flag = false;
    while (*biggy && ft_isdigit(*biggy))
		if (flag ^= true)
			big->couple_digits[index] = ((*biggy++ - '0') << 4) | 0x0f;
		else
			big->couple_digits[index++] &= (*biggy++ - '0') | 0xf0;
    return (big);
}

char			*bigint_tostr(t_bigint *big)
{
	t_uint32		temp[2];
	t_uint32		index;
	char			*buff;

	temp[1] = BIGINT_COUPLE_SIZE(big);
	buff = ft_strnew(big->ten_exp + big->sign);
	index = 0;
	if (big->sign)
		buff[index++] = '-';
	temp[0] = 0;
	while (temp[0] < temp[1])
	{
		buff[index++] = (big->couple_digits[temp[0]] >> 4) + '0';
		if ((big->couple_digits[temp[0]] & 0x0F) != 0x0F)
			buff[index++] = (big->couple_digits[temp[0]] & 0x0F) + '0';
		temp[0]++;
	}
	return (buff);
}

t_bigint		*bigint_maxof(t_bigint *big1, t_bigint *big2)
{
	t_uint32		temp[2];
	bool			flag;
	t_int8			diff;
	t_int8			is_nega;

	UNLESS_RET(big1 && big2, NULL);
	ASSERT_RET((!big1->sign && big2->sign), big1);
	ASSERT_RET((!big2->sign && big1->sign), big2);
	ASSERT_RET(big1->ten_exp > big2->ten_exp, big1->sign ? big2 : big1);
	ASSERT_RET(big2->ten_exp > big1->ten_exp, big1->sign ? big1 : big2);
	is_nega = big1->sign && big2->sign ? -1 : 1;
	flag = false;
	temp[0] = 0;
	temp[1] = BIGINT_COUPLE_SIZE(big1);
	while (temp[0] < temp[1])
	{
		diff = is_nega * (!flag ?
			BIGINT_LD(big1, temp[0]) - BIGINT_LD(big2, temp[0]) :
			BIGINT_RD(big1, temp[0]) - BIGINT_RD(big2, temp[0]));
		if (flag ^= true)
		{
			ASSERT_RET(diff < 0, big2);
			ASSERT_RET(diff > 0, big1);
		}
		else
		{
			if (BIGINT_IS_RD(big1, temp[0]) && BIGINT_IS_RD(big2, temp[0]))
			{
				ASSERT_RET(diff < 0, big2);
				ASSERT_RET(diff > 0, big1);
			}
			ASSERT_RET(BIGINT_IS_RD(big1, temp[0]) &&
					   !BIGINT_IS_RD(big2, temp[0]), big1);
			ASSERT_RET(BIGINT_IS_RD(big2, temp[0]) &&
					   !BIGINT_IS_RD(big1, temp[0]), big2);
			temp[0]++;
		}
	}
	return (big1);
}

t_bigint		*bigint_minof(t_bigint *big1, t_bigint *big2)
{
	return (bigint_maxof(big2, big1) == big1 ? big2 : big1);
}

t_bigint		*bigint_init(t_int128 number)
{
	char		*num_as_str;
	t_bigint	*big;

	num_as_str = ft_lltoa(number);
	big = bigint_new(num_as_str);
	ft_strdel(&num_as_str);
	return (big);
}

void			bigint_refdel(void *o)
{
	t_bigint **bigref;
	
	bigref = o;
	bigint_free(bigref);
}

void			bigint_free(t_bigint **big_number)
{
	if (*big_number)
	{
		free((*big_number)->couple_digits);
		free(*big_number);
		*big_number = NULL;
	}
}

t_bigint		*bigint_clone(t_bigint *big)
{
	char		*foo;
	t_bigint	*clone;

	foo = bigint_tostr(big);
	clone = bigint_new(foo);
	ft_strdel(&foo);
	return (clone);
}
