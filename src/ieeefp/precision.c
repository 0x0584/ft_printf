#include "libft.h"
#include "ieeefp.h"

static void		skip_leading_zeros(char **astr)
{
	size_t	i;
	char	*str;

	i = 0;
	str = *astr;
	while (str[i] && str[i] == '0')
		i++;
	if (str[i] && str[i] == '.')
		i--;
	if (!i)
		return ;
	str = ft_strdup(*astr + i);
	ft_strdel(astr);
	*astr = str;
}

static bool		has_trailing_zeros(char *buff, size_t index)
{
	while (buff[index])
		if (buff[index] != '0')
			return (false);
		else
			index++;
	return (true);
}

static void		round_nearest_even(char **fp_buff, t_ieee_fmt style,
										int *exp, int prec)
{
	char	*buff;
	size_t	i;
	bool	carry;

	buff = *fp_buff;
	i = MAX(style == IEEE_EXPONENT ? 0 : *exp, 0) + prec;
	if (!buff[i + 1] || buff[i + 1] < '5' || (buff[i + 1] == '5'
		&& IS_EVEN(buff[i] - '0') && has_trailing_zeros(buff, i + 2)))
		return ;
	carry = true;
	while (i && carry)
	{
		if ((buff[i] = (buff[i] == '9') ? '0' : buff[i] + 1) != '0')
			carry = false;
		i--;
	}
	if (i || !carry)
		return ;
	if (buff[i] == '9')
	{
		buff[i] = '1';
		buff[MAX((*exp)++, 0) + prec + 1] = '0';
	}
	else
		buff[i] += 1;
	ft_putstr(" round // "); ft_putendl(buff);
	getchar();
	ft_putstr(" round \\ "); ft_putendl(buff);
	getchar();

}

static void		prepare_fp_buff(char **buff, t_ieee_fmt style,
									t_s32 *exp, int prec)
{
	t_s32			npad;
	size_t			buff_size;

	ft_putstr(" buff !? "); ft_putendl(*buff);
	getchar();

	buff_size = ft_strlen(*buff) - 1;

	if (*exp < 0 && style == IEEE_NORMAL)
		ft_strpad(buff, '0', -*exp, TOWARD_HEAD);

	ft_putstr(" buff !? "); ft_putendl(*buff);
	getchar();

	if (*exp <= 0)
		npad = MAX(prec - buff_size, 0);
	else
	{

		/* getchar(); */
		npad = MAX(*exp - (t_s32)buff_size, 0) + prec
				- (*exp < (t_s32)buff_size ? 0 : ft_strlen(*buff + *exp + 1));
	}
	if (npad < 0)
		npad += buff_size;
	ft_putendl(*buff + *exp + 1);
	(void)printf(" to << %d %zu\n", npad, buff_size);
	(void)getchar();
	ft_strpad(buff, '0', ABS(npad), TOWARD_TAIL);

	ft_putstr(" buff !? "); ft_putendl(*buff);
	getchar();

	round_nearest_even(buff, style, exp, prec);
}

void	dragon4_prec(char **fp_buff, t_s32 *exp, t_ieee_fmt style,
						t_u32 prec)
{
	char	*fp;
	char	*tmp;
	char	*int_part;
	char	*frac_part;
	int		exp2;

	ft_putstr(" fp_buff ?? "); ft_putendl(*fp_buff);
	getchar();

	prepare_fp_buff(fp_buff, style, exp, prec);

	ft_putstr(" prepered fp_buff ?? "); ft_putendl(*fp_buff);
	getchar();

	int_part = *fp_buff;
	if (*int_part == '0' && style == IEEE_EXPONENT)
	{
		while (*int_part && *int_part == '0')
			int_part++;
		*exp *= -1;
		exp2 = 0;
	}
	else
		exp2 = MAX(style == IEEE_EXPONENT ? 0 : *exp, 0);
	fp = ft_strrdup(int_part, int_part + exp2);
	frac_part = prec ? int_part + exp2 : NULL;

	/* ft_putnumber(*exp); ft_putstr(" >>> "); ft_putendl(fp); */
	/* getchar(); */

	if (frac_part)
	{
		ft_strappend(&fp, ".");
		skip_leading_zeros(&fp);
		tmp = ft_strrdup(frac_part + 1, frac_part + prec);
		ft_strappend(&fp, tmp);
		ft_strdel(&tmp);
	}
	ft_strdel(fp_buff);
	*fp_buff = fp;
}
