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
  FIXME: try to allocated memory fpr exatly dest size chars

  IDEA:
  =====

  move over the string to count the length
  allocated memory for exactly that length + 1
  code the process of decoding
*/
static t_int8 dest[0xffff];

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
	else if (frmt->conv == CONV_UHEX)
		str = handle_unsigned_deci(frmt, BASE_UHEX);
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
