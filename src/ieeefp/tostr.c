#include "format.h"
#include "ieeefp.h"

char	*ieee_ldtoa(long double ld, t_u32 prec)
{
	(void)ld;
	(void)prec;
	return (NULL);
}

char	*ieee_ftoa(float f, t_u32 prec)
{
	(void)f;
	(void)prec;
	return (NULL);
}

/*
   NOTE: this should be ieee_tostr() instead
   BUG: forget to handle negative and g flag
*/

char	*ieee_dtoa(double d, t_u32 prec, t_ieee_fmt style, t_s32 *exp)
{
	char		*buff;
	t_s32		exp2;
	t_ieeefp	fp;

	buff = ft_strnew(DRAGON4_BUFF_SIZE);
	fp.d.d = d;
	exp2 = dragon4(fp, IEEE_DOUBLE, buff, DRAGON4_BUFF_SIZE);

	ft_putendl("----");

	if (style == IEEE_SUITABLE)
	{
		style = (exp2 < (t_s32)prec && exp2 >= -4)
					? IEEE_NORMAL : IEEE_EXPONENT;
		prec -= (1 + (style == IEEE_NORMAL) * exp2);
	}

	printf("%u", prec);
	getchar();

	dragon4_prec(&buff, &exp2, style, prec);
	if (d < .0)
		ft_strinsert_at(&buff, "-", 0);
	if (exp)
		*exp = exp2;
	return (buff);
}


/*
  NOTE: this does the job instead of dtoa and so..
  FIXME: remove all above functions
*/

char	*ieee_tostr(t_frmt *frmt, t_ieeefp fp)
{
	(void)fp;
	/* if (frmt->has_radix) */
	return (NULL);
}
