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
static t_int8 dest[0xff];

/* 
   TODO: handle precision in INT
*/

char	*handle_unsigned_deci(t_frmt *frmt, int base)
{
	char *str;

	if (frmt->length == MODIF_LL)
		str = ft_itoa_base((long long)frmt->u_data.ll, base);
	else if (frmt->length == MODIF_L)
		str = ft_itoa_base((long long)frmt->u_data.l, base);
	else if (frmt->length == MODIF_H)
		str = ft_itoa_base((long long)frmt->u_data.s, base);
	else
		str = ft_itoa_base((long long)frmt->u_data.i, base);
	if (base == 16 && frmt->conv == U_HEXA2)
		ft_strtoupper(str);
	return (str);
}

char	*handle_signed_deci(t_frmt *frmt)
{
	if (frmt->length == MODIF_LL)
		return ft_lltoa((long long)frmt->u_data.ll);
	else if (frmt->length == MODIF_L)
		return ft_lltoa((long long)frmt->u_data.l);
	else if (frmt->length == MODIF_H)
		return ft_lltoa((long long)frmt->u_data.s);
	else
		return ft_lltoa((long long)frmt->u_data.i);
}

char	*handle_double(t_frmt *frmt, bool round)
{
	/* this would be e and E */
	char *str;

	if (frmt->length == MODIF_L)
		str = ft_ldtoa(frmt->u_data.d, frmt->precision, round);
	else
		str = ft_dtoa(frmt->u_data.d, frmt->precision, round);
	if (frmt->conv == DBL_EXP2)
		ft_strtoupper(str);
	return str;
}

char	*handle_char(t_frmt *frmt)
{
	char *str;

	if (frmt->length != MODIF_L)
	{
		str = ft_strnew(1);
		*str = (char)frmt->u_data.i;
	}
	else
	{
		ft_bzero(dest, 5);
		ft_utf8tostr_ch(dest, frmt->u_data.i);
		str = ft_strdup(dest);
	}

	return (str);
}

char	*handle_string(t_frmt *frmt)
{
	char *str;

	if (frmt->length != MODIF_L)
		return ft_strdup(frmt->u_data.str);

	ft_bzero(dest, 0xff);
	int ret = ft_utf8tostr(dest, 0xff, frmt->u_data.wstr, 0xff);
	str = ft_strrdup(dest, dest + ret);
	return (str);
}
