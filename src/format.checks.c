/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 format.checks.c									:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <archid-@student.1337.ma>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/06/23 13:53:22 by archid-		   #+#	  #+#			  */
/*   Updated: 2019/08/06 14:17:44 by archid-          ###   ########.fr       */
/*																			  */
/* ************************************************************************** */

#include "format.h"

int		check_flags(char **fmt, t_frmt *frmt)
{
	char *bar;

	bar = *fmt;
	while (*bar)
	{
		if (*bar == '#')
			frmt->flags |= FLAG(FL_HASH);
		else if (*bar == '+')
			frmt->flags |= FLAG(FL_PLUS);
		else if (*bar == ' ')
			frmt->flags |= FLAG(FL_SPACE);
		else if (*bar == '-')
			frmt->flags |= FLAG(FL_MINUS);
		else if (*bar == '0')
			frmt->flags |= FLAG(FL_ZERO);
		else
			break;
		bar++;
	}
	*fmt = bar;
	return (1);
}

int		check_modifier(char **fmt, t_frmt *frmt)
{
	t_modif		len;
	char		*bar;

	bar = *fmt;
	len = MOD_NA;
	if (*bar)
	{
		if (*bar == 'h')
			len = (*(bar + 1) == 'h') ? MOD_HH : MOD_H;
		else if (*bar == 'l')
			len = (*(bar + 1) == 'l') ? MOD_LL : MOD_L;
		else if (*bar == 'L')
			len = MOD_L_CAP;
		if (len != MOD_NA)
			*fmt = bar + 1 + (len == MOD_HH || len == MOD_LL);
		frmt->length = len;
		return (1);
	}
	return (0);
}

#define ALL_TYPES			"dbouxffgeacsp"
#define LONG_TYPES			"DOUSC"
#define UPPER_TYPES			"XEAG"

int		check_conversion(char **fmt, t_frmt *frmt)
{
	char *bar;
	/* char *foo; */

	/* TODO: find the bug in this one! */

	/*
	if ((foo = ft_strchr(ALL_TYPES, ft_tolower(*bar))))
		frmt->conv = foo - bar;
	ft_putstr(foo);
	getchar();
	if ((foo = ft_strchr(LONG_TYPES, *bar)))
		frmt->length = MOD_L;
	if ((foo = ft_strchr(UPPER_TYPES, *bar)))
		frmt->is_upcase = true;
	*/

	bar = *fmt;

	if (*bar == 'd' || *bar == 'D' || *bar == 'i')
	{
		frmt->length = (*bar == 'D' ? MOD_L : frmt->length);
		frmt->conv = CONV_INT;
	}
	else if (*bar == 'o' || *bar == 'O')
	{
		frmt->length = (*bar == 'O' ? MOD_L : frmt->length);
		frmt->conv = CONV_UOCT;
	}
	else if (*bar == 'u' || *bar == 'U')
	{
		frmt->length = (*bar == 'U' ? MOD_L : frmt->length);
		frmt->conv = CONV_UDEC;
	}
	else if (*bar == 'x' || *bar == 'X')
		frmt->conv = CONV_UHEX;
	else if (*bar == 'e' || *bar == 'E')
		frmt->conv = CONV_EDBL;
	else if (*bar == 'f' || *bar == 'F')
		frmt->conv = (*bar == 'F' ? CONV_LDBL : CONV_DBL);
	else if (*bar == 'c' || *bar == 'C')
	{
		frmt->length = (*bar == 'C' ? MOD_L : frmt->length);
		frmt->conv = CONV_CHAR;
	}
	else if (*bar == 's' || *bar == 'S')
	{
		frmt->length = *bar == 'S' ? MOD_L : frmt->length;
		frmt->conv = CONV_STR;
	}
	else if (*bar == 'p')
		frmt->conv = CONV_PTR;
	else
		return (0);

	*fmt = ++bar;
	return (1);
}
