#include "format.h"

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
		if (*pad > 1)
			*pad -= 2;
		else if (*pad <= 1)
			*pad = 0;
	}
	else if (frmt->conv == CONV_UBIN)
	{
		ft_strprepend(astr, frmt->is_upcase ?  "0B" : "0b" );
		if (*pad > 1)
			*pad -= 2;
		else if (*pad <= 1)
			*pad = 0;
	}
	return (true);
}

void		flag_zero_padding(t_frmt *frmt, char **astr, size_t *pad)
{
	char tmp_sign;

	if (!frmt || !SAFE_PTRVAL(astr) || !pad)
		return ;
	if (HAS_FLAG(frmt, FL_ZERO) && !HAS_FLAG(frmt, FL_MINUS)
			&& frmt->width && *pad
			&& !(format_isnumeric(frmt) && frmt->prec))
	{
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
		{
			ft_strreplace(astr, frmt->is_upcase ? "0X" : "0x", "");
			ft_strinsert_at(astr, frmt->is_upcase ? "0X" : "0x", 0);
		}
		else if (frmt->conv == CONV_UBIN && HAS_FLAG(frmt, FL_HASH))
		{
			ft_strreplace(astr, frmt->is_upcase ? "0B" : "0b", "");
			ft_strinsert_at(astr, frmt->is_upcase ? "0B" : "0b", 0);
		}
	}
}
