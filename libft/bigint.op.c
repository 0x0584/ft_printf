/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 22:47:50 by archid-           #+#    #+#             */
/*   Updated: 2019/07/23 08:03:53 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* FIXME: check all memory allocations and returns */

#include "bigint.h"

static char		*mul_as_str(const char *s1, const char *s2)
{
	size_t		sizes[2];
	size_t		indexes[3];
	char		*buff;
	t_int32		result, carry = 0;

	sizes[0] = ft_strlen(s1);
	sizes[1] = ft_strlen(s2);

	/* NOTE: The reason why using malloc and not ft_strnew() because we need
	 * to call memset() to initialize the string with 48 or '0; */
	UNLESS_RET(buff = malloc(sizes[0] + sizes[1] + 1), NULL);
	ft_memset(buff, '0', sizes[0] + sizes[1]);
	buff[sizes[0] + sizes[1]] = '\0'; /* BUG: missed the '\0' */
	indexes[0] = sizes[0];
	while (indexes[0]--)
	{
		indexes[1] = sizes[1];
		indexes[2] = indexes[1] + indexes[0];
		while (indexes[1]--)
		{
			result = GET_DIGI(s1[indexes[0]]) * GET_DIGI(s2[indexes[1]])
						+ GET_DIGI(buff[indexes[2]]) + carry;
			carry = result / 10;
			buff[indexes[2]--] = TO_DIGI(result % 10);
		}
		buff[indexes[2]] += carry;
	}
	return (buff);
}

static char		*sub_as_str(const char *s1, const char *s2)
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
		ASSERT_DO(carry = sub < 0, sub += 10);
		buff[index++] = TO_DIGI(sub);
	}
	while (sizes[0])
	{
		sub = GET_DIGI(s1[--sizes[0]]) - carry;
		ASSERT_DO(carry = sub < 0, sub += 10);
		buff[index++] = TO_DIGI(sub);
	}
	result = ft_strrev(buff);
	ft_strdel(&buff);
	return (result);
}

static char		*sum_as_str(const char *s1, const char *s2)
{
	size_t	sizes[2];
	t_int8	carry;
	t_int8	sum;
	char	*buff, *result;
	int		index = 0;

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

t_bigint		*bigint_sub(t_bigint *big1, t_bigint *big2)
{
	t_bigint		*bigint;
	char			*bigint_str[2];
	char			*tmp;
	bool			sign;
	bool			flag;

	if (big1->sign && !big2->sign)
	{
		/* -200 - 20 */
		big1->sign = false;
		bigint = bigint_maxof(big1, big2);
		flag = (bigint == big1);
		bigint = bigint_sub(flag ? big1 : big2, flag ? big2 : big1);
		bigint->sign = flag;
		big1->sign = true;
		return (bigint);
	}
	else if (big2->sign && !big1->sign)
	{
		/* 100 - -20 */
		big2->sign = false;
		bigint = bigint_maxof(big1, big2);
		flag = (bigint == big2);
		bigint = bigint_add(flag ? big2 : big1, flag ? big1 : big2);
		bigint->sign = flag;
		big2->sign = true;
		return (bigint);
	}
	else if (big1->sign && big2->sign)
	{
		/* -20 - -30 */
		big2->sign = false;
		bigint = bigint_add(big1, big2);
		big2->sign = true;
		return (bigint);
	}
	bigint = bigint_maxof(big1, big2);
	bigint_str[0] = bigint_tostr(bigint);
	bigint_str[1] = bigint_tostr(bigint == big1 ? big2 : big1);
	sign = (bigint != big1);
	tmp = sub_as_str(bigint_str[0] + (*bigint_str[0] == '-'),
					 bigint_str[1] + (*bigint_str[1] == '-'));
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
	t_bigint		*bigint;
	char			*bigint_str[2];
	char			*tmp;
	bool			flag;

	/*
	  if both are negative just do addition and apply sign
	  if one is negative, surpass the sign
	*/

	if (big1->sign && !big2->sign)
	{
		big1->sign = false;
		bigint = bigint_maxof(big1, big2);
		flag = (bigint == big1);
		bigint = bigint_sub(flag ? big1 : big2, flag ? big2 : big1);
		bigint->sign = flag;
		big1->sign = true;
		return (bigint);
	}
	else if (big2->sign && !big1->sign)
	{
		big2->sign = false;
		bigint = bigint_maxof(big1, big2);
		flag = (bigint == big2);
		bigint = bigint_sub(flag ? big2 : big1, flag ? big1 : big2);
		bigint->sign = flag;
		big2->sign = true;
		return (bigint);
	}
	else if (big1->sign && big2->sign)
	{
		big1->sign = false;
		big2->sign = false;
		bigint = bigint_add(big1, big2);
		bigint->sign = true;
		big1->sign = true;
		big2->sign = true;
		return (bigint);
	}
	bigint = bigint_maxof(big1, big2);
	bigint_str[0] = bigint_tostr(bigint);
	bigint_str[1] = bigint_tostr(bigint == big1 ? big2 : big1);
	tmp = sum_as_str(bigint_str[0] + (*bigint_str[0] == '-'),
						 bigint_str[1] + (*bigint_str[1] == '-'));
	bigint = bigint_new(tmp);
	ft_strdel(&tmp);
	ft_strdel(&bigint_str[0]);
	ft_strdel(&bigint_str[1]);
	return (bigint);
}

t_bigint		*bigint_mul(t_bigint *big1, t_bigint *big2)
{
	t_bigint		*bigint;
	char			*bigint_str[2];
	bool			sign;

	bigint_str[0] = bigint_tostr(big1);
	bigint_str[1] = bigint_tostr(big2);
	sign = false;
	if (!ft_strcmp(bigint_str[0], "0") || !ft_strcmp(bigint_str[1], "0"))
		bigint = bigint_new("0");
	else
	{
		char *buff = mul_as_str(bigint_str[0] + big1->sign,
								bigint_str[1] + big2->sign);
		bigint = bigint_new(buff);
		bigint->sign = (big1->sign ^ big2->sign);
		ft_strdel(&buff);
	}
	ft_strdel(&bigint_str[0]);
	ft_strdel(&bigint_str[1]);
	return (bigint);
}

t_bigint		*bigint_pow(t_bigint *big1, t_uint32 power)
{
	t_bigint *big;
	t_bigint *tmp;

	big = bigint_init(1);
	if (power <= 0)				/* FIXME: handle negative power!  */
		return (big);
	else if (power == 1)
		return (big1);			/* FIXME: reallocate this! */
	while (power--)
	{
		tmp = bigint_mul(big1, big);
		bigint_free(&big);
		big = tmp;
	}
	return (big);
}
