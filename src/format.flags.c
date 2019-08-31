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
				*pad -= 1;;
		}
}

void	flag_zero_padding(t_frmt *frmt, char **astr, size_t *pad)
{
	char tmp_sign;
	char *s_frmt;

	if (!frmt || !SAFE_PTRVAL(astr) || !pad)
	{
		ft_putendl_fd("ERROR!!! PTR IN FLAG_ZERO_PADDING() IS NULL!", 2);
		return ;
	}
	s_frmt = *astr;
	/* Zero padding */
	/* FIXME: ignore zero padding when precision */
	if (HAS_FLAG(frmt, FL_ZERO) && !HAS_FLAG(frmt, FL_MINUS)
			&& frmt->width && *pad
			&& !(format_isnumeric(frmt) && frmt->prec))
	{
		tmp_sign = *s_frmt;
		ft_putstr(" ?? "); ft_putendl(s_frmt);

		ft_strpad(&s_frmt, '0', *pad, TOWARD_HEAD);

		ft_putstr(" >");
		getchar();

		if (tmp_sign == '+' && !HAS_FLAG(frmt, FL_PLUS)
			&& HAS_FLAG(frmt, FL_SPACE))
			tmp_sign = ' ';
		if (tmp_sign == '+' || tmp_sign == '-' || tmp_sign == ' ')
			ft_strreplace(&s_frmt, (char []){tmp_sign, '\0'}, "");
		if (tmp_sign == '+' || tmp_sign == '-' || tmp_sign == ' ')
			ft_strinsert_at(&s_frmt, (char []){tmp_sign, '\0'}, 0);

		ft_putendl(s_frmt);
		getchar();
	}

}
