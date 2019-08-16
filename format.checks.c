/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 format.checks.c									:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <archid-@student.1337.ma>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/06/23 13:53:22 by archid-		   #+#	  #+#			  */
/*	 Updated: 2019/06/30 03:06:52 by archid-		  ###	########.fr		  */
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
		/* FIXME: handle L for long double */
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

	/* TODO: create a function int foo(char c) which computes
	 * the conversion index */
	bar = *fmt;
	if (*bar == 'd' || *bar == 'D' || *bar == 'i')
	{
		frmt->length = (*bar == 'D' ? MODIF_L : frmt->length);
		frmt->conv = SIGNED_DECI;
	}
	else if (*bar == 'o' || *bar == 'O')
	{
		frmt->length = (*bar == 'O' ? MODIF_L : frmt->length);
		frmt->conv = UNSIGNED_OCTA;
	}
	else if (*bar == 'u' || *bar == 'U')
	{
		frmt->length = (*bar == 'U' ? MODIF_L : frmt->length);
		frmt->conv = UNSIGNED_DECI;
	}
	else if (*bar == 'x' || *bar == 'X')
		frmt->conv = (*bar == 'X' ? UNSIGNED_HEXA2 : UNSIGNED_HEXA);
	else if (*bar == 'e' || *bar == 'E')
		frmt->conv = (*bar == 'E' ? DOUBLE_EXP2 : DOUBLE_EXP);
	else if (*bar == 'f' || *bar == 'F')
		frmt->conv = (*bar == 'F' ? DOUBLE_NORMAL2 : DOUBLE_NORMAL);
	else if (*bar == 'c' || *bar == 'C')
	{
		frmt->length = (*bar == 'C' ? MODIF_L : frmt->length);
		frmt->conv = CHAR;
	}
	else if (*bar == 's' || *bar == 'S')
	{
		frmt->length = *bar == 'S' ? MODIF_L : frmt->length;
		frmt->conv = STRING;
	}
	else if (*bar == 'p')
		frmt->conv = POINTER;
	else if (*bar == '%')
		frmt->conv = PERCENTAGE;
	else
		return (0);
	*fmt = ++bar;
	return (1);
}
