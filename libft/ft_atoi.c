/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:23:59 by archid-           #+#    #+#             */
/*   Updated: 2019/04/10 17:50:46 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *s)
{
	long	result;
	int		sign;
	char	*str;
	size_t	len;

	sign = 1;
	str = (char *)s;
	while (ft_isspace(*str))
		str++;
	if ((*str == '-' || *str == '+') && (*str++ == '-'))
		sign = -1;
	len = 0;
	while (ft_isdigit(str[len]))
		len++;
	result = 0;
	while (ft_isdigit(*str))
		result += ft_power(10, --len) * (*str++ - '0');
	return ((int)result * sign);
}
