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
										int *exp, int preci)
{
	char			*buff;
	size_t			i;
	t_uint32		carry;

	buff = *fp_buff;
	i = MAX(style == IEEE_EXPONENT ? 0 : *exp, 0) + preci;
	if (!buff[i + 1] || buff[i + 1] < '5' || (buff[i + 1] == '5'
		&& IS_EVEN(buff[i] - '0') && has_trailing_zeros(buff, i + 2)))
		return ;
	carry = 1U;
	while (i && carry)
	{
		if ((buff[i] = (buff[i] == '9') ? '0' : buff[i] + 1) != '0')
			carry = 0U;
		i--;
	}
	if (i || !carry)
		return ;
	if (buff[i] == '9')
	{
		buff[i] = '1';
		buff[MAX((*exp)++, 0) + preci + 1] = '0';
	}
	buff[i] += 1;
}

static void		prepare_fp_buff(char **buff, t_ieee_fmt style,
									int *exp, int preci)
{
	t_int32			npad;
	size_t			buff_size;

	buff_size = ft_strlen(*buff);
	if (*exp < 0 && style == IEEE_NORMAL)
		ft_strpad(buff, '0', -*exp, TOWARD_HEAD);
	if (*exp <= 0)
		npad = MAX(preci - (buff_size - 1), 0);
	else
		npad = MAX(*exp - (buff_size - 1), 0) + preci
				- (*exp > ((ssize_t)buff_size - 1)
					? 0 : ft_strlen(*buff + *exp + 1));
	/* (void)printf(" << %d %zu\n", ABS(npad), buff_size); */
	/* (void)getchar(); */
	ft_strpad(buff, '0', ABS(npad), TOWARD_TAIL);
	round_nearest_even(buff, style, exp, preci);
}

void	dragon4_prec(char **fp_buff, t_int32 *exp, t_ieee_fmt style,
						t_uint32 preci)
{
	char	*fp;
	char	*tmp;
	char	*int_part;
	int		exp2;

	/* ft_putstr(" fp_buff ?? "); ft_putendl(*fp_buff); */
	/* getchar(); */

	prepare_fp_buff(fp_buff, style, exp, preci);

	/* ft_putstr(" prepered fp_buff ?? "); ft_putendl(*fp_buff); */
	/* getchar(); */

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

	/* ft_putnumber(*exp); ft_putstr(" >>> "); ft_putendl(fp); */
	/* getchar(); */

	if (preci)
	{
		ft_strappend(&fp, ".");
		skip_leading_zeros(&fp);
		tmp = ft_strrdup(int_part + exp2 + 1, int_part + exp2 + preci);
		ft_strappend(&fp, tmp);
		ft_strdel(&tmp);
	}
	ft_strdel(fp_buff);
	*fp_buff = fp;
}
