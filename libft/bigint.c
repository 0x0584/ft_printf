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

/* just like atoi's escape */
static char		*escape_unwanted(const char *str)
{
	size_t index;
	
	UNLESS_RET(str, NULL);
	index = 0;
	while (str[index] && str[index] != '-'
		   && (!ft_isdigit(str[index])
			   || (str[index] == '0' && str[index + 1])))
		index++;
	return ((char *)str + index);
}

t_bigint		*bigint_alloc(size_t ten_power, bool has_sign)
{
	t_bigint *big;

	big = NULL;
	UNLESS_RET(big = ALLOC(t_bigint *, 1, sizeof(t_bigint)), NULL);
	big->ten_exp = ten_power;
	big->sign = has_sign;
	if (!(big->couple_digits = ALLOC(t_uint8 *, BINT_COUPLE_SIZE(big),
									 sizeof(t_uint8))))
	{
		bigint_free(&big);
		return (NULL);
	}
	return (big);
}

t_bigint        *bigint_new(const char *big_number)
{
    t_bigint        *big;
	char			*biggy;
    t_uint32        index;
	bool			flag;

    UNLESS_RET(biggy = escape_unwanted(big_number), NULL);
	flag = false;
	if (*biggy && *biggy == '-')
		flag = (*biggy++ == '-');
    UNLESS_RET(big = bigint_alloc(ft_strlen(biggy), flag), NULL);
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

	temp[1] = BINT_COUPLE_SIZE(big);
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

t_bigint		*bigint_cmp(t_bigint *b1, t_bigint *b2, bool get_max)
{
	UNLESS_RET(b1 && b2, NULL);
	ASSERT_RET((!b1->sign && b2->sign), b1);
	ASSERT_RET((!b2->sign && b1->sign), b2);
	ASSERT_RET(b1->ten_exp > b2->ten_exp, b1->sign ? b2 : b1);
	ASSERT_RET(b2->ten_exp > b1->ten_exp, b1->sign ? b1 : b2);
	return (get_max ? bigint_maxof(b1, b2) : bigint_minof(b1, b2));
}

t_bigint		*bigint_maxof(t_bigint *b1, t_bigint *b2)
{
	t_uint32		ci;
	bool			flag;
	t_int8			diff;
	t_int8			sign;
	
	UNLESS_RET(b1 && b2, NULL);
	ci = 0;
	flag = false;
	sign = (b1->sign && b2->sign ? -1 : 1);
	while (ci < BINT_COUPLE_SIZE(b1))
	{
		/* TODO: check this */
		diff = (!flag ? BINT_SUB_LD(b1, b2, ci) : BINT_SUB_RD(b1, b2, ci));
		if (diff && (flag ^= true))
			return (sign * diff < 0 ? b2 : b1);
		if (diff && BINT_IS_RD(b1, ci) && BINT_IS_RD(b2, ci))
			return (sign * diff < 0 ? b2 : b1);
		ASSERT_RET(BINT_IS_RD(b1, ci) && !BINT_IS_RD(b2, ci), b1);
		ASSERT_RET(BINT_IS_RD(b2, ci) && !BINT_IS_RD(b1, ci), b2);
		ci++;
	}
	
	return (b1);
}

t_bigint		*bigint_minof(t_bigint *b1, t_bigint *b2)
{
	UNLESS_RET(b1 && b2, NULL);
	return (bigint_maxof(b2, b1) == b1 ? b2 : b1);
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
