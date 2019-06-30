/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 18:17:07 by archid-           #+#    #+#             */
/*   Updated: 2019/06/30 01:30:21 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	t_int8	*buff1;
	t_int8	*buff2;
	size_t	i;

	i = 0;
	buff1 = (t_int8 *)s1;
	buff2 = (t_int8 *)s2;
	if (n == 0)
		return (0);
	while (buff1[i] == buff2[i] && --n)
		i++;
	return (buff1[i] - buff2[i]);
}
