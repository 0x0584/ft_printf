/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utf8tostr_ch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 23:09:02 by archid-           #+#    #+#             */
/*   Updated: 2019/06/30 03:05:22 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_int8	ft_utf8tostr_ch(t_int8 *dest, t_int32 ch)
{
	t_int8 i;

	i = 0;
    if (ch < 0x80)
        dest[i++] = (char)ch;
    else if (ch < 0x800) {
        dest[i++] = (ch >> 6) | 0xC0;
        dest[i++] = (ch & 0x3F) | 0x80;
    }
    else if (ch < 0x10000) {
        dest[i++] = (ch >> 12) | 0xE0;
        dest[i++] = ((ch >> 6) & 0x3F) | 0x80;
        dest[i++] = (ch & 0x3F) | 0x80;
    }
    else if (ch < 0x110000) {
        dest[i++] = (ch >> 18) | 0xF0;
        dest[i++] = ((ch >> 12) & 0x3F) | 0x80;
        dest[i++] = ((ch >> 6) & 0x3F) | 0x80;
        dest[i++] = (ch & 0x3F) | 0x80;
    }
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
