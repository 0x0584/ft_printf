#include "format.h"


/*
	XXX:	this must be named adjust_base_prefix()
	BUG:	insertion and replace are not working in case of zero!
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	NOTE:	this must be rewritten!! it's ugly code!!
	NOTE:	altered the behavior of this function. now if replace
			and insert are both true, we only insert if we find it.
*/

bool	adjust_base_prefix(char **astr, t_frmt *frmt, bool replace, bool insert)
{
	char *prefix;
	bool status;

	status = false;
	if (!(SAFE_PTRVAL(astr)) || !frmt || !ft_strcmp(*astr, "0")
			|| !HAS_FLAG(frmt, FL_HASH))
		return status;
	prefix = NULL;
	if (frmt->conv == CONV_UHEX && HAS_FLAG(frmt, FL_HASH))
		prefix = frmt->is_upcase ? "0X" : "0x";
	else if (frmt->conv == CONV_UBIN && HAS_FLAG(frmt, FL_HASH))
		prefix = frmt->is_upcase ? "0B" : "0b";
	if (prefix)
	{
		if (replace && insert)
		{
			if ((status = (ft_strstr(*astr, prefix) != NULL)))
			{
				ft_strreplace(astr, prefix, "");
				ft_strinsert_at(astr, prefix, 0);
			}
		}
		else if (replace)
		{
			if ((status = (ft_strstr(*astr, prefix)) != NULL))
				ft_strreplace(astr, prefix, "");
		}
		else if ((status = insert))
			ft_strinsert_at(astr, prefix, 0);
	}
	return (status);
}

bool	flag_alterform(t_frmt *frmt, char **astr, size_t *pad)
{
	/* dbg_str("in alter", true); */
	if (!(SAFE_PTRVAL(astr)) || !frmt || !pad
			|| ((!HAS_FLAG(frmt, FL_HASH) || !(format_isnumeric(frmt)))
					&& frmt->conv != CONV_PTR))
		return (false);
	if (frmt->conv == CONV_UOCT && ft_strcmp(*astr, "0"))
	{
		ft_strprepend(astr, "0");
		if (*pad)
			*pad -= 1;
		dbg_str("in octa", true);
	}
	else if ((frmt->conv == CONV_UHEX && HAS_FLAG(frmt, FL_HASH)
				&& ft_strcmp(*astr, "0")) || frmt->conv == CONV_PTR)
	{
		ft_strprepend(astr, frmt->is_upcase ?  "0X" : "0x");
		if (*pad)
			*pad -= (*pad <= 1 ? 1 : 2);
		dbg_str("in hexa", true);
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

	/* dbg_str("in zero padding", true); */
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
	else if (((frmt->conv == CONV_UHEX || frmt->conv == CONV_UBIN)
				&& HAS_FLAG(frmt, FL_HASH)) || frmt->conv == CONV_PTR)
		// BUG: only insert when exists
		adjust_base_prefix(astr, frmt, true, true);
	else if (frmt->conv == CONV_UBIN && HAS_FLAG(frmt, FL_HASH))
		adjust_base_prefix(astr, frmt, true, true);
}
