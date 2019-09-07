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
#include "utf8.h"
#include "ieeefp.h"

/*
  BUG: unsigned conversions have problem with negative numbers

  it's probably due to conversions are all treated as intmax_t, while unsigned
  numbers consided the sign bit as significat bit. probably I have to create a
  one for each data type

	format (%#04x) arg -89999

	mine:	(0xFFFFFFFFFFFEA071)
	glibc:	(0xfffea071)

	format (%#04o) arg -89999

	mine:	(01777777777777777520161)
	glibc:	(037777520161)

	format	(%#04o) arg 89999

	mine:	(0257617)
	glibc:	(0257617)
*/

static char		*handle_unsigned_deci(t_frmt *frmt, const char *base)
{
	if (frmt->length == MOD_LL)
		return ft_utoa_base((t_u128)frmt->data.ull, base);
	else if (frmt->length == MOD_L || frmt->conv == CONV_PTR)
		return ft_utoa_base((t_u64)frmt->data.ul, base);
	else if (frmt->length == MOD_H)
		return ft_utoa_base((t_u16)frmt->data.us, base);
	else if (frmt->length == MOD_HH)
		return ft_utoa_base((t_u8)frmt->data.uc, base);
	else if (frmt->length == MOD_Z)
		return ft_utoa_base((size_t)frmt->data.usz, base);
	else if (frmt->length == MOD_J)
		return ft_utoa_base((uintmax_t)frmt->data.uj, base);
	else
		return ft_utoa_base((t_u32)frmt->data.ui, base);
	return (NULL);
}

static char	*handle_signed_deci(t_frmt *frmt)
{
	if (frmt->length == MOD_LL)
		return ft_itoa_base((t_s128)frmt->data.ll, BASE_DEC);
	else if (frmt->length == MOD_L)
		return ft_itoa_base((t_s64)frmt->data.l, BASE_DEC);
	else if (frmt->length == MOD_H)
		return ft_itoa_base((t_s16)frmt->data.s, BASE_DEC);
	else if (frmt->length == MOD_HH)
		return ft_itoa_base((t_s8)frmt->data.c, BASE_DEC);
	else if (frmt->length == MOD_Z)
		return ft_itoa_base((ssize_t)frmt->data.sz, BASE_DEC);
	else if (frmt->length == MOD_J)
		return ft_itoa_base((intmax_t)frmt->data.j, BASE_DEC);
	else
		return ft_itoa_base((t_s32)frmt->data.i, BASE_DEC);
}

static char		*handle_floating_point(t_frmt *frmt)
{
	t_ieeefp		fp;
	t_ieee_fmt		style;
	t_ieeesp		sp;

	if (format_isfloat(frmt) && !frmt->has_radix
			&& frmt->conv != CONV_HDBL)
		frmt->prec = 6;
	ieee_set_fp(&fp, frmt);
	if ((sp = ieee_is_spval(&fp)))
		return ieee_sp_as_str(sp, frmt);
	if (frmt->conv == CONV_HDBL)
		return ieee_hex_style(&fp, frmt->prec, frmt->is_upcase);
	style = IEEE_NORMAL;
	if (frmt->conv == CONV_EDBL)
		style = IEEE_EXPONENT;
	else if (frmt->conv == CONV_GDBL)
	{
		style = IEEE_SUITABLE;
		if (frmt->has_radix && !frmt->prec)
			frmt->prec = 1;
	}
	return ieee_tostr(&fp, style, frmt);
}

static char		*handle_char(t_frmt *frmt)
{
	char *str;
	char dest[5];

	if (frmt->length != MOD_L)
	{
		str = ft_strnew(1);
		*str = (char)frmt->data.i;
	}
	else
	{
		ft_bzero(dest, 5);
		utf8_tostr_ch(dest, frmt->data.wc);
		str = ft_strdup(dest);
	}
	return (str);
}

static char		*handle_string(t_frmt *frmt)
{
	char *str;

	if (frmt->conv == CONV_FRMT || frmt->length != MOD_L)
		return ft_strdup(frmt->data.str);
	str = ft_strnew(0);
	utf8_tostr(&str, frmt->data.wstr);
	return (str);
}

char			*format_handle_conversion(t_frmt *frmt)
{
	char *str;

	str = NULL;
	if (frmt->conv == CONV_INT)
		str =  handle_signed_deci(frmt);
	else if (frmt->conv == CONV_UOCT)
		str = handle_unsigned_deci(frmt, BASE_OCT);
	else if (frmt->conv == CONV_UDEC)
		str = handle_unsigned_deci(frmt, BASE_DEC);
	else if (frmt->conv == CONV_UBIN)
		str = handle_unsigned_deci(frmt, BASE_BIN);
	else if (frmt->conv == CONV_UHEX || frmt->conv == CONV_PTR)
		str = handle_unsigned_deci(frmt, frmt->is_upcase
											? BASE_UHEX : BASE_LHEX);
	else if (format_isfloat(frmt))
		str = handle_floating_point(frmt);
	else if (frmt->conv == CONV_CHAR)
		str = handle_char(frmt);
	else if (frmt->conv == CONV_STR || frmt->conv == CONV_FRMT)
		str = handle_string(frmt);
	return (str);
}
