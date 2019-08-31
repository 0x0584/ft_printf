#include "libft.h"
#include "bigint.h"
#include "ieeefp.h"

char	*ft_ldtoa(long double ld, t_uint32 pre)
{
	(void)ld;
	(void)pre;
	return (NULL);
}

char	*ft_ftoa(float f, t_uint32 pre)
{
	(void)f;
	(void)pre;
	return (NULL);
}

/*
   BUG: when precision is zero some weird output shows up

   format %f arg 0.00899
   mine:	(0000)
   glibc:	(0.008990)
 */
char	*ft_dtoa(double d, t_uint32 pre)
{
	char		*buff;
	/* char		*tmp; */
	t_int32		exp;
	t_ieeefp	fp;

	printf(" double in %f\n", d);
	buff = ft_strnew(DRAGON4_BUFF_SIZE);
	fp.d.d = d;
	exp = dragon4(fp, IEEE_DOUBLE, buff, DRAGON4_BUFF_SIZE);
	ft_putendl("----");
	handle_precision(&buff, IEEE_NORMAL, exp, pre);

	ft_putendl(buff);
	getchar();
	return (buff);
}
