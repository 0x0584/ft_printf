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

static bool sort_lstfrmt = true;

/* FIXME: free string as so */
void	format_free(void *dat, size_t size)
{
	if (size)
		free(dat);
}

t_frmt	*format_const_string(int index, char *str)
{
	static t_frmt frmt;

	ft_bzero(&frmt, sizeof(t_frmt));
	frmt.conv = STRING_FRMT;
	frmt.fmtindex = index;
	frmt.u_data.str = str;
	return (&frmt);
}

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

static int		cmp_by_argindex(t_plist e1, t_plist e2)
{
	t_frmt *foo;
	t_frmt *bar;

	foo = e1->content;
	bar = e2->content;
	return (foo->argindex < bar->argindex);
}

static int		cmp_by_frmtindex(t_plist e1, t_plist e2)
{
	t_frmt *foo;
	t_frmt *bar;

	foo = e1->content;
	bar = e2->content;
	return (foo->fmtindex < bar->fmtindex);
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
	check_flags(fmt, &frmt);
	frmt.argindex = hungry_getnbr(fmt);
	if (*fmt[0] != '$')
	{
		frmt.width = frmt.argindex;
		frmt.argindex = 0;
		sort_lstfrmt = false;
	}
	else
		*fmt += 1;
	if (frmt.argindex)
		frmt.width = hungry_getnbr(fmt);
	*fmt += (*fmt[0] == '.');
	frmt.precision = hungry_getnbr(fmt);
	check_modifier(fmt, &frmt);
	check_conversion(fmt, &frmt);
	ft_lstpush(alstfrmt, ft_lstnew(&frmt, sizeof(t_frmt)));
}

int				handle_relative_args(va_list *arglst, t_plist *alstfrmt)
{
	t_list	*e;
	t_frmt	*frmt;

	if (sort_lstfrmt)
		ft_lst_mergesort(alstfrmt, cmp_by_argindex);
	e = *alstfrmt;
	while (e && (frmt = (t_frmt *)e->content))
	{
		if (frmt->conv == STRING_FRMT)
		{
			LST_NEXT(e);
			continue;
		}
		if (frmt->conv == SIGNED_DECI || frmt->conv == CHAR)
		{
			if (frmt->length == MODIF_H)
				frmt->u_data.s = va_arg(*arglst, short);
			else if (frmt->length == MODIF_LL)
				frmt->u_data.ll = va_arg(*arglst, long long);
			else if (frmt->length == MODIF_L)
				frmt->u_data.l = va_arg(*arglst, long);
			else
				frmt->u_data.i = va_arg(*arglst, int);
		}
		else if (frmt->conv == UNSIGNED_OCTA ||
					frmt->conv == UNSIGNED_DECI ||
					frmt->conv == UNSIGNED_HEXA ||
					frmt->conv == UNSIGNED_HEXA2 ||
				 frmt->conv == POINTER)
		{
			if (frmt->length == MODIF_H)
				frmt->u_data.us = va_arg(*arglst, unsigned short);
			else if (frmt->length == MODIF_L || frmt->conv == POINTER)
				frmt->u_data.ul = va_arg(*arglst, unsigned long);
			else if (frmt->length == MODIF_LL)
				frmt->u_data.ull = va_arg(*arglst, unsigned long long);
			else
				frmt->u_data.ui = va_arg(*arglst, unsigned int);
		}
		else if (frmt->conv == DOUBLE_EXP ||
					frmt->conv == DOUBLE_EXP2 ||
					frmt->conv == DOUBLE_NORMAL ||
					frmt->conv == DOUBLE_NORMAL2)
		{
			if (frmt->length == MODIF_L)
				frmt->u_data.ld = va_arg(*arglst, long double);
			else
				frmt->u_data.d = va_arg(*arglst, double);
		}
		else if (frmt->conv == STRING)
		{
			if (frmt->length == MODIF_L)
				frmt->u_data.wstr = va_arg(*arglst, t_int32 *);
			else
				frmt->u_data.str = va_arg(*arglst, char *);
		}
		format_dbg(frmt);
		/* getchar(); */
		LST_NEXT(e);
	}
	ft_putendl("------ end of getting data -------");
	/* getchar(); */
	if (sort_lstfrmt)
		ft_lst_mergesort(alstfrmt, cmp_by_frmtindex);
	return (1);
}
