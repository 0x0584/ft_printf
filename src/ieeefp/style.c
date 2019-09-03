#include "ieeefp.h"
#include "libft.h"

/* NOTE: remove sci exponent from precision before handling style */
void	ieee_sci_style(char **astr, t_s32 exp, bool upcase)
{
	char	*fp_sci;

	if (!SAFE_PTRVAL(astr))
	{
		ft_putendl_fd("ERROR! astr was NULL in ieee_sci_style", 2);
		return ;
	}

	fp_sci = ft_itoa_base(exp, BASE_DEC);
	/* ft_putstr(" fp_sci as exp ?? "); ft_putendl(fp_sci); */
	/* getchar(); */

	if (*fp_sci == '-' && ft_strlen(fp_sci) < 3)
		ft_strinsert_at(&fp_sci, "0", 1);
	else if (*fp_sci != '-')
		ft_strinsert_at(&fp_sci, ft_strlen(fp_sci) < 2 ? "+0" : "+", 0);

	/* ft_putstr(" fp_sci after append sign ?? "); ft_putendl(fp_sci); */
	/* getchar(); */

	ft_strinsert_at(&fp_sci, upcase ? "E" : "e", 0);
	ft_strinsert_at(&fp_sci, *astr, 0);

	ft_strdel(astr);
	*astr = ft_strdup(fp_sci);

	/* ft_putstr("\n\nHEREE "); ft_putnumber(exp); */
	/* ft_putstr(" !! "); ft_putendl(*astr); */
	/* getchar(); */
}

char	*ieee_hex_style(t_ieeefp fp, bool upcase)
{
	char *result;
	char *tmp;

}

void	ieee_suitable_style(char **astr, bool upcase)
{

}
