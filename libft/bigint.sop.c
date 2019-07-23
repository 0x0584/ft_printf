/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.sop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 08:23:48 by archid-           #+#    #+#             */
/*   Updated: 2019/07/23 08:24:21 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

char		*mul_as_str(const char *s1, const char *s2)
{
	size_t		sizes[2];
	size_t		indexes[3];
	char		*buff;
	t_int32		result, carry = 0;

	UNLESS_RET(s1 && s2, NULL);
	sizes[0] = ft_strlen(s1);
	sizes[1] = ft_strlen(s2);
	UNLESS_RET(buff = malloc(sizes[0] + sizes[1] + 1), NULL);
	ft_memset(buff, '0', sizes[0] + sizes[1]);
	buff[sizes[0] + sizes[1]] = '\0';
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

char		*sub_as_str(const char *s1, const char *s2)
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

char		*sum_as_str(const char *s1, const char *s2)
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
