/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 23:07:37 by archid-           #+#    #+#             */
/*   Updated: 2019/07/20 04:17:04 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *escape_unwanted(const char *s)
{
	char *foo = (char *)s;
	while (!ft_isdigit(*foo) || *foo == '0')
		foo++;
	return (foo);
}

char *sum_str(const char *s1, const char *s2)
{
	char *ordered[2];
	size_t sizes[2];
	t_int8 carry;
	t_uint16 sum;
	char *buff, *result;
	int index = 0;


	if (ft_strlen(escape_unwanted(s2)) < ft_strlen(escape_unwanted(s1))) {
		ordered[0] = escape_unwanted(s2);
		ordered[1] = escape_unwanted(s1);
	} else {
		ordered[1] = escape_unwanted(s2);
		ordered[0] = escape_unwanted(s1);
	}

	ft_putendl(s1);
	ft_putendl(ordered[0]);
	ft_putendl(s2);
	ft_putendl(ordered[1]);
	sizes[0] = ft_strlen(ordered[0]);
	sizes[1] = ft_strlen(ordered[1]);
	buff = ft_strnew(MAX(sizes[0], sizes[1]) + 1);

	carry = 0;
	while (sizes[0])
	{
		sum = (ordered[0][--sizes[0]] - '0') + (ordered[1][--sizes[1]] - '0');
		sum += carry;
		ft_putendl("---------------");
		buff[index++] = (sum % 10) + '0';
		ft_putendl(buff);
		carry = sum / 10;
	}
	ft_putendl("out");
	printf("sizes[1] = %zu, sizes[0] = %zu\n", sizes[1], sizes[0]);
	while (sizes[1])
	{
		ft_putendl("---------------");
		sum = ordered[1][--sizes[1]] - '0';
		sum += carry;
		buff[index++] = (sum % 10) + '0';
		carry = sum / 10;
	}

	if (carry)
		buff[index] = carry + '0';

	result = ft_strrev(buff);
	ft_strdel(&buff);
	return result;
}

int main(int argc, char *argv[])
{
	char *str = sum_str("000001400", "000000200");

	ft_putendl(str);
	ft_strdel(&str);
    return 0;
}
