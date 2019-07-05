/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 format.c											:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <archid-@student.1337.ma>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/06/17 22:20:34 by archid-		   #+#	  #+#			  */
/*	 Updated: 2019/06/26 20:43:21 by archid-		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "format.h"

static int		hungry_getnbr(char **str)
{
	char *bar;
	int foo;

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

void			handle_format(char **fmt, t_list **alstfrmt, int *index)
{
	t_frmt			frmt;

	ft_bzero(&frmt, sizeof(t_frmt));
	frmt.fmtindex = *index;
	ft_putendl("begin handle format");
	ft_putendl(*fmt);

	/* getchar(); */
	*fmt += 1;
	frmt.argindex = hungry_getnbr(fmt);
	if (*fmt[0] != '$')
	{
		frmt.width = frmt.argindex;
		frmt.argindex = -1;
	}
	else
		*fmt += 1;
	check_flags(fmt, &frmt);
	if (frmt.argindex != -1)
		frmt.width = hungry_getnbr(fmt);
	*fmt += (*fmt[0] == '.');
	frmt.precision = hungry_getnbr(fmt);
	check_modifier(fmt, &frmt);
	check_conversion(fmt, &frmt);
	ft_lstpush(alstfrmt, ft_lstnew(&frmt, sizeof(t_frmt)));
}

int				handle_relative_args(va_list *arglst, t_list *lstfrmt)
{
	/* FIXME: implement a `lstsort' kind of function to sort `lstfrmt'
	 * based on which frmt->x_index to use: either arg_index or fmt_index */
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

	/* ft_putendl("----- ((())) ----------"); */
	e = lstfrmt;
	/* fill lstfrmt */
	while (e)
	{
		/* (void)printf("#############\n"); */
		frmt = (t_frmt *)e->content;
		if (frmt->conv == SIGNED_DECI || frmt->conv == CHAR)
		{
			if (frmt->length == MODIF_L)
				frmt->u_data.l = va_arg(*arglst, long);
			else if (frmt->length == MODIF_LL)
				frmt->u_data.ll = va_arg(*arglst, long long);
			else
				frmt->u_data.i = va_arg(*arglst, int);
		}
		else if (frmt->conv == UNSIGNED_OCTA ||
					frmt->conv == UNSIGNED_DECI ||
					frmt->conv == UNSIGNED_HEXA ||
					frmt->conv == UNSIGNED_HEXA2 ||
				 frmt->conv == POINTER) {
			if (frmt->length == MODIF_L || frmt->conv == POINTER)
				frmt->u_data.ul = va_arg(*arglst, unsigned long);
			else if (frmt->length == MODIF_LL)
				frmt->u_data.ull = va_arg(*arglst, unsigned long long);
			else
				frmt->u_data.ui = va_arg(*arglst, unsigned int);
		}
		else if (frmt->conv == DOUBLE_EXP ||
					frmt->conv == DOUBLE_EXP2 ||
					frmt->conv == DOUBLE_NORMAL ||
					frmt->conv == DOUBLE_NORMAL2) {
			if (frmt->length == MODIF_L)
				frmt->u_data.ld = va_arg(*arglst, long double);
			else
				frmt->u_data.d = va_arg(*arglst, double);
		}
		else if (frmt->conv == STRING)
			frmt->u_data.str = va_arg(*arglst, char *);
		e = e->next;
	}

	flag = false;
	while (!flag)
	{
		flag = true;
		e = lstfrmt;
		while (((t_frmt *)e->content)->fmtindex >
			   ((t_frmt *)e->next->content)->fmtindex)
		{
			tmp = e->content;
			e->content = e->next->content;
			e->next->content = tmp;
			flag = false;
		}
	}

	return (1);
}
