/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 07:06:13 by archid-           #+#    #+#             */
/*   Updated: 2019/09/28 17:59:00 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(const void *mem, size_t n)
{
	t_s8 *buff;

	if (!(buff = ALLOC(t_s8 *, n, sizeof(t_s8))))
		return (NULL);
	return (ft_memcpy(buff, mem, n));
}
