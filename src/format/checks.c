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

static bool		check_integer_conversions(t_frmt *frmt, char conv)
{
	if (conv == 'd' || conv == 'D' || conv == 'i')
		frmt->conv = CONV_INT;
	else if (conv == 'o' || conv == 'O')
		frmt->conv = CONV_UOCT;
	else if (conv == 'u' || conv == 'U')
		frmt->conv = CONV_UDEC;
	else if (conv == 'b' || conv == 'B')
		frmt->conv = CONV_UBIN;
	else if (conv == 'x' || conv == 'X')
		frmt->conv = CONV_UHEX;
	else
		return (false);
	return (true);
}

static bool		check_floating_point_conv(t_frmt *frmt, char conv)
{
	if (conv == 'e' || conv == 'E')
		frmt->conv = CONV_EDBL;
	else if (conv == 'g' || conv == 'G')
		frmt->conv = CONV_GDBL;
	else if (conv == 'a' || conv == 'A')
		frmt->conv = CONV_HDBL;
	else if (conv == 'f' || conv == 'F')
		frmt->conv = (frmt->length == MOD_L_CAP ? CONV_LDBL : CONV_DBL);
	else
		return (false);
	return (true);
}

int			check_conversion(char **fmt, t_frmt *frmt)
{
	char *bar;

	bar = *fmt;
	if (!check_integer_conversions(frmt ,*bar))
		if (!check_floating_point_conv(frmt, *bar))
		{
			if (*bar == 'c' || *bar == 'C')
				frmt->conv = CONV_CHAR;
			else if (*bar == 's' || *bar == 'S'
						|| *bar == 'r' || *bar == 'v')
			{
				frmt->conv = CONV_STR;
				frmt->reverse_string = (*bar == 'r');
				frmt->non_printable = (*bar == 'v');
			}
			else if (*bar == 'p')
				frmt->conv = CONV_PTR;
			else
				return (0);
		}
	if (ft_strchr(LONG_TYPES, *bar))
		frmt->length = MOD_L;
	if (ft_strchr(UPPER_TYPES, *bar))
		frmt->is_upcase = true;
	*fmt = ++bar;
	return (1);
}
