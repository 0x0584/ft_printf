/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_dtoa.c											:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <archid-@student.1337.ma>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/07/25 19:48:43 by archid-		   #+#	  #+#			  */
/*	 Updated: 2019/07/26 21:51:20 by archid-		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"
#include "bigint.h"
#include "float.h"

/*
 * getting a double below zero is done with mulipliying with 2^(exp)
 * but if exp < 0, we can do this trick
 *
 *		2^(exp) x 5^(exp) x 5^(-exp) = 10^(exp) x 5^(-exp)
 *
 * so we can just computer 5^(-exp) then later know when to place the period
 * using the exp.
 */

/*
**
** big[4] indexes:
**
** 0 - five power
** 1 - ten power
** 2 - five power times the man sum
** 3 - five power times ten power
** 4 - final result
*/
char		*get_double_below_zero(t_float64 dbl, t_bigint *msum)
{
	char *buff;
	t_bigint *big[4];
	t_bigint *result;

	big[0] = bigint_pow(5, ABS(dbl.ieee.e - F64BIT_BAIS));
	big[1] = bigint_pow(10, msum->ten_exp);
	big[2] = bigint_bigmul(big[0], msum);
	big[3] = bigint_bigmul(big[0], big[1]);
	result = bigint_bigadd(big[2], big[3]);
	buff = ft_strnew(result->ten_exp + 2 + dbl.ieee.s);
	if (dbl.ieee.s)
		*buff = '-';
	ft_strncpy(buff + dbl.ieee.s, "0.", 2);
	ft_strncpy(buff + 2 + dbl.ieee.s, result->base, result->ten_exp);
	ft_memdel_all(bigint_refdel, &big[0], &big[1], &big[2],
					&big[3], &result, NULL);
	return (buff);
}

/*
** big array indexes
**
** 0 - two_exp
** 1 - two_exp times msum
** 2 - int_part of msum
** 3 - int_part of double
*/

char		*get_double_above_zero(t_float64 dbl, t_bigint *msum)
{
	char *buff;
	char *int_part;
	t_bigint *big[4];

	big[0] = bigint_pow(2, ABS(dbl.ieee.e - F64BIT_BAIS));
	big[1] = bigint_bigmul(msum, big[0]);
	int_part = ft_strsub(big[1]->base, 0, EXP_DIFF(big[1], msum));
	big[2] = bigint_new(int_part);
	big[3] = bigint_bigadd(big[2], big[0]);
	buff = ft_strnew(ft_strlen(big[1]->base + EXP_DIFF(big[1], msum))
						+ big[3]->ten_exp + dbl.ieee.s + 1);
	if (dbl.ieee.s) 
		*buff = '-';
	ft_strncpy(buff + dbl.ieee.s, big[3]->base, big[3]->ten_exp);
	buff[big[3]->ten_exp + dbl.ieee.s] = '.';
	ft_strcpy(buff + big[3]->ten_exp + dbl.ieee.s + 1,
				big[1]->base + EXP_DIFF(big[1], msum));
	ft_memdel_all(bigint_refdel, &big[0], &big[1], &big[2], &big[3], NULL);
	ft_strdel(&int_part);
	return (buff);
}

/*
** Indexes in tmp array
**
** 0 - five power
** 1 - ten power
** 2 - prod of ten x five
** 3 - temp
*/

t_bigint	*get_mantissa_sum(t_float64 dbl, t_uint64 mansize)
{
	t_uint32 i;
	t_bigint *big[4];
	t_bigint *msum;

	msum = bigint_init(0);
	while (i < mansize)
	{
		if ((dbl.ieee.m >> i++) & 1)
		{
			big[0] = bigint_pow(5, mansize - i + 1);
			big[1] = bigint_pow(10, i - 1);
			big[2] = bigint_bigmul(big[0], big[1]);
			big[3] = msum;
			msum = bigint_bigadd(msum, big[2]);
			ft_memdel_all(bigint_refdel, &big[0], &big[1],
							&big[2], &big[3], NULL);
		}
	}
	return (msum);
}

char		*ft_dtoa(double d)
{
	t_float64	dbl;
	t_bigint	*msum;
	char		*buff;

	dbl.d = d;
	ASSERT_RET(!dbl.ieee.s && !dbl.ieee.m && !dbl.ieee.e, ft_strdup("0.0"));
	ASSERT_RET(dbl.ieee.e == 0x7FF, dbl.ieee.m ? ft_strdup("nan") :
									ft_strdup(dbl.ieee.s ? "-inf" : "inf"));
	msum = get_mantissa_sum(dbl, F64BIT_MAN_SIZE);
	if ((dbl.ieee.e - 1023) < 0)
		buff = get_double_below_zero(dbl, msum);
	else
		buff = get_double_above_zero(dbl, msum);
	return (buff);
}
