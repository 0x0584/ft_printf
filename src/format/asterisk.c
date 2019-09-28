/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 18:13:24 by archid-           #+#    #+#             */
/*   Updated: 2019/09/28 19:08:50 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "format.h"

static int		hungry_getnbr(char **str)
{
	char	*bar;
	int		foo;

	bar = *str;
	foo = 0;
	while (ft_isdigit(*bar))
	{
		foo = (foo << 3) + (foo << 1);
		foo += (*bar++ - '0');
	}
	*str = bar;
	return (foo);
}

void			set_width(char **fmt, t_frmt *frmt)
{
	t_u16 i;

	if ((*fmt)[0] != '*')
	{
		frmt->width = hungry_getnbr(fmt);
		return ;
	}
	i = 0;
	frmt->width_as_arg = true;
	while ((*fmt)[i] && (*fmt)[i] == '*')
		i++;
	*fmt += i;
}

void			set_precision(char **fmt, t_frmt *frmt)
{
	t_u16 i;

	if ((frmt->has_radix = (*fmt[0] == '.')))
	{
		*fmt += 1;
		if ((*fmt)[0] != '*')
		{
			frmt->prec = hungry_getnbr(fmt);
			return ;
		}
		i = 0;
		frmt->prec_as_arg = true;
		while ((*fmt)[i] && (*fmt)[i] == '*')
			i++;
		*fmt += i;
	}
}

void			set_arg_index(char **fmt, t_frmt *frmt)
{
	char *tmp;

	tmp = *fmt;
	frmt->iarg = hungry_getnbr(fmt);
	if (*fmt[0] == '$')
		*fmt += 1;
	else
	{
		*fmt = tmp;
		frmt->iarg = 0;
	}
}

void			get_wild_args(t_frmt *frmt, va_list *alst)
{
	int tmp;

	if (!frmt || !alst)
		return ;
	if (frmt->width_as_arg)
	{
		if ((tmp = va_arg(*alst, int)) < 0)
			frmt->flags |= FLAG(FL_MINUS);
		frmt->width = ABS(tmp);
	}
	if (frmt->prec_as_arg)
	{
		if ((tmp = va_arg(*alst, int)) < 0)
		{
			frmt->prec = 0;
			frmt->has_radix = false;
		}
		else
			frmt->prec = tmp;
	}
}
