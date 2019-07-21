/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 01:01:43 by archid-           #+#    #+#             */
/*   Updated: 2019/07/21 09:36:43 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

t_bigint        *bigint_new(char *big_number)
{
    t_bigint        *big;
    t_uint32        index;
	bool			flag;

	char *foo = big_number;

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
	(void)printf("bigint(%s) & sign: %s\n", foo,
						big->sign ? "signed" : "unsigned");
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

	ft_putendl("here");
	is_nega = big1->sign && big2->sign ? -1 : 1;
	ft_putstr("is_nega: "); ft_putnumber(is_nega); ft_putstr(" diff: \n");
	/* (void)printf(" }}} %d %d %d\n", is_nega, big1->sign, big2->sign); */
	flag = false;
	temp[0] = 0;
	temp[1] = BIGINT_COUPLE_SIZE(big1);
	while (temp[0] < temp[1])
	{
		diff = is_nega * (!flag ?
			BIGINT_LD(big1, temp[0]) - BIGINT_LD(big2, temp[0]) :
			BIGINT_RD(big1, temp[0]) - BIGINT_RD(big2, temp[0]));
		ft_putnumber(diff); ft_putstr(" ");
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
	ft_putendl("end diff");
	return (big1);
}

t_bigint		*bigint_minof(t_bigint *big1, t_bigint *big2)
{
	return (bigint_maxof(big2, big1) == big1 ? big2 : big1);
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
