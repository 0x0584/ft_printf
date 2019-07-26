/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_ftoa.c											:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <archid-@student.1337.ma>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/06/30 02:45:42 by archid-		   #+#	  #+#			  */
/*   Updated: 2019/07/25 20:37:51 by archid-          ###   ########.fr       */
/*																			  */
/* ************************************************************************** */

#include "libft.h"
#include "bigint.h"
#include "float.h"

/*
   TODO: Finish ftoa()

   IDEA:
   ~~~~~

   1. compute $2^{exp - BAIS}$

   2. compute the fraction form the mantissa as the following:

		- mantissa is in the following form 1.mantissa_in_binary
		so each time we should $\Sigma{bit \times 1/2^{i}}$, which would
		give us a fraction.

		- the question is how to get the integer part? well,
		we multiply by $10^{i}$. Thus $\Sigma{bit \times 5^{i}}$

   3. test on the sign of $exp - BAIS$.

		- Fraction Part: if positive, skip $exp - BAIS$ digits from mantissa's
		front. otherwise if negative \textit{pad $exp - BAIS$ zero's but with
		a one first} -- since the number written as is $2^{exp - BAIS} \times
		1.mantissa$.

		- Integer Part: based on what we had done, take whatever on the left!

   4. Let $i$ be the Integer Part of a floating point number $u$, and $f$ it's
		fractional part. compute $i \times 2^{exp - BAIS}$ and $f \times
		2^{exp - BAIS}$.
*/

char	*ft_ftoa(float f, t_int8 precision)
{
	printf("--------------- ftoa(%f, %d) ------------------\n\n", f, precision);

	t_float32 foo = {.f = f};
	t_bigint *exp, *two, *man;
	t_bigint *tmp[2];

	t_bigint *man_exp;
	t_int32 exp_val = F32BIT_EXP(foo) - F32BIT_BIAS;
	bool exp_val_sign;

	if ((exp_val_sign = exp_val < 0))
		exp_val *= -1;

	two = bigint_new("2");
	ft_putstr(" here ");
	ft_putbigint(two);
	ft_putendl("\n");
	ft_putstr(" exp_val >> "); ft_putnumber(exp_val); ft_putendl("\n }}}");

	ft_putnumber(F32BIT_EXP(foo)); ft_putendl("\n");
	ft_putnumber(F32BIT_EXP(foo) - F32BIT_BIAS); ft_putendl("\n");

	exp = bigint_bigpow(two, exp_val);
    man = bigint_init(F32BIT_MAN(foo) | 0x800000);
	man_exp = bigint_bigmul(exp, man);

	/* TODO: implement a five power! */

	ft_putstr("\nas unsigned int: ");
	ft_putnumber(foo.i);
	ft_putendl("\n exp : ");
	ft_putbigint(exp);
	ft_putendl("\n man_exp :");
	ft_putbigint(man_exp);
	ft_putendl("\n---");
	ft_putnumber(precision);
	ft_putendl("\n--- man ");
	ft_putnumber(F32BIT_MAN(foo));
	ft_putendl("\n--- exp ");
	ft_putnumber(F32BIT_EXP(foo));
	ft_putendl("\n-- sign");
	ft_putnumber(F32BIT_SIGN(foo));
	ft_putendl("\n- && ---");

	bigint_free(&two);
	bigint_free(&exp);
	bigint_free(&man);
	bigint_free(&man_exp);

	return (NULL);
}
