/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 23:27:49 by archid-           #+#    #+#             */
/*   Updated: 2019/07/19 23:37:18 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(const char *str)
{
	char	*rev;
	size_t	walker[2];

	walker[0] = 0;
	walker[1] = ft_strlen(str);
	if (!(rev = ft_strnew(walker[1])))
		return (NULL);
	while (walker[0] < walker[1])
	{
		rev[walker[0]] = str[walker[1] - walker[0] - 1];
		walker[0]++;
	}
	return (rev);
}
