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

char		*get_double_below_zero(t_float64 dbl, t_bigint *sum)
{
	char *buff;
	
	ft_putstr(" sum: ");ft_putbigint(sum);
	
	t_bigint *five = bigint_pow(5, ABS(dbl.ieee.e - F64BIT_BAIS));
	ft_putstr("\n five: ");ft_putbigint(five);
	
	t_bigint *sumed = bigint_bigmul(five, sum);
	 ft_putstr("\n sumed: "); ft_putbigint(sumed);
	 
	t_bigint *ten = bigint_pow(10, sum->ten_exp);
	 ft_putstr("\n ten: "); ft_putbigint(ten);
	 
	t_bigint *one_mul_five = bigint_bigmul(five, ten);
	 ft_putstr("\n one_mul_five: ");ft_putbigint(one_mul_five);
	 
	t_bigint *final_result = bigint_bigadd(one_mul_five, sumed);
	ft_putstr("\n final_result: ");	ft_putbigint(final_result);
	
	char *final_as_str = bigint_tostr(final_result);
	ft_putstr("\n");
	
	buff = ft_strnew(ft_strlen(final_as_str) + 2 + dbl.ieee.s);
	if (dbl.ieee.s)
		*buff = '-';
	ft_strncpy(buff + dbl.ieee.s, "0.", 2);
	ft_strncpy(buff + 2 + dbl.ieee.s, final_as_str, ft_strlen(final_as_str));
	bigint_free(&five);
	bigint_free(&sumed);
	bigint_free(&ten);
	bigint_free(&one_mul_five);
	bigint_free(&final_result);
	ft_strdel(&final_as_str);
	
	return (buff);
}

char		*get_double_above_zero(t_float64 dbl, t_bigint *sum)
{
	char *buff;
	t_bigint *two_exp = bigint_pow(2, ABS(dbl.ieee.e - F64BIT_BAIS));
	t_bigint *result = bigint_bigmul(sum, two_exp);
	char * s = bigint_tostr(result);
	char *toadd = ft_strsub(s, 0, result->ten_exp - sum->ten_exp - 1);

	t_bigint *toadd_big = bigint_new(toadd);
	t_bigint *left_of_point = bigint_bigadd(toadd_big, two_exp);
	char *left = bigint_tostr(left_of_point);
		
	buff = ft_strnew(ft_strlen(left) +
					 ft_strlen(s + result->ten_exp - sum->ten_exp) 
					 + dbl.ieee.s);
	if (dbl.ieee.s)
		*buff = '-';
	ft_strncpy(buff + dbl.ieee.s, left, ft_strlen(left));
	ft_strncpy(buff + ft_strlen(left) + dbl.ieee.s, ".", 1);
	ft_strcpy(buff + ft_strlen(left) + dbl.ieee.s + 1, 
			  s + result->ten_exp - sum->ten_exp - 1);

	bigint_free(&toadd_big);
	bigint_free(&left_of_point);
	ft_strdel(&s);
	ft_strdel(&toadd);
	ft_strdel(&left);
	bigint_free(&two_exp);
	bigint_free(&result);
	return buff;
}

/*
** Indexes in tmp array
** 
** 0 - five power
** 1 - ten power
** 2 - prod of ten x five
** 3 - temp
*/

t_bigint	*get_mantissa(t_float64 dbl, t_uint64 mansize)
{
	t_uint32 i;
	t_bigint *tmp[4];
	t_bigint *sum;
	
	sum = bigint_init(0);
	while (i < mansize)
	{
		if ((dbl.ieee.m >> i++) & 1)
		{
			tmp[0] = bigint_pow(5, mansize - i + 1);
			tmp[1] = bigint_pow(10, i - 1);
			tmp[2] = bigint_bigmul(tmp[0], tmp[1]);
			tmp[3] = sum;
			sum = bigint_bigadd(sum, tmp[2]);
			ft_memdel_all(bigint_refdel, &tmp[0], &tmp[1], 
							&tmp[2], &tmp[3], NULL);
		}
	}
	return (sum);
}

char		*ft_dtoa(double d, t_uint16 precision)
{
	char *buff;
	t_float64 dbl;
	t_bigint *sum;

	dbl.d = d;
	(void)	precision;
	ASSERT_RET(!dbl.ieee.s && !dbl.ieee.m && !dbl.ieee.e, ft_strdup("0.0"));
	ASSERT_RET(dbl.ieee.e == 0x7FF, dbl.ieee.m ? ft_strdup("nan") :
									ft_strdup(dbl.ieee.s ? "-inf" : "inf"));
	sum = get_mantissa(dbl, F64BIT_MAN_SIZE);
	
	ft_putstr(" >> "); ft_putbigint(sum); ft_putendl("\n");

	t_int32 exp = dbl.ieee.e - 1023;

	ft_putstr(" exp >> "); ft_putnumber(exp); ft_putendl("\n");

	buff = NULL;
	
	/* IDEA: when exp iss negative it's like compiutinh fives power */
	if (exp < 0)
		buff = get_double_below_zero(dbl, sum);
	else
		buff = get_double_above_zero(dbl, sum);
	return (buff);
}
