/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_dtoa.c											:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <archid-@student.1337.ma>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/07/25 19:48:43 by archid-		   #+#	  #+#			  */
/*   Updated: 2019/08/06 14:42:47 by archid-          ###   ########.fr       */
/*																			  */
/* ************************************************************************** */

#include "libft.h"
#include "bigint.h"
#include "float.h"

char	*ft_dtoa(double d, t_uint16 precision, bool round)
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
	i = 0;
	if (f.ieee.s == 0 && f.ieee.m == 0 && f.ieee.e == 0)
		return (ft_strdup("0.0"));
	else if (f.ieee.e == 0x7FF)
		return f.ieee.m ? ft_strdup("nan") :
				ft_strdup(f.ieee.s ? "-inf" : "inf");
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

	ft_putstr(" >> "); ft_putbigint(sum); ft_putendl("\n");

	t_int32 exp = f.ieee.e - 1023;
	bool sign;

	ft_putstr(" exp >> "); ft_putnumber(exp); ft_putendl("\n");

	if ((sign = exp < 0))
	{
		exp *= -1;
		char *big_as_str = bigint_tostr(sum);
		t_bigint *n = bigint_pow(5, exp);
		t_bigint *sumed	 = bigint_bigmul(n, sum);
		t_bigint *ten_pow = bigint_pow(10, sum->ten_exp);
		t_bigint *one_mul_five = bigint_bigmul(n, ten_pow);
		t_bigint *final_result = bigint_bigadd(one_mul_five, sumed);
		char *final_as_str = bigint_tostr(final_result);

		buff = ft_strnew(ft_strlen(big_as_str) + 1);
		if (f.ieee.s)
			*buff = '-';
		ft_strcpy(buff + f.ieee.s, "0.");
		ft_strcpy(buff + 2 + f.ieee.s, final_as_str);
		bigint_free(&n);
		bigint_free(&sumed);
		bigint_free(&ten_pow);
		bigint_free(&one_mul_five);
		bigint_free(&final_result);
		ft_strdel(&final_as_str);
		ft_strdel(&big_as_str);
	} else {

		t_bigint *two_exp = bigint_pow(2, exp);
		t_bigint *result = bigint_bigmul(sum, two_exp);
		char * s = bigint_tostr(result);
		char *toadd = ft_strsub(s, 0, result->ten_exp - sum->ten_exp - 1);

		t_bigint *toadd_big = bigint_new(toadd);
		t_bigint *left_of_point = bigint_bigadd(toadd_big, two_exp);
		char *left = bigint_tostr(left_of_point);
		buff = ft_strnew(ft_strlen(toadd) +
						 ft_strlen(s + result->ten_exp - sum->ten_exp) + 1);
		if (f.ieee.s)
			*buff = '-';
		ft_strcpy(buff + f.ieee.s, left);
		ft_strcpy(buff + ft_strlen(left) + f.ieee.s, ".");
		ft_strcpy(buff + ft_strlen(left) + f.ieee.s + 1, s + result->ten_exp - sum->ten_exp - 1);

		bigint_free(&toadd_big);
		bigint_free(&left_of_point);
		ft_strdel(&s);
		ft_strdel(&toadd);
		bigint_free(&two_exp);
		bigint_free(&result);
		bigint_free(&sum);
	}
	return (buff);
}
