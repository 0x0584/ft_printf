/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsubswap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 14:06:38 by archid-           #+#    #+#             */
/*   Updated: 2019/09/28 17:51:42 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strsubswap(char **astr, const char *s1, const char *s2)
{
	if (!SAFE_PTRVAL(astr))
		return ;
	ft_strreplace(astr, s1, s2);
	ft_strreplace(astr, s2, s1);
}
