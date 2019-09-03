#include "format.h"

static bool	check_alterform(char **astr, t_frmt *frmt, size_t *pad)
{
	if (!(SAFE_PTRVAL(astr)) || !HAS_FLAG(frmt, FL_HASH)
			|| !format_isnumeric(frmt))
		return (false);

	if (frmt->conv == CONV_UOCT && ft_strcmp(*astr, "0"))
	{
		ft_strprepend(astr, "0");
		if (*pad)
			*pad -= 1;
	}
	else if (frmt->conv == CONV_UHEX)
	{
		ft_strprepend(astr, frmt->is_upcase ?  "0X" : "0x" );
		if (*pad)
			*pad -= 2;
	}
/*
  call buffutils_pad(dest, "0", 1) for %o
  call buffutils_pad(dest, "0x", 2) for %x
  call buffutils_pad(dest, "0X", 1) for %X

  if format_isfloat(frmt)
  dest = ft_format_ieee_float(frmt, trailing_is_on) // default off
*/

	return (true);
}

void		flag_getprefix_or_sign (t_frmt *frmt, char **astr, size_t *pad)
{
	if (!frmt || !SAFE_PTRVAL(astr) || !pad)
		return ;
	/* XXX: plus overrides the space */
	if (!check_alterform(astr, frmt, pad))
		if ((HAS_FLAG(frmt, FL_PLUS) || HAS_FLAG(frmt, FL_SPACE))
			&& (frmt->conv == CONV_INT || format_isfloat(frmt))
			&& format_getsign(frmt) != '-')
		{

			ft_strpad(astr, HAS_FLAG(frmt, FL_PLUS) ? '+' : ' ', 1,
					  TOWARD_HEAD);
			/* XXX: decrement size of padding when sign */
			if (*pad)
				*pad -= 1;
		}
}

void		flag_zero_padding(t_frmt *frmt, char **astr, size_t *pad)
{
	char tmp_sign;

	if (!frmt || !SAFE_PTRVAL(astr) || !pad)
		return ;

	/* ft_putstr("inside flag_zero_padding() >>> "); */
	/* ft_putstr(*astr); */
	/* getchar(); */

	/* Zero padding */
	/* FIXME: ignore zero padding when precision */
	if (HAS_FLAG(frmt, FL_ZERO) && !HAS_FLAG(frmt, FL_MINUS)
			&& frmt->width && *pad
			&& !(format_isnumeric(frmt) && frmt->prec))
	{
		tmp_sign = *astr[0];
		/* ft_putstr(" ?? "); ft_putendl(*astr); */

		ft_strpad(astr, '0', *pad, TOWARD_HEAD);

		/* ft_putstr(" !? "); ft_putendl(*astr); */
		/* ft_putstr(" >"); */
		/* getchar(); */

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
		/* ft_putendl(*astr); */
		/* getchar(); */
	}

}

void		flag_adjust_padding(t_frmt *frmt, char **astr, size_t *pad)
{
	if (!frmt || !SAFE_PTRVAL(astr) || !pad)
		return ;

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