/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_ftoa.c											:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <archid-@student.1337.ma>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/06/30 02:45:42 by archid-		   #+#	  #+#			  */
/*   Updated: 2019/07/23 13:56:57 by archid-          ###   ########.fr       */
/*																			  */
/* ************************************************************************** */

#include "libft.h"
#include "bigint.h"
#include "float.h"

/* IDEA:

   you need a new data structure, which is BigInt, that can hold to the
   whole set!
 */

/* IDEA:

   implement the following:

   void compute_two_power(char **base, t_int8 exponent)
   void compute_mantessa_exponent(char **base, t_uint8 exponent, t_uint32 mantessa)

 */

/*
void	str_add_number(char **base, t_uint64 number)
{
	char *result;


}

void compute_two_power(char **base, t_int8 exponent, t_uint8 offset)
{
	t_int16 diff;

	diff = exponent - offset;
	if (diff < 0)
	{
		// here you have to keep track of how many you have to add

	}
	else
	{
		// it's positive
	}
}
*/

/*
void compute_mantessa_exponent(char **base, t_uint8 exp, t_uint32 man)
{

	compute_two_power(&pow_two, exp, FLOAT_OFFSET);

	multiplay_two_bignumbers(&pow_two, );

}
*/

char	*ft_ftoa(float f, t_int8 precision)
{
	ft_putendl("--------------- ftoa ------------------");

	t_float32 foo = {.f = f};
	t_bigint *exp, *two, *man;
	t_bigint *man_exp;
	t_int16 exp_val = F32BIT_EXP(foo) - F32BIT_BIAS;
	bool exp_val_sign;

	if ((exp_val_sign = exp_val < 0))
		exp_val *= -1;

	/* XXX: work on BIG INTS to IMPLEMENT THE FLOAT! */

	two = bigint_init(2);
	ft_putstr(" exp >> "); ft_putnumber(exp_val); ft_putendl("\n");
	ft_putnumber(F32BIT_EXP(foo)); ft_putendl("\n");

	exp = bigint_pow(two, exp_val);
	man = bigint_init(F32BIT_MAN(foo));
	man_exp = bigint_mul(exp, man);

	ft_putstr("\nas unsigned int: ");
	ft_putnumber(foo.i);
	ft_putendl("\n");
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
