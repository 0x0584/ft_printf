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
	return (c == SIGNED_DECI ||
			c == U_OCTA ||
			c == U_DECI ||
			c == U_HEXA ||
			c == U_HEXA2);
}

bool	format_isfloat(t_frmt *frmt)
{
	t_int8 c;

	c = frmt->conv;
	return (c == DBL_EXP ||
			c == DBL_EXP2 ||
			c == DBL_NRML ||
			c == DBL_NRML2);
}

char	format_getsign(t_frmt *frmt)
{
	if (frmt->conv == SIGNED_DECI)
	{
		if (frmt->length == MODIF_L)
			return (frmt->u_data.l < 0) ? '-' : '+';
		else if (frmt->length == MODIF_LL)
			return (frmt->u_data.ll < 0) ? '-' : '+';
		else
			return (frmt->u_data.i < 0) ? '-' : '+';
	}
	else if (frmt->conv == DBL_EXP ||
				frmt->conv == DBL_EXP2 ||
				frmt->conv == DBL_NRML ||
				 frmt->conv == DBL_NRML2)
	{
		if (frmt->length == MODIF_L)
			return (frmt->u_data.ld < 0) ? '-' : '+';
		else
			return (frmt->u_data.d < 0) ? '-' : '+';
	}
	return ('+');
}

char	*format_ieee_float(t_frmt *frmt)
{
	return ((frmt->length == MODIF_LL)
			? ft_dtoa(frmt->u_data.ld, frmt->precision)
			: ft_ldtoa(frmt->u_data.d, frmt->precision));
}

void	format_alterform(char **astr, t_frmt *frmt)
{
	if (format_isnumeric(frmt))
	{
		if (frmt->conv == U_OCTA)
			ft_strprepend(astr, "0");
		else if (frmt->conv == U_HEXA)
			ft_strprepend(astr, "0x");
		else if (frmt->conv == U_HEXA2)
			ft_strprepend(astr, "0X");
	}
/*
  call buffutils_pad(dest, "0", 1) for %o
  call buffutils_pad(dest, "0x", 2) for %x
  call buffutils_pad(dest, "0X", 1) for %X

  if format_isfloat(frmt)
  dest = ft_format_ieee_float(frmt, trailing_is_on) // default off
*/

}
