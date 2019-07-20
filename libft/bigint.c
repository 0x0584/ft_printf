/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 01:01:43 by archid-           #+#    #+#             */
/*   Updated: 2019/07/19 22:48:21 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

t_bigint        *bigint_new(char *big_number)
{
    t_bigint        *big;
    t_uint32        index;
	bool			flag;

    UNLESS_RET(big_number, NULL);
    UNLESS_RET(big = ALLOC(t_bigint *, 1, sizeof(t_bigint)), NULL);
	if (*big_number && *big_number == '-')
		big->sign = *big_number++ == '-' ? true : false;
    big->ten_exp = ft_strlen(big_number);
    if (!(big->couple_digits = ALLOC(t_uint8 *, BIGINT_COUPLE_SIZE(big),
									 sizeof(t_uint8))))
    {
        bigint_free(&big);
        return (NULL);
    }
    index = 0;
    flag = false;
    while (*big_number && ft_isdigit(*big_number))
		if (flag ^= true)
			big->couple_digits[index] = ((*big_number++ - '0') << 4) | 0x0f;
		else
			big->couple_digits[index++] &= (*big_number++ - '0') | 0xf0;

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

	/* ft_putendl("------- .>>> "); */
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
	if (big2 || 1)
		return big1;
}

t_bigint		*bigint_minof(t_bigint *big1, t_bigint *big2)
{
	if (big2 || 1)
		return big1;
}

/* FIXEME: finish bigint_init(t_int128 number) */
t_bigint		*bigint_init(t_int128 number)
{
    t_bigint        *big;
    t_uint32        size;
	bool			flag;

    UNLESS_RET(big = ALLOC(t_bigint *, 1, sizeof(t_bigint)), NULL);
	size = BIGINT_COUPLE_SIZE(big);
    big->sign = number < 0;
    big->ten_exp = ft_digitcount_128bit(number);
    if (!(big->couple_digits = ALLOC(t_uint8 *, size, sizeof(t_uint8))))
    {
        bigint_free(&big);
        return (NULL);
    }
	while (size--)
	{

	}
	return big;
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
