#include "format.h"
#include "ieeefp.h"
#include "dragon4.h"

char	*ieee_tostr(t_ieeefp *fp, t_ieee_fmt style, t_frmt *frmt)
{
	char		*buff;
	t_s32		exp2;

	exp2 = dragon4(fp, &buff);
	if (style == IEEE_SUITABLE)
	{
		style = (exp2 < (t_s32)frmt->prec && exp2 >= -4)
					? IEEE_NORMAL : IEEE_EXPONENT;
		frmt->prec -= (1 + (style == IEEE_NORMAL) * exp2);
	}
	dragon4_prec(&buff, &exp2, style, frmt->prec);
	if (ieee_get_sign(fp))
		ft_strinsert_at(&buff, "-", 0);
	if (HAS_FLAG(frmt, FL_HASH) && !ft_strchr(buff, '.'))
		ft_strappend(&buff, ".");
	if (frmt->conv == CONV_EDBL)
		ieee_sci_style(&buff, exp2, frmt->is_upcase);
	return (buff);
}
