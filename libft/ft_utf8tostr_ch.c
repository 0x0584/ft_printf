/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utf8tostr_ch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 23:09:02 by archid-           #+#    #+#             */
/*   Updated: 2019/07/02 17:09:25 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_int8	ft_utf8tostr_ch(t_int8 *dest, t_int32 wch)
{
	t_int8 i;

	i = 0;
    if (wch <= 0x7F)
        dest[i++] = (t_int8)wch;
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

/*
int main()
{
	t_int32 *input = L"@&@{čřžŧ¶'`[łĐŧđĐ¶←^€~[←^ø{&}čž";

	char dest[50];
	size_t ret;

	ret = ft_strtoutf8(dest, 50, input, 50);
	write(1, dest, ret);
	return 0;
}
*/
