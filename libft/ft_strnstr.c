/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 18:50:51 by archid-           #+#    #+#             */
/*   Updated: 2019/04/12 21:11:08 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *tofind, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	if (!*tofind)
		return ((char *)s);
	if (len == 0)
		return (NULL);
	while (s[i])
	{
		j = 0;
		while (tofind[j] && s[i + j] == tofind[j] && i + j < len)
			j++;
		if (tofind[j] == '\0')
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}
