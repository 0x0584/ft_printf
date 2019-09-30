/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 22:20:34 by archid-           #+#    #+#             */
/*   Updated: 2019/09/30 02:44:32 by archid-          ###   ########.fr       */
/*                                                                            */
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

char			*format_handle_conversion(t_frmt *frmt)
{
	if (frmt->conv == CONV_INT)
		return (handle_signed_deci(frmt));
	else if (frmt->conv == CONV_UOCT)
		return (handle_unsigned_deci(frmt, BASE_OCT));
	else if (frmt->conv == CONV_UDEC)
		return (handle_unsigned_deci(frmt, BASE_DEC));
	else if (frmt->conv == CONV_UBIN)
		return (handle_unsigned_deci(frmt, BASE_BIN));
	else if (frmt->conv == CONV_UHEX || frmt->conv == CONV_PTR)
		return (handle_unsigned_deci(frmt, frmt->is_upcase
											? BASE_UHEX : BASE_LHEX));
	else if (format_isfloat(frmt))
		return (handle_floating_point(frmt));
	else if (frmt->conv == CONV_CHAR)
		return (handle_char(frmt));
	else if (frmt->conv == CONV_STR || frmt->conv == CONV_FRMT)
		return (handle_string(frmt));
	else if (frmt->conv == CONV_PERC)
		return (ft_strdup("%"));
	return (NULL);
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
	if (!check_conversion(fmt, &frmt))
		return ;
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
		get_wild_args(frmt, arglst);
		if (!get_signed_args(frmt, arglst))
			if (!get_unsigned_args(frmt, arglst))
				if (!get_floating_point_args(frmt, arglst))
					(void)get_string_args(frmt, arglst);
		while ((LST_NEXT(e)) && g_sort_lstfrmt && e->content
					&& ((t_frmt *)e->content)->iarg == frmt->iarg)
			((t_frmt *)e->content)->data = frmt->data;
	}
	if (g_sort_lstfrmt)
		ft_lst_mergesort(alstfrmt, cmp_by_frmtindex);
	return (g_sort_lstfrmt = true);
}
