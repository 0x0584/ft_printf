/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 15:35:27 by archid-           #+#    #+#             */
/*   Updated: 2019/04/12 21:11:44 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s, const char *tofind)
{
	size_t i;
	size_t j;

	if (!*tofind)
		return ((char *)s);
	i = 0;
	while (s[i])
	{
		j = 0;
		while (tofind[j] && s[i + j] == tofind[j])
			j++;
		if (tofind[j] == '\0')
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}
