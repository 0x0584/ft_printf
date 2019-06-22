/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 22:20:34 by archid-           #+#    #+#             */
/*   Updated: 2019/06/22 15:03:58 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "format.h"

typedef int	(*t_checker)(char **, t_frmt *);


int		check_arg_index(char **fmt, t_frmt *frmt)
{
	char *bar;

	/* NOTE:
	 *
	 * this is a stupid solution, since I have to check is only digits follow
	 */

	UNLESS_RET(bar = ft_strchr(*fmt + 1, '$'), 0);
	if ((frmt->argindex = ft_atoi(*fmt + 1)))
	{
		frmt->argindex = -1;	/* fmtindex instead */
		return (0);
	}
	*fmt = bar;					/* FIXME: mempry leak,
								 *
								 * try to keep a point or something
								 */
	return (1);
}

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

int		check_min_width(char **fmt, t_frmt *frmt)
{
}

int		check_precision(char **fmt, t_frmt *frmt)
{
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
		return 1;
    }
	else
		return 0;
}

int		check_conversion(char **fmt, t_frmt *frmt)
{
	/* TODO: disable #-flag when %{c,d,i,n,p,s,u} */
}

int		handle_relative_args(va_list *arglst, t_list *lstfrmt)
{
	/*
	 * TODO: for $ flag, format must be a list
	 * ========================================
	 *
	 * you have to read all the format strings,
	 * and find the arg indexes, sort them
	 * based on those indexes, and then call
	 * va_arg() to fill the whole list.
	 * and finally re-sort them based on the
	 * order they were read in.
	 */
}

void format_to_buff(t_list *lstfrmt, t_buff *buff)
{

}

static t_checker chkrs[] = {
	check_arg_index,
	check_flags,
	check_min_width,
	check_precision,
	check_modifier,
	check_conversion,

	NULL
};

int		hungry_getnbr(char **str)
{
	char *bar;
	int foo;

	bar = *str;

	while (ft_isdigit(*bar))
    {
        foo = (foo << 3) + (foo << 1);
        foo += (*bar++ - '0');
    }
	*str = bar;
	return (foo);
}

void	handle_format(char **fmt, va_list *arglst, t_buff *buff)
{
	static t_list	*lstfrmt = NULL;
	static int		frmt_index = 0;
	t_frmt			frmt;

	/* int i; */

	/* i = 0; */
	/* while (chkrs[i]) */
	/* 	chkrs[i++](fmt, &frmt); */

	/* get argindex */
	frmt.argindex = hungry_getnbr(fmt);
    if (*fmt[0] != '$')
    {
        // this is not the arg argument
        frmt.width = frmt.argindex;;
        frmt.argindex = -1;
    }
	else
		*fmt += 1;

	/* get the flags */
	check_flags(fmt, &frmt);
	if (frmt.argindex != -1)
		frmt.width = hungry_getnbr(fmt);
	*fmt += (*fmt[0] == '.');
	if (*fmt[0] && *fmt[0] == '.')
		frmt.precision = hungry_getnbr(fmt);

	ft_lstpush(&lstfrmt, ft_lstnew(&frmt, sizeof(t_frmt)));
	if (!ft_strchr(*fmt, '%'))
	{
		handle_relative_args(arglst, lstfrmt);
		format_to_buff(lstfrmt, buff);
		ft_lstdel(&lstfrmt, NULL);
	}
}
