/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 22:47:50 by archid-           #+#    #+#             */
/*   Updated: 2019/07/19 06:43:49 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

t_bigint		*bigint_add(t_bigint *big1, t_bigint *big2)
{
	t_bigint		*result;
	t_bigint		*ordered[2];
	t_uint32		sizes[2];
	t_int8			cmp;
	bool			toadd;
	bool			sign;

	UNLESS_RET(big1 && big2, NULL);
	/* handle sign */
	if ((toadd = !(big1->sign ^ big2->sign)))
	{
		/*
		  they have the same sign
		  perform addition and then the sign is the same sign
		 */
		sign = big1->sign;
		ordered[0] = bigint_minof(big1, big2);
		ordered[1] = bigint_maxof(big1, big2);
	}
	else if ((cmp = bigint_ucmp(big1, big2)))
	{
		/*
		   they have different sign, determine the bigger
		   and the it must has it's sign

		   IDEA:

		   compare them as unsigned, teh sign of the result if
		   the sign of the bigger
		*/
		sign = cmp > 0 ? big1->sign : big2->sign;
		ordered[0] = cmp > 0 ? big2 : big1;
		ordered[1] = cmp > 0 ? big1 : big2;
	}
	else
		return bigint_new("0");

	sizes[0] = BIGINT_COUPLE_SIZE(big1);
	sizes[1] = BIGINT_COUPLE_SIZE(big2);
	UNLESS_RET(result = ALLOC(t_bigint *, 1, sizeof(t_bigint)), NULL);
    if (!(result->couple_digits = ALLOC(t_uint8 *, MAX(sizes[0], sizes[1]) + 1,
									 sizeof(t_uint8))))
    {
        bigint_free(&result);
        return (NULL);
    }

	ordered[1] = NULL;
	while (sizes[0]-- && sizes[1]--)
	{
		if (toadd)
		{
			/*
			   performe addition and append to result

			   call bitwise_adder()
			 */
		}
		else
		{
			/*
			   performe subtraction and append to result

			   call bitwise_subtractor()
			*/
		}

		if (sizes[0] && !sizes[1])
			ordered[1] = big1;					/* big1 > big2 */
		else if (!sizes[0] && sizes[1])
			ordered[1] = big2;					/* big2 > big1 */
	}


	/* FIXME:

	   result must have some memory waste example 9999 + (-999) is 9
	   but we would have allocated memory for 5 digits!

	   so at the last, remove trailing zeros!
	 */
	return (result);
}

/* try to imeplemet those based on t_bigint couple_digits array! */

t_uint8			bitwise_subtractor(t_uint8 a, t_uint8 b)
{
	if (b == 0)
		return (a);
	return bitwise_subtractor(a ^ b, (~a & b) << 1);
}

t_uint8			bitwise_adder(t_uint8 a, t_uint8 b)
{
	if (b == 0)
		return (a);
	return bitwise_adder(a ^ b, (a & b) << 1);
}

t_uint8			bitwise_multiplier(t_uint8 a, t_uint8 b)
{
	t_uint8 result;

	result = 0;
	while (b)
	{
		if (b & 1)
			result = bitwise_adder(result, a);
		a <<= 1;
		b >>= 1;
	}
	return (result);
}

t_bigint		*bigint_mul(t_bigint *big1, t_bigint *big2)
{
	/*
	   IDEA:

	   when calling bitwise_multiplier(), check if result >= 10.
	   if so, add result % 10 to "wa7adat" and result  / 10 to "3acharat"
	   this might result some sequence of changes, which better be done
	   using recursive bitwise
	*/
}

t_bigint		*bigint_pow(t_bigint *big1, t_uint32 power)
{

}
