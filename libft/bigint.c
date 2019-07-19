/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 01:01:43 by archid-           #+#    #+#             */
/*   Updated: 2019/07/19 03:10:55 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

/* IDEA: this might have to be done using an array of ints! */

/*
t_bigint		*bigint_new(char *big_number)
{
	t_bigint		*big;
	t_uint32		index;

	UNLESS_RET(big_number, NULL);
	UNLESS_RET(big = ALLOC(t_bigint *, 1, sizeof(t_bigint)), NULL);

	big->sign = *big_number == '-';
	big->ten_exp = ft_strlen(big_number) - big->sign;
	if (!(big->couple_digits = ALLOC(t_uint8 *, big->ten_exp / 2,
			sizeof(t_uint8))))
	{
		bigint_free(&big);
		return (NULL);
	}

	index = 0;
	while (ft_isdigit(*big_number))
	{
		big->couple_digits[index] = *big_number++ - '0';
		big->couple_digits[index] <<= 4;
		big->couple_digits[index++] |= *big_number++;
	}

	return (big);
}
*/
t_bigint        *bigint_new(char *big_number)
{
    t_bigint        *big;
    t_uint32        index;
	bool			flag;

    UNLESS_RET(big_number, NULL);
    UNLESS_RET(big = ALLOC(t_bigint *, 1, sizeof(t_bigint)), NULL);
    big->sign = *big_number == '-';
    big->ten_exp = ft_strlen(big_number) - big->sign;
    if (!(big->couple_digits = ALLOC(t_uint8 *, big->ten_exp / 2,
            sizeof(t_uint8))))
    {
        bigint_free(&big);
        return (NULL);
    }
    index = 0;
    flag = false;
    while (*big_number && ft_isdigit(*big_number))
      if (flag ^= true)
		  big->couple_digits[index] = (*big_number++ - '0') << 4;
      else
		  big->couple_digits[index++] |= *big_number++ - '0';

    return (big);
}

t_bigint		*bigint_init(t_int128 number);
void			bigint_free(t_bigint **big_number);
