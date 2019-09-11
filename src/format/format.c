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

static bool		g_sort_lstfrmt = true;

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

void			format_doparse(char **fmt, t_list **alstfrmt, int *index)
{
	t_frmt			frmt;

	if (format_apply_color(fmt, alstfrmt, index))
		return ;
	ft_bzero(&frmt, sizeof(t_frmt));
	frmt.ifrmt = *index;
	set_arg_index(fmt, &frmt);
	if (frmt.iarg == 0)
		g_sort_lstfrmt = false;
	check_flags(fmt, &frmt);
	set_width(fmt, &frmt);
	set_precision(fmt, &frmt);
	check_modifier(fmt, &frmt);
	check_conversion(fmt, &frmt);
	ft_lstpush(alstfrmt, ft_lstnew(&frmt, sizeof(t_frmt)));
}

int				format_populate(t_plist *alstfrmt, va_list *arglst)
{
	t_list	*e;
	t_frmt	*frmt;

	if (g_sort_lstfrmt)
		ft_lst_mergesort(alstfrmt, cmp_by_argindex);
	e = *alstfrmt;
	while (e && (frmt = (t_frmt *)e->content))
	{
		if (frmt->conv == CONV_FRMT)
		{
			LST_NEXT(e);
			continue ;
		}
		if (frmt->width_as_arg)
			frmt->width = va_arg(*arglst, unsigned int);
		if (frmt->prec_as_arg)
			frmt->prec = va_arg(*arglst, unsigned int);
		if (!get_signed_args(frmt, arglst))
			if (!get_unsigned_args(frmt, arglst))
				if (!get_floating_point_args(frmt, arglst))
					(void)get_string_args(frmt, arglst);
		LST_NEXT(e);
		while (e && ((t_frmt *)e->content)->iarg == frmt->iarg)
		{
			((t_frmt *)e->content)->data = frmt->data;
			LST_NEXT(e);
		}
	}
	if (g_sort_lstfrmt)
		ft_lst_mergesort(alstfrmt, cmp_by_frmtindex);
	g_sort_lstfrmt = true;
	return (1);
}
