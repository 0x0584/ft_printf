/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 19:48:43 by archid-           #+#    #+#             */
/*   Updated: 2019/07/26 20:50:24 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "bigint.h"
#include "float.h"

char	*ft_dtoa(double d, t_uint16 precision)
{
	char *buff;
	t_float64 f;
	t_uint32 i;

	t_bigint *five_pow;
	t_bigint *ten_pow;
	t_bigint *prod;
	t_bigint *sum = bigint_init(0);
	t_bigint *tmp;

	f.d = d;
	/* printf("---------- dtoa(%lf, %u) ----------\n", d, precision); */
	/* printf("%lf = m:%lu e:%u s:%u\n", d, f.ieee.m, f.ieee.e, f.ieee.s); */

	/* IDEA: I HAVE FOUND IT! IT WAS FUCKING SIMPLE! */

	i = 0;
	while (i < F64BIT_MAN_SIZE)
	{
		if ((f.ieee.m >> i++) & 1)
		{
			five_pow = bigint_pow(5, F64BIT_MAN_SIZE - i + 1);
			ten_pow = bigint_pow(10, i - 1);
			prod = bigint_bigmul(five_pow, ten_pow);
			tmp = sum;
			sum = bigint_bigadd(sum, prod);
			bigint_free(&five_pow);
			bigint_free(&ten_pow);
			bigint_free(&prod);
			bigint_free(&tmp);
		}
	}

	t_int32 exp = f.ieee.e - 1023;
	t_bigint *two_exp = bigint_pow(2, exp);
	t_bigint *result = bigint_bigmul(sum, two_exp);

	buff = NULL;
	if (result->ten_exp - sum->ten_exp != 0)
	{
		char * s = bigint_tostr(result);
		char *toadd = ft_strsub(s, 0, result->ten_exp - sum->ten_exp);
		t_bigint *toadd_big = bigint_new(toadd);
		t_bigint *left_of_point = bigint_bigadd(toadd_big, two_exp);

		ft_putbigint(left_of_point); ft_putstr(".");
		ft_putstr(s + result->ten_exp - sum->ten_exp);

		buff = ft_strnew(ft_strlen(toadd) +
						 ft_strlen(s + result->ten_exp - sum->ten_exp) + 1);
		ft_strcpy(buff, toadd);
		ft_strcpy(buff, ".");
		ft_strcpy(buff, s + result->ten_exp - sum->ten_exp);
		bigint_free(&toadd_big);
		bigint_free(&left_of_point);
		ft_strdel(&s);
		ft_strdel(&toadd);
	}

	bigint_free(&two_exp);
	bigint_free(&result);
	bigint_free(&sum);
	return (buff);
}
