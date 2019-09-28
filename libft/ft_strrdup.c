/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 01:45:03 by archid-           #+#    #+#             */
/*   Updated: 2019/09/28 17:52:37 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrdup(const char *head, const char *tail)
{
	char	*buff;
	size_t	length;

	if (head > tail)
		return (NULL);
	length = 1;
	while (head + length <= tail)
		length++;
	if (!(buff = ALLOC(char *, length + 1, sizeof(char))))
		return (NULL);
	while (head + --length >= head)
		buff[length] = head[length];
	return (buff);
}
