/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:05:15 by archid-           #+#    #+#             */
/*   Updated: 2019/09/30 02:44:49 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "format.h"
#include "ieeefp.h"
#include "utf8.h"

char		*handle_unsigned_deci(t_frmt *frmt, const char *base)
{
	if (frmt->length == MOD_LL)
		return (ft_utoa_base((t_u128)frmt->data.ull, base));
	else if (frmt->length == MOD_L || frmt->conv == CONV_PTR)
		return (ft_utoa_base((t_u64)frmt->data.ul, base));
	else if (frmt->length == MOD_H)
		return (ft_utoa_base((t_u16)frmt->data.us, base));
	else if (frmt->length == MOD_HH)
		return (ft_utoa_base((t_u8)frmt->data.uc, base));
	else if (frmt->length == MOD_Z)
		return (ft_utoa_base((size_t)frmt->data.usz, base));
	else if (frmt->length == MOD_J)
		return (ft_utoa_base((uintmax_t)frmt->data.uj, base));
	return (ft_utoa_base((t_u32)frmt->data.ui, base));
}

char		*handle_signed_deci(t_frmt *frmt)
{
	if (frmt->length == MOD_LL)
		return (ft_itoa_base((t_s128)frmt->data.ll, BASE_DEC));
	else if (frmt->length == MOD_L)
		return (ft_itoa_base((t_s64)frmt->data.l, BASE_DEC));
	else if (frmt->length == MOD_H)
		return (ft_itoa_base((t_s16)frmt->data.s, BASE_DEC));
	else if (frmt->length == MOD_HH)
		return (ft_itoa_base((t_s8)frmt->data.c, BASE_DEC));
	else if (frmt->length == MOD_Z)
		return (ft_itoa_base((ssize_t)frmt->data.sz, BASE_DEC));
	else if (frmt->length == MOD_J)
		return (ft_itoa_base((intmax_t)frmt->data.j, BASE_DEC));
	return (ft_itoa_base((t_s32)frmt->data.i, BASE_DEC));
}

char		*handle_floating_point(t_frmt *frmt)
{
	char			*s;
	t_ieeefp		fp;
	t_ieee_fmt		style;

	if (format_isfloat(frmt) && frmt->conv != CONV_HDBL
			&& !frmt->has_radix)
		frmt->prec = 6;
	ieee_set_fp(&fp, frmt);
	if ((s = ieee_sp_as_str(&fp, frmt)))
		return (s);
	else if (frmt->conv == CONV_HDBL)
		return (ieee_hex_style(&fp, frmt->prec, frmt->is_upcase));
	style = IEEE_NORMAL;
	if (frmt->conv == CONV_EDBL)
		style = IEEE_EXPONENT;
	else if (frmt->conv == CONV_GDBL)
	{
		style = IEEE_SUITABLE;
		if (frmt->has_radix && !frmt->prec)
			frmt->prec = 1;
	}
	return (ieee_tostr(&fp, style, frmt));
}

char		*handle_char(t_frmt *frmt)
{
	char dest[5];

	ft_bzero(dest, 5);
	if (frmt->length != MOD_L)
	{
		if (!(*dest = (char)frmt->data.i))
			frmt->is_nulchr = true;
	}
	else
		utf8_tostr_ch(dest, frmt->data.wc);
	return (frmt->is_nulchr ? ft_strnew(1) : ft_strdup(dest));
}

char		*handle_string(t_frmt *frmt)
{
	char *str;

	str = NULL;
	if (frmt->conv == CONV_FRMT || frmt->length != MOD_L)
	{
		if (!frmt->data.str)
			return (ft_strdup("(null)"));
		if (frmt->reverse_string)
			ft_strchange(&str, ft_strrev(frmt->data.str));
		else if (frmt->non_printable)
			ft_strchange(&str, ft_strnonprintable(frmt->data.str));
		else
			str = ft_strdup(frmt->data.str);
		return (str);
	}
	if (!frmt->data.wstr)
		return (ft_strdup("(null)"));
	utf8_tostr(&str, frmt->data.wstr);
	return (str);
}
