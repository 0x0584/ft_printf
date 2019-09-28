/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpad.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 07:09:30 by archid-           #+#    #+#             */
/*   Updated: 2019/09/28 17:53:02 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strpad(char **astr, char c, size_t n, bool left)
{
	char	*tmp;
	size_t	i;
	size_t	size;

	if (!astr || !*astr || !n)
		return ;
	size = ft_strlen(*astr) + n;
	if (!(tmp = ft_strnew(size)))
		return ;
	i = 0;
	if (left)
		while (i < n)
			tmp[i++] = c;
	ft_strncpy(tmp + i, *astr, size - n);
	if (!left)
		while (i < n)
			tmp[size - n + i++] = c;
	ft_strdel(astr);
	*astr = tmp;
}
