/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 22:21:43 by archid-           #+#    #+#             */
/*   Updated: 2019/04/05 19:50:27 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t len)
{
	size_t	i;
	size_t	lens[2];
	size_t	ret;
	int		limit;

	i = -1;
	lens[0] = ft_strlen(dest);
	lens[1] = ft_strlen(src);
	limit = len - lens[0];
	ret = ((len >= lens[0]) ? lens[0] : len) + lens[1];
	while (src[++i] != '\0' && limit-- > 1)
		dest[lens[0] + i] = src[i];
	dest[lens[0] + i] = '\0';
	return (ret);
}
