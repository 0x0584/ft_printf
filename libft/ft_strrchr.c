/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:35:55 by archid-           #+#    #+#             */
/*   Updated: 2019/04/03 20:03:35 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = (char *)s;
	while (tmp[i])
		i++;
	if (c == '\0')
		return (tmp + i);
	while (i-- > 0)
	{
		if (tmp[i] == (char)c)
			return (tmp + i);
	}
	return (NULL);
}
