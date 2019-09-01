#include "libft.h"
#include "ieeefp.h"

char	*ieee_ldtoa(long double ld, t_uint32 prec)
{
	(void)ld;
	(void)prec;
	return (NULL);
}

char	*ieee_ftoa(float f, t_uint32 prec)
{
	(void)f;
	(void)prec;
	return (NULL);
}

char	*ieee_dtoa(double d, t_uint32 prec, t_ieee_fmt style, t_int32 *exp)
{
	char		*buff;
	t_int32		exp2;
	t_ieeefp	fp;

	buff = ft_strnew(DRAGON4_BUFF_SIZE);
	fp.d.d = d;
	exp2 = dragon4(fp, IEEE_DOUBLE, buff, DRAGON4_BUFF_SIZE);
	ft_putendl("----");
	dragon4_prec(&buff, exp2, style, prec);
	if (exp)
		*exp = exp2;
	return (buff);
}
