/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 format.c											:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <archid-@student.1337.ma>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/06/17 22:20:34 by archid-		   #+#	  #+#			  */
/*   Updated: 2019/08/06 14:17:44 by archid-          ###   ########.fr       */
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
	frmt.conv = CONV_FRMT;
	frmt.ifrmt = index;
	frmt.data.str = str;
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
	return (foo->iarg < bar->iarg);
}

static int		cmp_by_frmtindex(t_plist e1, t_plist e2)
{
	t_frmt *foo;
	t_frmt *bar;

	foo = e1->content;
	bar = e2->content;
	return (foo->ifrmt < bar->ifrmt);
}

void			format_handle(char **fmt, t_list **alstfrmt, int *index)
{
	t_frmt			frmt;

	ft_bzero(&frmt, sizeof(t_frmt));
	frmt.ifrmt = *index;
	*fmt += 1;
	check_flags(fmt, &frmt);
	frmt.iarg = hungry_getnbr(fmt);
	if (*fmt[0] == '$')
		*fmt += 1;
	else
	{
		frmt.width = frmt.iarg;
		frmt.iarg = 0;
		sort_lstfrmt = false;
	}
	if (frmt.iarg)
		frmt.width = hungry_getnbr(fmt);
	frmt.has_radix = (*fmt[0] == '.');
	*fmt += frmt.has_radix;
	frmt.prec = hungry_getnbr(fmt);
	check_modifier(fmt, &frmt);
	check_conversion(fmt, &frmt);
	ft_lstpush(alstfrmt, ft_lstnew(&frmt, sizeof(t_frmt)));
}

int				format_populate(t_plist *alstfrmt, va_list *arglst)
{
	t_list	*e;
	t_frmt	*frmt;

	if (sort_lstfrmt)
		ft_lst_mergesort(alstfrmt, cmp_by_argindex);
	e = *alstfrmt;
	while (e && (frmt = (t_frmt *)e->content))
	{
		if (frmt->conv == CONV_FRMT)
		{
			LST_NEXT(e);
			continue;
		}
		if (frmt->conv == CONV_INT || frmt->conv == CONV_CHAR)
		{
		    if (frmt->length == MOD_LL)
				frmt->data.ll = va_arg(*arglst, long long);
			else if (frmt->length == MOD_L)
				frmt->data.l = va_arg(*arglst, long);
			else
				frmt->data.i = va_arg(*arglst, int);
		}
		else if (frmt->conv == CONV_UOCT || frmt->conv == CONV_UDEC
					|| frmt->conv == CONV_UBIN || frmt->conv == CONV_UHEX
					|| frmt->conv == CONV_PTR)
		{
		    if (frmt->length == MOD_L || frmt->conv == CONV_PTR)
				frmt->data.ul = va_arg(*arglst, unsigned long);
			else if (frmt->length == MOD_LL)
				frmt->data.ull = va_arg(*arglst, unsigned long long);
			else
				frmt->data.ui = va_arg(*arglst, unsigned int);
		}
		else if (frmt->conv == CONV_DBL || frmt->conv == CONV_LDBL
					|| frmt->conv == CONV_GDBL || frmt->conv == CONV_EDBL
					|| frmt->conv == CONV_HDBL)
		{
			if (frmt->length == MOD_L_CAP)
				frmt->data.ld = va_arg(*arglst, long double);
			else
				frmt->data.d = va_arg(*arglst, double);
		}
		else if (frmt->conv == CONV_STR)
		{
			if (frmt->length == MOD_L)
				frmt->data.wstr = va_arg(*arglst, t_s32 *);
			else
				frmt->data.str = va_arg(*arglst, char *);
		}
		LST_NEXT(e);
	}
	if (sort_lstfrmt)
		ft_lst_mergesort(alstfrmt, cmp_by_frmtindex);
	sort_lstfrmt = true;
	return (1);
}
