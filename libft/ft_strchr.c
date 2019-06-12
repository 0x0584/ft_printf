/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 04:50:23 by archid-           #+#    #+#             */
/*   Updated: 2019/04/14 23:09:42 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*tmp;

	if (s == NULL)
		return (NULL);
	i = 0;
	if (s[0] == c)
		return ((char *)s);
	tmp = (char *)s;
	while (tmp[i++])
		if (tmp[i] == (char)c)
			return ((char *)tmp + i);
	return (NULL);
}
