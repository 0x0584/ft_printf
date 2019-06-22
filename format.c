/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 22:20:34 by archid-           #+#    #+#             */
/*   Updated: 2019/06/22 17:20:10 by archid-          ###   ########.fr       */
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
	if (*bar == 'd' || *bar == 'i') {
		frmt->conv = SIGNED_DECI;
	}
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
	t_list *e;
	void *tmp;
	bool flag;
	t_frmt *frmt;

	flag = false;
	while (!flag)
	{
		flag = true;
		e = lstfrmt;
		while (((t_frmt *)e->content)->argindex >
			   ((t_frmt *)e->next->content)->argindex)
		{
			tmp = e->content;
			e->content = e->next->content;
			e->next->content = tmp;
			flag = false;
		}
	}
	e = lstfrmt;
	/* while (e) */
	/* { */
	/* 	frmt = (t_frmt *)e->content; */
	/* 	if (frmt->conv == ) */
	/* 		frmt->u; */
	/* } */
	return (1);
}

void format_to_buff(t_list *lstfrmt, t_buff *buff)
{

}

/* static t_checker chkrs[] = { */
/* 	check_arg_index, */
/* 	check_flags, */
/* 	check_modifier, */
/* 	check_conversion, */

/* 	NULL */
/* }; */

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

	frmt.fmtindex = frmt_index++;
	frmt.argindex = hungry_getnbr(fmt);
    if (*fmt[0] != '$')
    {
        frmt.width = frmt.argindex;;
        frmt.argindex = -1;
    }
	else
		*fmt += 1;
	check_flags(fmt, &frmt);
	if (frmt.argindex != -1)
		frmt.width = hungry_getnbr(fmt);
	*fmt += (*fmt[0] == '.');
	if (*fmt[0] && *fmt[0] == '.')
		frmt.precision = hungry_getnbr(fmt);
	check_modifier(fmt, &frmt);
	check_conversion(fmt, &frmt);
	ft_lstpush(&lstfrmt, ft_lstnew(&frmt, sizeof(t_frmt)));
	if (!ft_strchr(*fmt, '%'))
	{
		handle_relative_args(arglst, lstfrmt);
		format_to_buff(lstfrmt, buff);
		ft_lstdel(&lstfrmt, NULL);
		frmt_index = 0;
	}
}
