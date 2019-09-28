/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utf8tostr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 23:08:36 by archid-           #+#    #+#             */
/*   Updated: 2019/09/28 19:19:43 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utf8.h"

t_s16		utf8_tostr_ch(t_s8 *dest, t_s32 wch)
{
	t_s16	i;

	i = 0;
	if (wch <= 0x7F)
		dest[i++] = (t_s8)wch;
	else if (wch <= 0x7FF)
	{
		dest[i++] = 0xC0 | (wch >> 6);
		dest[i++] = 0x80 | (wch & 0x3F);
	}
	else if (wch <= 0xFFFF)
	{
		dest[i++] = 0xE0 | (wch >> 12);
		dest[i++] = 0x80 | ((wch >> 6) & 0x3F);
		dest[i++] = 0x80 | (wch & 0x3F);
	}
	else if (wch <= 0x1FFFFF)
	{
		dest[i++] = 0xF0 | (wch >> 18);
		dest[i++] = 0x80 | ((wch >> 12) & 0x3F);
		dest[i++] = 0x80 | ((wch >> 6) & 0x3F);
		dest[i++] = 0x80 | (wch & 0x3F);
	}
	return (i);
}

void		utf8_tostr(t_s8 **dest, const wchar_t *wsrc)
{
	t_s64	i;
	char	buff[5];

	i = 0;
	while (wsrc[i] != L'\0')
	{
		ft_bzero(buff, 5);
		utf8_tostr_ch(buff, wsrc[i++]);
		ft_strappend(dest, buff);
	}
}

char		*utf8_moveto(wchar_t *s, char *buff, size_t nth_ch)
{
	size_t	len;
	size_t	walk;

	len = 0;
	walk = 0;
	while (walk < nth_ch)
		len += utf8_chlen(s[walk++]);
	return (buff + len);
}
