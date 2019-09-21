#include "format.h"

/* FIXME: this must be named adjust_base_prefix() */
void	do_adjust_prefix(char **astr, t_frmt *frmt, bool replace, bool insert)
{
	char *prefix;

	if (!(SAFE_PTRVAL(astr)) || !frmt || !ft_strcmp(*astr, "0"))
		return ;
	prefix = NULL;
	if (frmt->conv == CONV_UHEX && HAS_FLAG(frmt, FL_HASH))
		prefix = frmt->is_upcase ? "0X" : "0x";
	else if (frmt->conv == CONV_UBIN && HAS_FLAG(frmt, FL_HASH))
		prefix = frmt->is_upcase ? "0B" : "0b";
	if (prefix)
	{
		if (replace)
			ft_strreplace(astr, prefix, "");
		if (insert)
			ft_strinsert_at(astr, prefix, 0);
	}
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
		ft_strprepend(astr, frmt->is_upcase ?  "0X" : "0x");
		if (*pad)
			*pad -= (*pad <= 1 ? 1 : 2);
	}
	else if (frmt->conv == CONV_UBIN && HAS_FLAG(frmt, FL_HASH))
	{
		ft_strprepend(astr, frmt->is_upcase ?  "0B" : "0b" );
		if (*pad)
			*pad -= (*pad <= 1 ? 1 : 2);
	}
	return (true);
}

void		flag_zero_padding(t_frmt *frmt, char **astr, size_t *pad)
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
			ft_strreplace(astr, (char []){tmp_sign, '\0'}, "");
		if (tmp_sign == '+' || tmp_sign == '-' || tmp_sign == ' ')
			ft_strinsert_at(astr, (char []){tmp_sign, '\0'}, 0);
	}
	else if ((frmt->conv == CONV_UHEX && HAS_FLAG(frmt, FL_HASH))
				|| frmt->conv == CONV_PTR)
		do_adjust_prefix(astr, frmt, true, true);
	else if (frmt->conv == CONV_UBIN && HAS_FLAG(frmt, FL_HASH))
		do_adjust_prefix(astr, frmt, true, true);
}
