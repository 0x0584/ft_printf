/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 23:00:18 by archid-           #+#    #+#             */
/*   Updated: 2019/06/30 03:02:06 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_s16		ft_wordcount(char const *s, char using)
{
	size_t count;

	count = 0;
	while (*s == using)
		s++;
	while (*s)
	{
		while (*s && *s == using)
			s++;
		count += !!*s;
		while (*s && *s != using)
			s++;
	}
	return (count);
}
