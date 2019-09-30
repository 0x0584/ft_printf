/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 15:40:49 by archid-           #+#    #+#             */
/*   Updated: 2019/09/28 23:13:14 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "format.h"
#include "utf8.h"

#define GOOD			(SAFE_PTRVAL(astr) && frmt && pad)

static bool		adjust_int_precision(t_frmt *frmt, char **astr, size_t *pad)
{
	char	tmp_c;
	t_s64	n_pad;
	bool	has_base_prefix;

	if (!GOOD || (!format_isnumeric(frmt) && frmt->conv != CONV_PTR))
		return (false);
	has_base_prefix = adjust_base_prefix(astr, frmt, true, false);
	tmp_c = (*astr)[0];
	if (!ft_strcmp(*astr + (IS_PREFIX_SIGN(tmp_c)), "0") && frmt->has_radix &&
		!frmt->prec && !(HAS_FLAG(frmt, FL_HASH) && frmt->conv == CONV_UOCT))
	{
		ft_strchange(astr, ft_strdup(tmp_c == '0' ? ""
										: (char[]){tmp_c, '\0'}));
		*pad += 1;
	}
	if (frmt->conv == CONV_INT && IS_PREFIX_SIGN(tmp_c))
		ft_strreplace(astr, (char[]){tmp_c, '\0'}, "");
	if ((n_pad = frmt->prec - ft_strlen(*astr)) < 0)
		n_pad = 0;
	*pad -= (*pad > (size_t)n_pad ? (size_t)n_pad : *pad);
	ft_strpad(astr, '0', (t_u32)n_pad, TOWARD_HEAD);
	if (IS_PREFIX_SIGN(tmp_c))
		ft_strinsert_at(astr, (char[]){tmp_c, '\0'}, 0);
	adjust_base_prefix(astr, frmt, false, has_base_prefix);
	return (true);
}

static bool		adjust_str_precision(t_frmt *frmt, char **astr, size_t *pad)
{
	char	*tmp;
	size_t	len;

	if (!GOOD || frmt->conv != CONV_STR || !frmt->has_radix
				|| frmt->prec >= (len = (frmt->length == MOD_L
									? utf8_wstrlen(frmt->data.wstr)
										: ft_strlen(*astr))))
		return (false);
	if (!frmt->prec)
	{
		*pad = frmt->width;
		ft_strchange(astr, ft_strdup(""));
		return (true);
	}
	if (frmt->length == MOD_L)
		tmp = ft_strrdup(*astr, utf8_moveto(frmt->data.wstr,
											*astr, frmt->prec) - 1);
	else
		tmp = ft_strrdup(*astr, *astr + frmt->prec - 1);
	*pad = (frmt->prec < frmt->width
			? (frmt->width - frmt->prec) : 0);
	ft_strchange(astr, tmp);
	return (true);
}

void			adjust_prefix(t_frmt *frmt, char **astr, size_t *pad)
{
	if (!GOOD || flag_alterform(frmt, astr, pad))
		return ;
	if ((HAS_FLAG(frmt, FL_PLUS) || HAS_FLAG(frmt, FL_SPACE))
			&& (frmt->conv == CONV_INT || format_isfloat(frmt)))
	{
		if (format_getsign(frmt) != '-')
			ft_strpad(astr, HAS_FLAG(frmt, FL_PLUS) ? '+' : ' ', 1,
						TOWARD_HEAD);
		*pad -= (*pad ? ft_strchr("+ ", (*astr)[0]) != NULL : 0);
	}
}

void			adjust_padding(t_frmt *frmt, char **astr, size_t *pad)
{
	if (!GOOD)
		return ;
	if (frmt->has_radix && !format_isfloat(frmt))
		frmt->flags &= ~FLAG(FL_ZERO);
	if (frmt->width && *pad)
	{
		if (HAS_FLAG(frmt, FL_MINUS))
		{
			ft_strpad(astr, ' ', *pad, TOWARD_TAIL);
			if (frmt->is_nulchr)
				ft_strpad(astr, '\0', 1, TOWARD_HEAD);
		}
		else if (!HAS_FLAG(frmt, FL_ZERO))
		{
			ft_strpad(astr, ' ', *pad, TOWARD_HEAD);
			if (frmt->is_nulchr)
				ft_strpad(astr, '\0', 1, TOWARD_TAIL);
		}
	}
	if (HAS_FLAG(frmt, FL_ZERO) && !HAS_FLAG(frmt, FL_MINUS)
			&& frmt->width && *pad)
		flag_zero_padding(frmt, astr, pad);
}

void			adjustments(t_frmt *frmt, char **astr, size_t *pad)
{
	adjust_prefix(frmt, astr, pad);
	if (!adjust_int_precision(frmt, astr, pad))
		adjust_str_precision(frmt, astr, pad);
	adjust_padding(frmt, astr, pad);
}

#undef GOOD
