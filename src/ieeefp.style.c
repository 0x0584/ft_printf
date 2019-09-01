#include "ieeefp.h"
#include "libft.h"

/* NOTE: remove sci exponent from precision before handling style */
void	ieee_sci_style(char **astr)
{
	char	*fp_sci;
	size_t	idigi;
	t_int32 exp;

	if (!SAFE_PTRVAL(astr))
	{
		ft_putendl_fd("ERROR! astr was NULL in ieee_sci_style", 2);
		return ;
	}

	idigi = 0;
	fp_sci = NULL;
	if (!(exp = ft_strichr(*astr, '.') - 1))
		while ((*astr)[idigi + 2] == '0')
			idigi++;
	if (!exp && (*astr)[idigi + 2])
		exp = -(idigi + (*astr)[0] == '0');
	fp_sci = ft_itoa_base(exp, BASE_DEC);
	if (exp > -10 && exp < 0)
		ft_strinsert_at(&fp_sci, "0", 1);
	else if (exp > 0)
		ft_strinsert_at(&fp_sci, exp < 10 ? "+0" : "+", 0);
	ft_strinsert_at(&fp_sci, "e", 0);
	ft_strinsert_at(&fp_sci, *astr, 0);
	ft_strreplace(&fp_sci, ".", "");
	ft_strctrim(&fp_sci, '0', TOWARD_HEAD);
	ft_strinsert_at(&fp_sci, ".", 1);
	ft_strdel(astr);
	*astr = ft_strdup(fp_sci);
	ft_putstr("\n\nHEREE "); ft_putnumber(exp); ft_putstr(" !! "); ft_putendl(*astr); getchar();
}

char	*ieee_hex_style(t_ieeefp fp)
{
	char *result;
	char *tmp;


}

void	ieee_suitable_style(char **astr)
{

}
