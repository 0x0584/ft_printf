/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnprepend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 14:50:31 by archid-           #+#    #+#             */
/*   Updated: 2019/09/28 17:53:15 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t		ft_strnprepend(char **dest, const char *prefix, size_t prefixsz)
{
	char	*s;
	size_t	destsz;

	if (!dest || !*dest)
		return (-1);
	destsz = ft_strlen(*dest);
	if (!(s = ft_strnew(destsz + prefixsz)))
		return (0);
	while (destsz--)
		s[destsz + prefixsz] = (*dest)[destsz];
	while (prefixsz--)
		s[prefixsz] = prefix[prefixsz];
	ft_strdel(dest);
	*dest = s;
	return (destsz + prefixsz);
}
