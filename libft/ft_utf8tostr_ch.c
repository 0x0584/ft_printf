/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utf8tostr_ch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 23:09:02 by archid-           #+#    #+#             */
/*   Updated: 2019/07/26 08:22:42 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_s16		ft_utf8tostr_ch(t_s8 *dest, t_s32 wch)
{
	t_s16 i;

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
    else if (wch <= 0xFFFF)
	{
        dest[i++] = 0xF0 | (wch >> 18);
        dest[i++] = 0x80 | ((wch >> 12) & 0x3F);
        dest[i++] = 0x80 | ((wch >> 6) & 0x3F);
        dest[i++] = 0x80 | (wch & 0x3F);
    }
	else
		return (-1);
    return (i);
}
