/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 13:53:22 by archid-           #+#    #+#             */
/*   Updated: 2019/06/23 13:54:09 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "format.h"

int		check_flags(char **fmt, t_frmt *frmt)
{
	char *bar;

	bar = *fmt;

	/* FIXME: improve the flag checking process
	 *
	 * is there anyway otehr than this? find a way and implement it
	 * since this is really not crafted well. try bitwise operations!
	 *
	 * 6 bits and a bit mask!? what's that.
	 *
	 * 1111 1111
	 * 0 -+ #$''
	 */
	while (*bar)
	{
		if (*bar == '#')
			frmt->is_alter = true;
		else if (*bar == '+')
			frmt->prefix_signe = true;
		else if (*bar == ' ')
			frmt->prefix_plus_blank = true;
		else if (*bar == '-')
			frmt->padding_on_left = true;
		else if (*bar == '0')
			frmt->prefix_zeros = true;
		else
			break;
		bar++;
	}
	*fmt = bar;
	return (1);
}

int		check_modifier(char **fmt, t_frmt *frmt)
{
	enum e_modifiers len;
	char *bar;

	bar = *fmt;
	len = MODIF_DEFAULT;
	if (*bar)
    {
        if (*bar == 'h')
			len = (*(bar + 1) == 'h') ? MODIF_HH : MODIF_H;
		else if (*bar == 'l')
			len = (*(bar + 1) == 'l') ? MODIF_LL : MODIF_L;
        if (len != MODIF_DEFAULT)
			*fmt = bar + 1 + (len == MODIF_HH || len == MODIF_LL);
		frmt->length = len;
		return (1);
    }
	return (0);
}

/* TODO: disable #-flag when %{c,d,i,n,p,s,u} */
int		check_conversion(char **fmt, t_frmt *frmt)
{
	char *bar;

	bar = *fmt;
	if (*bar == 'd' || *bar == 'i')
		frmt->conv = SIGNED_DECI;
    else if (*bar == 'o')
		frmt->conv = UNSIGNED_OCTA;
    else if (*bar == 'u')
		frmt->conv = UNSIGNED_DECI;
    else if (*bar == 'x')
		frmt->conv = UNSIGNED_HEXA;
    else if (*bar == 'X')
		frmt->conv = UNSIGNED_HEXA2;
    else if (*bar == 'D')
    {
		frmt->length = MODIF_L;
		frmt->conv = SIGNED_DECI;
    }
    else if (*bar == 'O')
    {
		frmt->length = MODIF_L;
		frmt->conv = UNSIGNED_OCTA;
    }
    else if (*bar == 'U')
    {
		frmt->length = MODIF_L;
		frmt->conv = UNSIGNED_DECI;
    }
    else if (*bar == 'e')
		frmt->conv = DOUBLE_EXP;
    else if (*bar == 'E')
		frmt->conv = DOUBLE_EXP2;
    else if (*bar == 'f')
		frmt->conv = DOUBLE_NORMAL;
    else if (*bar == 'F')
		frmt->conv = DOUBLE_NORMAL2;
    else if (*bar == 'c')
		frmt->conv = CHAR;
    else if (*bar == 'C')
    {
		frmt->length = MODIF_L;
		frmt->conv = CHAR;
    }
    else if (*bar == 's')
		frmt->conv = STRING;
    else if (*bar == 'S')
    {
		frmt->length = MODIF_L;
		frmt->conv = STRING;
    }
    else if (*bar == 'p')
		frmt->conv = POINTER;
    else if (*bar == '%')
		frmt->conv = PERCENTAGE;
	return (1);
}
