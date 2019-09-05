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
#include "ieeefp.h"

/*
  FIXME: try to allocated memory fpr exatly dest size chars

  IDEA:
  =====

  move over the string to count the length
  allocated memory for exactly that length + 1
  code the process of decoding
*/
static t_s8 dest[0xffff];

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
	else if (frmt->conv == CONV_UHEX || frmt->conv == CONV_PTR)
		str = handle_unsigned_deci(frmt,
								   frmt->is_upcase ? BASE_UHEX : BASE_LHEX);
	else if (format_isfloat(frmt))
		str = handle_floating_point(frmt);
	else if (frmt->conv == CONV_CHAR)
		str = handle_char(frmt);
	else if (frmt->conv == CONV_STR || frmt->conv == CONV_FRMT)
		str = handle_string(frmt);

	return (str);
}

char	*handle_unsigned_deci(t_frmt *frmt, const char *base)
{
	char *str;

	if (frmt->length == MOD_LL)
		str = ft_utoa_base((t_u128)frmt->data.ll, base);
	else if (frmt->length == MOD_L || frmt->conv == CONV_PTR)
		str = ft_utoa_base((t_u64)frmt->data.l, base);
	else if (frmt->length == MOD_H)
		str = ft_utoa_base((t_u16)frmt->data.s, base);
	else
		str = ft_utoa_base((t_u32)frmt->data.i, base);
	return (str);
}

char	*handle_signed_deci(t_frmt *frmt)
{
	if (frmt->length == MOD_LL)
		return ft_itoa_base((t_s128)frmt->data.ll, BASE_DEC);
	else if (frmt->length == MOD_L)
		return ft_itoa_base((t_s64)frmt->data.l, BASE_DEC);
	else if (frmt->length == MOD_H)
		return ft_itoa_base((t_s16)frmt->data.s, BASE_DEC);
	else
		return ft_itoa_base((t_s32)frmt->data.i, BASE_DEC);
}

/*
   XXX: %.0f shows weird output!

   XXX: handle special values

   procedure is as the following:

   get value of va_arg() as either double or long double.
     - check if value is inf
     - check if value is nan
*/

char	*ieee_sp_as_str(t_ieeesp sp, t_frmt *frmt)
{
	char *s;
	bool is_sp;

	s = NULL;
	is_sp = false;

	if ((is_sp = (sp == IEEE_INFINI_P || sp == IEEE_INFINI_N)))
		s = ft_strdup(frmt->is_upcase ? "INF" : "inf");
	else if ((is_sp = sp == IEEE_NOT_A_NUMBER))
		s = ft_strdup(frmt->is_upcase ? "NAN" : "nan");
	if (is_sp)
	{
		if (sp == IEEE_NOT_A_NUMBER)
			frmt->flags &= ~(FLAG(FL_SPACE) | FLAG(FL_PLUS));
		frmt->flags &= ~FLAG(FL_ZERO);
	}
	return (s);
}

char	*handle_floating_point(t_frmt *frmt)
{
	char *str;
	t_ieeefp fp;
	t_s32 exp;
	t_ieee_fmt style;
	t_ieeesp sp;

	if (format_isfloat(frmt) && !frmt->has_radix)
		frmt->prec = 6;

	if (frmt->length == MOD_L_CAP)
		fp.ld.ld = frmt->data.ld;
	else
		fp.d.d = frmt->data.d;

	if ((sp = is_special_value(fp, IEEE_DOUBLE)))
		return ieee_sp_as_str(sp, frmt);

	ft_putendl("here");
	getchar();
	if (frmt->conv == CONV_HDBL)
	{
		str = ieee_hex_style(fp, frmt->is_upcase);
	}
	else
	{
		style = IEEE_NORMAL;
		if (frmt->conv == CONV_EDBL)
			style = IEEE_EXPONENT;
		else if (frmt->conv == CONV_GDBL)
		{
			/*
			   NOTE: is style is suitable, allow trim
			*/
			style = IEEE_SUITABLE;
			if (frmt->has_radix && !frmt->prec)
				frmt->prec = 1;
		}

		/*
		   XXX: here you have to alter the exponent
		   sending the exponent by reference
		*/

		/* NOTE: this should be ieee_tostr() */
		str = (frmt->length == MOD_L_CAP)
			? ieee_ldtoa(frmt->data.d, frmt->prec)
			: ieee_dtoa(frmt->data.d, frmt->prec, style, &exp);

		/* ft_putstr(" dbl ?? "); ft_putendl(str); */
		/* getchar(); */

		/* FIXME: this belongs to flags.alterform() */
		if (HAS_FLAG(frmt, FL_HASH) && !ft_strchr(str, '.'))
			/* TODO: trim zeros */
			ft_strappend(&str, ".");

		if (frmt->conv == CONV_EDBL)
			ieee_sci_style(&str, exp, frmt->is_upcase);
		else if (frmt->conv == CONV_GDBL)
			ieee_suitable_style(&str, frmt->is_upcase);
		/*

		   num
		   0000000000010110010000001010001110101101000110001101001001011111
		   denum
		   0000000000000010100000000000000000000000000000000000000000000000
		   num
		   0000000011011110100001100110010011000010111110000011011110110110
		   denum
		   0000000000000000010000000000000000000000000000000000000000000000

		*/
	}
	return (str);
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

	if (frmt->conv == CONV_FRMT || frmt->length != MOD_L)
		return ft_strdup(frmt->data.str);

	ft_bzero(dest, 0xffff);
	ret = ft_utf8tostr(dest, 0xffff, frmt->data.wstr, 0xffff);
	str = ft_strrdup(dest, dest + ret);
	return (str);
}
