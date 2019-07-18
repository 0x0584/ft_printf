/*		   File:	format.numbers.c
 *		 Author:	ANAS RCHID
 *	Description:	NULL
 *
 *	  Created: <2019-07-06 Sat 22:12:16>
/*   Updated: 2019/07/14 01:56:55 by archid-          ###   ########.fr       */

#include "format.h"

bool	format_isnumeric(t_frmt *frmt)
{
	t_int8 c;

	c = frmt->conv;
	return (c == SIGNED_DECI ||
			c == UNSIGNED_OCTA ||
			c == UNSIGNED_DECI ||
			c == UNSIGNED_HEXA ||
			c == UNSIGNED_HEXA2);
}

bool	format_isfloat(t_frmt *frmt)
{
	t_int8 c;

	c = frmt->conv;
	return (c == DOUBLE_EXP ||
			c == DOUBLE_EXP2 ||
			c == DOUBLE_NORMAL ||
			c == DOUBLE_NORMAL2);
}

bool	format_getsigne(t_frmt *frmt)
{
	if (format_isfloat(frmt) || format_isnumeric(frmt))
	{
		/* TODO:
		   is it the ifs again!! something is wrong here!! */
	}
	return (!1);
}

char	*format_ieee_float(t_frmt *frmt, bool has_trailing)
{
	return NULL;
	/* return ((frmt->length == MODIF_LL) */
	/* 		? ft_ftoa854(frmt->u_data.ld, has_trailing) */
	/* 		: ft_ftoa754(frmt->u_data.d, has_trailing)); */
}

void	format_alterform(char **astr, t_frmt *frmt)
{
	if (format_isnumeric(frmt))
	{
		if (frmt->conv == UNSIGNED_OCTA)
			ft_strprepend(astr, "0");
		else if (frmt->conv == UNSIGNED_HEXA)
			ft_strprepend(astr, "0x");
		else if (frmt->conv == UNSIGNED_HEXA2)
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
