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

char	*ieee_dtoa(double d, t_uint32 prec)
{
	char		*buff;
	t_int32		exp;
	t_ieeefp	fp;

	buff = ft_strnew(DRAGON4_BUFF_SIZE);
	fp.d.d = d;
	exp = dragon4(fp, IEEE_DOUBLE, buff, DRAGON4_BUFF_SIZE);
	ft_putendl("----");
	handle_precision(&buff, IEEE_NORMAL, exp, 6);
	return (buff);
}
