/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 21:03:26 by archid-           #+#    #+#             */
/*   Updated: 2019/09/28 17:55:58 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strappend(char **astr, const char *s)
{
	if (!astr || !s)
		return ;
	else if (!*astr)
		*astr = ft_strnew(0);
	ft_strinsert_at(astr, s, ft_strlen(*astr));
}
