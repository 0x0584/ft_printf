#include "format.h"
#include "utf8.h"

static bool		adjust_int_precision(t_frmt *frmt, char **astr, size_t *pad)
{
	char	tmp;
	t_s64	n_pad;

 	if (!astr || !frmt || !pad || !format_isnumeric(frmt))
		return (false);
	if (!ft_strcmp(*astr, "0") && frmt->has_radix && !frmt->prec)
	{
		ft_strchange(astr, ft_strdup(""));
		*pad += 1;
		return (true);
	}
	tmp = *astr[0];
	if (frmt->conv == CONV_INT && ft_strchr(" +-", tmp))
		ft_strreplace(astr, (char []){tmp, '\0'}, "");
	do_adjust_prefix(astr, frmt, true, false);
	if ((n_pad = frmt->prec - ft_strlen(*astr)) < 0)
		n_pad = 0;
	*pad -= (*pad > (size_t)n_pad) ? (size_t)n_pad : *pad;
	ft_strpad(astr, '0', (t_u32)n_pad, TOWARD_HEAD);
	if (ft_strchr("+ -", tmp))
		ft_strinsert_at(astr, (char []){tmp, '\0'}, 0);
	do_adjust_prefix(astr, frmt, false, true);
	return (true);
}

static bool		adjust_str_precision(t_frmt *frmt, char **astr, size_t *pad)
{
	char *tmp;
	size_t len;

	if (!astr || !frmt || !pad || frmt->conv != CONV_STR
			|| frmt->prec >= (len = (frmt->length == MOD_L
										? utf8_wstrlen(frmt->data.wstr)
											: ft_strlen(*astr))))
		return (false);
	if (frmt->has_radix)
	{
		if (!frmt->prec)
		{
			*pad += len;
			ft_strchange(astr, ft_strdup(""));
			return false;
		}
		if (frmt->length == MOD_L)
			tmp = ft_strrdup(*astr, utf8_moveto(frmt->data.wstr,
													*astr, frmt->prec) - 1);
		else
			tmp = ft_strrdup(*astr, *astr + frmt->prec - 1);
		*pad += (len - frmt->prec);
		ft_strchange(astr, tmp);
	}
	return (true);
}

void			adjust_precision(t_frmt *frmt, char **astr, size_t *pad)
{
	if (!adjust_int_precision(frmt, astr, pad))
		adjust_str_precision(frmt, astr, pad);
}

void			adjust_prefix(t_frmt *frmt, char **astr, size_t *pad)
{
	if (!frmt || !SAFE_PTRVAL(astr) || !pad)
		return ;
	if (flag_alterform(frmt, astr, pad))
		return ;
	if ((HAS_FLAG(frmt, FL_PLUS) || HAS_FLAG(frmt, FL_SPACE))
			&& (frmt->conv == CONV_INT || format_isfloat(frmt))
			&& format_getsign(frmt) != '-')
	{

		ft_strpad(astr, HAS_FLAG(frmt, FL_PLUS) ? '+' : ' ', 1,
				  TOWARD_HEAD);
		if (*pad)
			*pad -= 1;
	}
}

void			adjust_padding(t_frmt *frmt, char **astr, size_t *pad)
{
	if (!frmt || !SAFE_PTRVAL(astr) || !pad)
		return ;
	if (frmt->prec)
		frmt->flags &= ~FLAG(FL_ZERO);
	if (frmt->width && *pad)
	{
		if (HAS_FLAG(frmt, FL_MINUS))
			ft_strpad(astr, ' ', *pad, TOWARD_TAIL);
		else if (!HAS_FLAG(frmt, FL_ZERO))
			ft_strpad(astr, ' ', *pad, TOWARD_HEAD);
	}
	if (HAS_FLAG(frmt, FL_ZERO) && !HAS_FLAG(frmt, FL_MINUS)
			&& frmt->width && *pad
			&& !(format_isnumeric(frmt) && frmt->prec))
		flag_zero_padding(frmt, astr, pad);
}
