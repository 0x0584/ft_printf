#include "format.h"

void	flag_getprefix_or_sign (t_frmt *frmt, char **astr, size_t *pad)
{
	if (!frmt || !SAFE_PTRVAL(astr) || !pad)
	{
		ft_putendl_fd("ERROR!!! PTR IN FLAG_GETPREFIX_OR_SIGN() IS NULL!", 2);
		return ;
	}
	/* XXX: plus overrides the space */
	if (!format_check_alterform(astr, frmt, pad))
		if (frmt->conv == CONV_INT && format_getsign(frmt) != '-'
			&& (HAS_FLAG(frmt, FL_PLUS) || HAS_FLAG(frmt, FL_SPACE)))
		{

			ft_strpad(astr, HAS_FLAG(frmt, FL_PLUS) ? '+' : ' ', 1,
					  TOWARD_HEAD);
			/* XXX: decrement size of padding when sign */
			if (*pad)
				*pad -= 1;
		}
}

void	flag_zero_padding(t_frmt *frmt, char **astr, size_t *pad)
{
	char tmp_sign;

	if (!frmt || !SAFE_PTRVAL(astr) || !pad)
	{
		ft_putendl_fd("ERROR!!! PTR IN FLAG_ZERO_PADDING() IS NULL!", 2);
		return ;
	}
	ft_putstr("inside flag_zero_padding() >>> ");
	ft_putstr(*astr);
	getchar();

	/* Zero padding */
	/* FIXME: ignore zero padding when precision */
	if (HAS_FLAG(frmt, FL_ZERO) && !HAS_FLAG(frmt, FL_MINUS)
			&& frmt->width && *pad
			&& !(format_isnumeric(frmt) && frmt->prec))
	{
		tmp_sign = *astr[0];
		ft_putstr(" ?? "); ft_putendl(*astr);

		ft_strpad(astr, '0', *pad, TOWARD_HEAD);

		ft_putstr(" !? "); ft_putendl(*astr);
		ft_putstr(" >");
		getchar();

		if (frmt->conv == CONV_INT)
		{
			if (tmp_sign == '+' && !HAS_FLAG(frmt, FL_PLUS)
				&& HAS_FLAG(frmt, FL_SPACE))
				tmp_sign = ' ';
			if (tmp_sign == '+' || tmp_sign == '-' || tmp_sign == ' ')
				ft_strreplace(astr, (char []){tmp_sign, '\0'}, "");
			if (tmp_sign == '+' || tmp_sign == '-' || tmp_sign == ' ')
				ft_strinsert_at(astr, (char []){tmp_sign, '\0'}, 0);
		}
		else if (frmt->conv == CONV_UHEX)
		{
			ft_strreplace(astr, frmt->is_upcase ? "0X" : "0x", "");
			ft_strinsert_at(astr, frmt->is_upcase ? "0X" : "0x", 0);
		}
		ft_putendl(*astr);
		getchar();
	}

}

void	flag_adjust_padding(t_frmt *frmt, char **astr, size_t *pad)
{
	if (!frmt || !SAFE_PTRVAL(astr) || !pad)
	{
		ft_putendl_fd("ERROR!!! PTR IN FLAG_ZERO_PADDING() IS NULL!", 2);
		return ;
	}

	/* Field width */
	if (frmt->width && *pad)
	{
		if (HAS_FLAG(frmt, FL_MINUS))
			ft_strpad(astr, ' ', *pad, TOWARD_TAIL);
		else if (!HAS_FLAG(frmt, FL_ZERO))
			ft_strpad(astr, ' ', *pad, TOWARD_HEAD);
	}

	/* Zero padding */
	if (!HAS_FLAG(frmt, FL_MINUS))
		flag_zero_padding(frmt, astr, pad);
}
