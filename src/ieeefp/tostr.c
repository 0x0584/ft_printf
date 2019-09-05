#include "format.h"
#include "ieeefp.h"
#include "dragon4.h"

/*
   XXX: this should be ieee_tostr() instead
   XXX: forget to handle negative and g flag
*/

/* char	*ieee_dtoa(double d, t_u32 prec, t_ieee_fmt style, t_s32 *exp) */
/* { */
/* 	char		*buff; */
/* 	t_s32		exp2; */
/* 	t_ieeefp	fp; */

/* 	fp.as.d.d = d; */
/* 	exp2 = dragon4(fp, &buff); */

/* 	ft_putendl("----"); */

/* 	if (style == IEEE_SUITABLE) */
/* 	{ */
/* 		style = (exp2 < (t_s32)prec && exp2 >= -4) */
/* 					? IEEE_NORMAL : IEEE_EXPONENT; */
/* 		prec -= (1 + (style == IEEE_NORMAL) * exp2); */
/* 	} */

/* 	printf("%u", prec); */
/* 	getchar(); */

/* 	dragon4_prec(&buff, &exp2, style, prec); */
/* 	if (d < .0) */
/* 		ft_strinsert_at(&buff, "-", 0); */
/* 	if (exp) */
/* 		*exp = exp2; */
/* 	return (buff); */
/* } */


/*
  NOTE: this does the job instead of dtoa and so..
  FIXME: remove all above functions
*/

char	*ieee_tostr(t_ieeefp *fp, t_ieee_fmt style, t_frmt *frmt)
{
	char		*buff;
	t_s32		exp2;

	exp2 = dragon4(fp, &buff);

	ft_putendl("----");

	if (style == IEEE_SUITABLE)
	{
		style = (exp2 < (t_s32)frmt->prec && exp2 >= -4)
					? IEEE_NORMAL : IEEE_EXPONENT;
		frmt->prec -= (1 + (style == IEEE_NORMAL) * exp2);
	}

	printf("%u", frmt->prec);
	getchar();

	dragon4_prec(&buff, &exp2, style, frmt->prec);
	if (ieee_get_sign(fp))
		ft_strinsert_at(&buff, "-", 0);

	if (HAS_FLAG(frmt, FL_HASH) && !ft_strchr(buff, '.'))
		/* TODO: trim zeros */
		ft_strappend(&buff, ".");

if (frmt->conv == CONV_EDBL)
		ieee_sci_style(&buff, exp2, frmt->is_upcase);

	return (buff);
}
