/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 13:53:22 by archid-           #+#    #+#             */
/*   Updated: 2019/09/30 02:08:50 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "format.h"

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

int				check_flags(char **fmt, t_frmt *frmt)
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
			break ;
		bar++;
	}
	*fmt = bar;
	return (1);
}

int				check_modifier(char **fmt, t_frmt *frmt)
{
	t_modif	len;
	char	*bar;

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
		else if (*bar == 'z')
			len = MOD_Z;
		else if (*bar == 'j')
			len = MOD_J;
		if (len != MOD_NA)
			*fmt = bar + 1 + (len == MOD_HH || len == MOD_LL);
		frmt->length = len;
		return (1);
	}
	return (0);
}

int				check_conversion(char **fmt, t_frmt *frmt)
{
	if (!SAFE_PTRVAL(fmt) || !(*fmt)[0] || !frmt)
		return (0);
	if (!check_integer_conversions(frmt, (*fmt)[0]))
		if (!check_floating_point_conv(frmt, (*fmt)[0]))
		{
			if (ft_strchr("cC", (*fmt)[0]))
				frmt->conv = CONV_CHAR;
			else if (ft_strchr("sSrv", (*fmt)[0]))
			{
				frmt->conv = CONV_STR;
				frmt->reverse_string = ((*fmt)[0] == 'r');
				frmt->non_printable = ((*fmt)[0] == 'v');
			}
			else if ((*fmt)[0] == 'p')
				frmt->conv = CONV_PTR;
			else if ((*fmt)[0] == '%')
				frmt->conv = CONV_PERC;
			else
				return (0);
		}
	frmt->length = ft_strchr(LONG_TYPES, (*fmt)[0]) ? MOD_L : frmt->length;
	frmt->is_upcase = ft_strchr(UPPER_TYPES, (*fmt)[0]) != NULL;
	*fmt += 1;
	return (1);
}
