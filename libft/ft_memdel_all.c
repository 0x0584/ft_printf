/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdel_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 17:25:59 by archid-           #+#    #+#             */
/*   Updated: 2019/07/26 17:37:28 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_memdel_all(void (*del)(void *o), void *ptr, ...)
{
    va_list args;
    void	**vp;
	size_t	count;

	count = 0;
	if (ptr)
	{
		del(ptr);
		count++;
	}
    va_start(args, ptr);
    while ((vp = va_arg(args, void **)))
		if (ptr)
		{
			del(ptr);
			count++;
		}
    va_end(args);
	return (count);
}
