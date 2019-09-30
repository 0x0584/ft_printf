/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:59:08 by archid-           #+#    #+#             */
/*   Updated: 2019/09/30 02:43:38 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "format.h"

#define IS_HASH(f)			HAS_FLAG(f, FL_HASH)
#define IS_HEX(f, c)		((c == CONV_UHEX && IS_HASH(f)) || c == CONV_PTR)
#define IS_BIN(f, c)		(c == CONV_UBIN && IS_HASH(f))

bool	helper_do_replace_insert(char **astr, char *prefix, bool foo, bool bar)
{
	bool status;
	bool replaceable;

	replaceable = (ft_strstr(*astr, prefix) != NULL);
	if (foo && bar)
	{
		if ((status = replaceable))
		{
			ft_strreplace(astr, prefix, "");
			ft_strinsert_at(astr, prefix, 0);
		}
	}
	else if (foo)
	{
		if ((status = replaceable))
			ft_strreplace(astr, prefix, "");
	}
	else if ((status = bar))
		ft_strinsert_at(astr, prefix, 0);
	return (status);
}

bool	adjust_base_prefix(char **astr, t_frmt *frmt, bool replace, bool insert)
{
	char	*prefix;
	bool	status;

	status = false;
	if (!(SAFE_PTRVAL(astr)) || !frmt || (!HAS_FLAG(frmt, FL_HASH)
											&& frmt->conv != CONV_PTR))
		return (status);
	prefix = NULL;
	if (IS_HEX(frmt, frmt->conv))
		prefix = frmt->is_upcase ? "0X" : "0x";
	else if (frmt->conv == CONV_UBIN && HAS_FLAG(frmt, FL_HASH))
		prefix = frmt->is_upcase ? "0B" : "0b";
	if (!prefix)
		return (status);
	return (helper_do_replace_insert(astr, prefix, replace, insert));
}

bool	flag_alterform(t_frmt *frmt, char **astr, size_t *pad)
{
	if (!(SAFE_PTRVAL(astr)) || !frmt || !pad
			|| ((!HAS_FLAG(frmt, FL_HASH) || !(format_isnumeric(frmt)))
					&& frmt->conv != CONV_PTR))
		return (false);
	if (frmt->conv == CONV_UOCT && ft_strcmp(*astr, "0"))
	{
		ft_strprepend(astr, "0");
		if (*pad)
			*pad -= 1;
	}
	else if ((frmt->conv == CONV_UHEX && HAS_FLAG(frmt, FL_HASH)
				&& ft_strcmp(*astr, "0")) || frmt->conv == CONV_PTR)
	{
		ft_strprepend(astr, frmt->is_upcase ? "0X" : "0x");
		if (*pad)
			*pad -= (*pad <= 1 ? 1 : 2);
	}
	else if (frmt->conv == CONV_UBIN && HAS_FLAG(frmt, FL_HASH))
	{
		ft_strprepend(astr, frmt->is_upcase ? "0B" : "0b");
		if (*pad)
			*pad -= (*pad <= 1 ? 1 : 2);
	}
	return (true);
}

void	flag_zero_padding(t_frmt *frmt, char **astr, size_t *pad)
{
	char tmp_sign;

	if (!frmt || !SAFE_PTRVAL(astr) || !pad)
		return ;
	tmp_sign = *astr[0];
	ft_strpad(astr, '0', *pad, TOWARD_HEAD);
	if (frmt->conv == CONV_INT || format_isfloat(frmt))
	{
		if (tmp_sign == '+' && !HAS_FLAG(frmt, FL_PLUS)
				&& HAS_FLAG(frmt, FL_SPACE))
			tmp_sign = ' ';
		if (tmp_sign == '+' || tmp_sign == '-' || tmp_sign == ' ')
			ft_strreplace(astr, (char[]){tmp_sign, '\0'}, "");
		if (tmp_sign == '+' || tmp_sign == '-' || tmp_sign == ' ')
			ft_strinsert_at(astr, (char[]){tmp_sign, '\0'}, 0);
	}
	else if (((frmt->conv == CONV_UHEX || frmt->conv == CONV_UBIN)
				&& HAS_FLAG(frmt, FL_HASH)) || frmt->conv == CONV_PTR)
		adjust_base_prefix(astr, frmt, true, true);
	else if (frmt->conv == CONV_UBIN && HAS_FLAG(frmt, FL_HASH))
		adjust_base_prefix(astr, frmt, true, true);
}
