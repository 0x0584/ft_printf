#include "format.h"

/* NOTE: adjust pricision after flag zero */
static bool		adjust_int_precision(t_frmt *frmt, char **astr, size_t *pad)
{
	char tmp;
	t_s64 n_pad;

    /* check input */
	if (!astr || !frmt || !pad || !format_isnumeric(frmt))
		return false;

	ft_putstr(" !? >> "); ft_putendl(*astr);
	getchar();

	if (frmt->conv == CONV_INT && ft_strchr(" +-", tmp = *astr[0]))
		ft_strreplace(astr, (char []){tmp, '\0'}, "");
	if (frmt->conv == CONV_UHEX && HAS_FLAG(frmt, FL_HASH))
		ft_strreplace(astr, frmt->is_upcase ? "0X" : "0x", "");

	if ((n_pad = frmt->prec - ft_strlen(*astr)) < 0)
		n_pad = 0;

	ft_putstr(" !??! "); ft_putnumber(n_pad);
	getchar();

	/* FIXME: code redundancy here */
	if ((t_s64)*pad > n_pad)
		*pad -= n_pad;
	else
		*pad = 0;

	if (n_pad)
		ft_strpad(astr, '0', (t_u32)n_pad, TOWARD_HEAD);

	ft_putstr(" in !! >> "); ft_putendl(*astr);
	getchar();

	if (ft_strchr("+ -", tmp))
		ft_strinsert_at(astr, (char []){tmp, '\0'}, 0);
	if (frmt->conv == CONV_UHEX && HAS_FLAG(frmt, FL_HASH))
	{
		ft_strinsert_at(astr, frmt->is_upcase ? "0X" : "0x", 0);
		ft_putstr(" fool "); ft_putendl(*astr);
		getchar();
	}


	ft_putstr(" in 3 >> "); ft_putendl(*astr);
	getchar();
	return true;
}

static bool		adjust_str_precision(t_frmt *frmt, char **astr, size_t *pad)
{
	char *tmp;

    /* check input */
	if (!astr || !frmt || !pad || frmt->conv != CONV_STR
			|| ft_strlen(*astr) <= frmt->prec)
		return false;

	if (!frmt->prec)
	{
		*pad += ft_strlen(*astr);
		ft_strchange(astr, ft_strdup(""));
		return false;
	}
	tmp = ft_strrdup(*astr, *astr + frmt->prec - 1);
	*pad += (ft_strlen(*astr) - ft_strlen(tmp));
	ft_strchange(astr, tmp);

	ft_putendl("here"); ft_putstr(*astr);
	getchar();
	return (true);
}

void		adjust_precision(t_frmt *frmt, char **astr, size_t *pad)
{
	if (!adjust_int_precision(frmt, astr, pad))
		adjust_str_precision(frmt, astr, pad);
}

void		adjust_prefix(t_frmt *frmt, char **astr, size_t *pad)
{
	if (!frmt || !SAFE_PTRVAL(astr) || !pad)
		return ;

	ft_putstr("inside flag_prefix() >>>[");
	ft_putstr(*astr); 	ft_putstr("]");
	getchar();

	/* XXX: plus overrides the space */
	if (flag_alterform(frmt, astr, pad))
		return ;
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
	ft_putstr("outside flag_prefix() >>>[");
	ft_putstr(*astr); 	ft_putstr("]");
	getchar();

}

void		adjust_padding(t_frmt *frmt, char **astr, size_t *pad)
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
