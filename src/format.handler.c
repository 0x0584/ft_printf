/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:05:15 by archid-           #+#    #+#             */
/*   Updated: 2019/08/06 15:52:58 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "format.h"

/*
 * FIXME: try to allocated memory fpr exatly dest size chars
 *
 * IDEA:
 * =====
 *
 * move over the string to count the length
 * allocated memory for exactly that length + 1
 * code the process of decoding
 */
static t_int8 dest[0xffff];

char	*handle_unsigned_deci(t_frmt *frmt, const char *base)
{
	char *str;

	if (frmt->length == MOD_LL)
		str = ft_utoa_base(frmt->data.ll, base);
	else if (frmt->length == MOD_L)
		str = ft_utoa_base(frmt->data.l, base);
	else if (frmt->length == MOD_H)
		str = ft_utoa_base(frmt->data.s, base);
	else
		str = ft_utoa_base(frmt->data.i, base);
	return (str);
}

char	*handle_signed_deci(t_frmt *frmt)
{
	if (frmt->length == MOD_LL)
		return ft_itoa_base(frmt->data.ll, BASE_DEC);
	else if (frmt->length == MOD_L)
		return ft_itoa_base(frmt->data.l, BASE_DEC);
	else if (frmt->length == MOD_H)
		return ft_itoa_base(frmt->data.s, BASE_DEC);
	else
		return ft_itoa_base(frmt->data.i, BASE_DEC);
}

char	*handle_floating_point(t_frmt *frmt)
{
	char *str;

	/* if (frmt->length == MOD_L) */
	/* 	str = ft_ldtoa(frmt->data.d, frmt->precision); */
	/* else */
	/* 	str = ft_dtoa(frmt->data.d, frmt->precision); */
	(void)frmt;
	str = NULL;
	return str;
}

char	*handle_char(t_frmt *frmt)
{
	char *str;

	if (frmt->length != MOD_L)
	{
		str = ft_strnew(1);
		*str = (char)frmt->data.i;
	}
	else
	{
		ft_bzero(dest, 5);
		ft_utf8tostr_ch(dest, frmt->data.i);
		str = ft_strdup(dest);
	}

	return (str);
}

char	*handle_string(t_frmt *frmt)
{
	char *str;
	int ret;

	if (frmt->length != MOD_L)
		return ft_strdup(frmt->data.str);

	ft_bzero(dest, 0xffff);
	ret = ft_utf8tostr(dest, 0xffff, frmt->data.wstr, 0xffff);
	str = ft_strrdup(dest, dest + ret);
	return (str);
}
