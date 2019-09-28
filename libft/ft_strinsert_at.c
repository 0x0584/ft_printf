/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert_at.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 05:58:08 by archid-           #+#    #+#             */
/*   Updated: 2019/09/28 17:54:35 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strinsert_at(char **str, char const *src, size_t index)
{
	char	*foo;
	size_t	sizes[2];

	if (!str || !*str)
		return ;
	sizes[0] = ft_strlen(*str);
	sizes[1] = ft_strlen(src);
	if (index > sizes[0] || !(foo = ft_strnew(sizes[0] + sizes[1])))
		return ;
	ft_strncpy(foo, *str, index);
	ft_strncpy(foo + index, src, sizes[1]);
	ft_strncpy(foo + sizes[1] + index, *str + index, sizes[0] - index);
	ft_strdel(str);
	*str = foo;
}
