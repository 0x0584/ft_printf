/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 17:25:59 by archid-           #+#    #+#             */
/*   Updated: 2019/07/26 17:37:28 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(void (*del)(void *o), void *ptr, ...)
{
	va_list args;
	void	*vp;

	if (ptr)
		del(ptr);
	va_start(args, ptr);
	while ((vp = va_arg(args, void *)) != NULL)
		if (vp)
			del(vp);
	va_end(args);
}
