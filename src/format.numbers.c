/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 format.numbers.c									:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <archid-@student.1337.ma>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/07/06 22:12:16 by archid-		   #+#	  #+#			  */
/*   Updated: 2019/08/06 14:17:44 by archid-          ###   ########.fr       */
/*																			  */
/* ************************************************************************** */

#include "format.h"

bool	format_isnumeric(t_frmt *frmt)
{
	t_int8 c;

	c = frmt->conv;
	return (c == CONV_INT || c == CONV_UOCT
				|| c == CONV_UDEC || c == CONV_UHEX);
}

bool	format_isfloat(t_frmt *frmt)
{
	t_int8 c;

	c = frmt->conv;
	return (c == CONV_DBL || c == CONV_LDBL
				|| c == CONV_GDBL || c == CONV_EDBL);
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

char	*format_ieee_float(t_frmt *frmt)
{
	(void)frmt;
	return (NULL);
	/* return ((frmt->length == MOD_LL) */
	/* 		? ft_dtoa(frmt->data.ld, frmt->precision) */
	/* 		: ft_ldtoa(frmt->data.d, frmt->precision)); */
}

void	format_check_alterform(char **astr, t_frmt *frmt)
{
	if (!HAS_FLAG(frmt, FL_HASH) || !format_isnumeric(frmt))
		return ;

	if (frmt->conv == CONV_UOCT && ft_strcmp(*astr, "0"))
		ft_strprepend(astr, "0");
	else if (frmt->conv == CONV_UHEX)
		ft_strprepend(astr, frmt->is_upcase ?  "0X" : "0x" );

/*
  call buffutils_pad(dest, "0", 1) for %o
  call buffutils_pad(dest, "0x", 2) for %x
  call buffutils_pad(dest, "0X", 1) for %X

  if format_isfloat(frmt)
  dest = ft_format_ieee_float(frmt, trailing_is_on) // default off
*/

}
