/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 23:07:37 by archid-           #+#    #+#             */
/*   Updated: 2019/07/20 12:17:49 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*sum_as_str(const char *s1, const char *s2)
{
	size_t sizes[2];
	t_int8 carry;
	t_uint16 sum;
	char *buff, *result;
	int index = 0;

	carry = 0;
	sizes[0] = ft_strlen(s1);
	sizes[1] = ft_strlen(s2);
	buff = ft_strnew(MAX(sizes[0], sizes[1]) + 1);
	while (sizes[0])
	{
		sum = (s1[--sizes[0]] - '0') + (s2[--sizes[1]] - '0') + carry;
		buff[index++] = (sum % 10) + '0';
		carry = sum / 10;
	}
	while (sizes[1])
	{
		sum = (s1[--sizes[1]] - '0') + carry;
		buff[index++] = (sum % 10) + '0';
		carry = sum / 10;
	}
	buff[index] = carry ? carry + '0' : '\0';
	result = ft_strrev(buff);
	ft_strdel(&buff);
	return result;
}

/* add bigint_add() here */

int main(int argc, char *argv[])
{
	char *str = sum_str("000001400", "000000200");

	ft_putendl(str);
	ft_strdel(&str);
    return 0;
}
