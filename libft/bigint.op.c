/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 22:47:50 by archid-           #+#    #+#             */
/*   Updated: 2019/07/21 23:52:19 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

char	*sub_as_str(const char *s1, const char *s2)
{
	size_t	sizes[2];
	size_t index = 0;
	t_int8	sub, carry = 0;
	char	*buff, *result;

	sizes[0] = ft_strlen(s1);
	sizes[1] = ft_strlen(s2);
	UNLESS_RET(buff = ft_strnew(MAX(sizes[0], sizes[1]) + 1), NULL);
	while (sizes[0] && sizes[1])
	{
		sub = GET_DIGI(s1[--sizes[0]]) - GET_DIGI(s2[--sizes[1]]) - carry;
		if ((carry = sub < 0))
			sub += 10;
		buff[index++] = TO_DIGI(sub);
	}
	while (sizes[0])
	{
		sub = GET_DIGI(s1[--sizes[0]]) - carry;
		if ((carry = sub < 0))
			sub += 10;
		buff[index++] = TO_DIGI(sub);
	}
	result = ft_strrev(buff);
	ft_strdel(&buff);
	return (result);
}

char		*sum_as_str(const char *s1, const char *s2)
{
	size_t		sizes[2];
	t_int8		carry;
	t_int8		sum;
	char		*buff, *result;
	int			index = 0;

	carry = 0;
	sizes[0] = ft_strlen(s1);
	sizes[1] = ft_strlen(s2);
	buff = ft_strnew(MAX(sizes[0], sizes[1]) + 1);
	while (sizes[0] && sizes[1])
	{
		sum = (s1[--sizes[0]] - '0') + (s2[--sizes[1]] - '0') + carry;
		buff[index++] = (sum % 10) + '0';
		carry = sum / 10;
	}
	while (sizes[0])
	{
		sum = (s1[--sizes[0]] - '0') + carry;
		buff[index++] = (sum % 10) + '0';
		carry = sum / 10;
	}
	buff[index] = carry ? carry + '0' : '\0';
	result = ft_strrev(buff);
	ft_strdel(&buff);
	return (result);
}

t_bigint	*bigint_sub(t_bigint *big1, t_bigint *big2)
{
	t_bigint	*bigint;
	char		*bigint_str[2];
	char		*tmp;
	bool		sign;

	/* fix this shit! */

	/*

	   if both positive, [0] = bigger, [1] = smaller

	 */
	bigint = bigint_maxof(big1, big2);
	bigint_str[0] = bigint_tostr(bigint);
	bigint_str[1] = bigint_tostr(bigint == big1 ? big2 : big1);

	sign = bigint != big1;

	ft_putstr("\n  .>> "); ft_putendl(bigint_str[0]);
	ft_putstr("  .>> "); ft_putendl(bigint_str[1]);

	tmp = sub_as_str(bigint_str[0], bigint_str[1]);
	bigint = bigint_new(tmp);
	bigint->sign = sign;

	ft_strdel(&tmp);
	ft_strdel(&bigint_str[0]);
	ft_strdel(&bigint_str[1]);
	return (bigint);
}

/* FIXME: how to implement bigint_add() using bitwise!? */
t_bigint		*bigint_add(t_bigint *big1, t_bigint *big2)
{
	t_bigint	*bigint;
	char		*bigint_str[2];
	char		*tmp;

	bigint = bigint_maxof(big1, big2);
	bigint_str[0] = bigint_tostr(bigint);
	bigint_str[1] = bigint_tostr(bigint == big1 ? big2 : big1);
	ft_putstr("\n  .>> "); ft_putendl(bigint_str[0]);
	ft_putstr("  .>> "); ft_putendl(bigint_str[1]);
	tmp = sum_as_str(bigint_str[0], bigint_str[1]);
	bigint = bigint_new(tmp);
	ft_strdel(&tmp);
	ft_strdel(&bigint_str[0]);
	ft_strdel(&bigint_str[1]);
	return (bigint);
}

t_uint8		bitwise_subtractor(t_uint8 a, t_uint8 b)
{
	if (b == 0)
		return (a);
	return bitwise_subtractor(a ^ b, (~a & b) << 1);
}

t_uint8		bitwise_adder(t_uint8 a, t_uint8 b)
{
	if (b == 0)
		return (a);
	return bitwise_adder(a ^ b, (a & b) << 1);
}

t_uint8		bitwise_multiplier(t_uint8 a, t_uint8 b)
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

t_bigint	*bigint_mul(t_bigint *big1, t_bigint *big2)
{
	/*
	   IDEA:

	   when calling bitwise_multiplier(), check if result >= 10.
	   if so, add result % 10 to "wa7adat" and result  / 10 to "3acharat"
	   this might result some sequence of changes, which better be done
	   using recursive bitwise
	*/
}

t_bigint	*bigint_pow(t_bigint *big1, t_uint32 power)
{

}

/* t_bigint		*bigint_add(t_bigint *big1, t_bigint *big2) */
/* { */
/* 	t_bigint		*result; */
/* 	t_bigint		*ordered[2]; */
/* 	t_uint32		sizes[2]; */
/* 	t_int8			cmp; */
/* 	bool			toadd; */
/* 	bool			sign; */

/* 	UNLESS_RET(big1 && big2, NULL); */
/* 	/\* handle sign *\/ */
/* 	if ((toadd = !(big1->sign ^ big2->sign))) */
/* 	{ */
/* 		/\* */
/* 		  they have the same sign */
/* 		  perform addition and then the sign is the same sign */
/* 		 *\/ */
/* 		sign = big1->sign; */
/* 		ordered[0] = bigint_minof(big1, big2); */
/* 		ordered[1] = bigint_maxof(big1, big2); */
/* 	} */
/* 	else if ((cmp = bigint_ucmp(big1, big2))) */
/* 	{ */
/* 		/\* */
/* 		   they have different sign, determine the bigger */
/* 		   and the it must has it's sign */

/* 		   IDEA: */

/* 		   compare them as unsigned, teh sign of the result if */
/* 		   the sign of the bigger */
/* 		*\/ */
/* 		sign = cmp > 0 ? big1->sign : big2->sign; */
/* 		ordered[0] = cmp > 0 ? big2 : big1; */
/* 		ordered[1] = cmp > 0 ? big1 : big2; */
/* 	} */
/* 	else */
/* 		return bigint_new("0"); */

/* 	sizes[0] = BIGINT_COUPLE_SIZE(big1); */
/* 	sizes[1] = BIGINT_COUPLE_SIZE(big2); */
/* 	UNLESS_RET(result = ALLOC(t_bigint *, 1, sizeof(t_bigint)), NULL); */
/*     if (!(result->couple_digits = ALLOC(t_uint8 *, MAX(sizes[0], sizes[1]) + 1, */
/* 									 sizeof(t_uint8)))) */
/*     { */
/*         bigint_free(&result); */
/*         return (NULL); */
/*     } */

/* 	ordered[1] = NULL; */
/* 	while (sizes[0]-- && sizes[1]--) */
/* 	{ */
/* 		if (toadd) */
/* 		{ */
/* 			/\* */
/* 			   performe addition and append to result */

/* 			   call bitwise_adder() */
/* 			 *\/ */
/* 		} */
/* 		else */
/* 		{ */
/* 			/\* */
/* 			   performe subtraction and append to result */

/* 			   call bitwise_subtractor() */
/* 			*\/ */
/* 		} */

/* 		if (sizes[0] && !sizes[1]) */
/* 			ordered[1] = big1;					/\* big1 > big2 *\/ */
/* 		else if (!sizes[0] && sizes[1]) */
/* 			ordered[1] = big2;					/\* big2 > big1 *\/ */
/* 	} */


/* 	/\* FIXME: */

/* 	   result must have some memory waste example 9999 + (-999) is 9 */
/* 	   but we would have allocated memory for 5 digits! */

/* 	   so at the last, remove trailing zeros! */
/* 	 *\/ */
/* 	return (result); */
/* } */


/* try to imeplemet those based on t_bigint couple_digits array! */
