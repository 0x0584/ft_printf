/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 22:12:16 by archid-           #+#    #+#             */
/*   Updated: 2019/09/28 18:36:53 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "format.h"

bool	format_isnumeric(t_frmt *frmt)
{
	t_s8 c;

	c = frmt->conv;
	return (c == CONV_INT || c == CONV_UOCT || c == CONV_UBIN
				|| c == CONV_UDEC || c == CONV_UHEX);
}

bool	format_isfloat(t_frmt *frmt)
{
	t_s8 c;

	c = frmt->conv;
	return (c == CONV_DBL || c == CONV_LDBL
				|| c == CONV_GDBL || c == CONV_EDBL
				|| c == CONV_HDBL);
}

char	format_getsign(t_frmt *frmt)
{
	if (frmt->conv == CONV_INT)
	{
		if (frmt->length == MOD_LL)
			return (frmt->data.ll < 0) ? '-' : '+';
		else if (frmt->length == MOD_L)
			return (frmt->data.l < 0) ? '-' : '+';
		else
			return (frmt->data.i < 0) ? '-' : '+';
	}
	else if (format_isfloat(frmt))
	{
		if (frmt->length == MOD_L)
			return (frmt->data.ld < 0) ? '-' : '+';
		else
			return (frmt->data.d < 0) ? '-' : '+';
	}
	return ('+');
}
