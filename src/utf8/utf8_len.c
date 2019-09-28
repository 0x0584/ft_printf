/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utf8_len.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 04:15:09 by archid-           #+#    #+#             */
/*   Updated: 2019/09/28 19:18:21 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utf8.h"

t_u16		utf8_chlen(t_s32 wch)
{
	if (wch <= 0x7F)
		return (1);
	else if (wch <= 0x7FF)
		return (2);
	else if (wch <= 0XFFFF)
		return (3);
	return (4);
}

size_t		utf8_strsize(wchar_t *s)
{
	size_t	len;
	wchar_t *walk;

	len = 0;
	walk = s;
	while (*walk != L'\0')
		len += utf8_chlen(*walk++);
	return (len);
}

size_t		utf8_wstrlen(wchar_t *s)
{
	size_t	len;
	wchar_t *walk;

	len = 0;
	if (s == NULL)
		return (len);
	walk = s;
	while (walk[len] != L'\0')
		len++;
	return (len);
}
