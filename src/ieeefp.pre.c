#include "libft.h"
#include "ieeefp.h"

static bool		has_trailing_zeros(char *buff, size_t index)
{
	while (buff[index])
		if (buff[index] != '0')
			return (false);
		else
			index++;
	return (true);
}

static void		round_nearest_even(char **fp_buff, t_ieee_fmt ftype,
										int *exp, int preci)
{
	char			*buff;
	size_t			i;
	t_uint32		carry;

	buff = *fp_buff;
	i = MAX(ftype == IEEE_EXPONENT ? 0 : *exp, 0) + preci;
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

static void		prepare_fp_buff(char **buff, t_ieee_fmt ftype,
									int *exp, int preci)
{
	t_int32			npad;
	size_t			buff_size;

	buff_size = ft_strlen(*buff);
	if (*exp < 0 && ftype == IEEE_NORMAL)
		ft_strpad(buff, '0', -*exp, TOWARD_HEAD);
	if (*exp <= 0)
		npad = MAX(preci - (buff_size - 1), 0);
	else
		npad = MAX(*exp - (buff_size - 1), 0) + preci -
			(*exp > ((int)buff_size - 1) ? 0 : ft_strlen(*buff + *exp + 1));
	(void)printf(" << %d %zu\n", ABS(npad), buff_size);
	/* (void)getchar(); */
	ft_strpad(buff, '0', ABS(npad), TOWARD_TAIL);
	round_nearest_even(buff, ftype, exp, preci);
}

void	skip_leading_zeros(char **astr)
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

void	handle_precision(char **fp_buff, t_ieee_fmt ftype, int exp, int preci)
{
	char	*fp;
	char	*tmp;
	int		exp2;

	prepare_fp_buff(fp_buff, ftype, &exp, preci);
	exp2 = MAX(ftype == IEEE_EXPONENT ? 0 : exp, 0);
	ft_putendl("^^^");
	fp = ft_strrdup(*fp_buff, *fp_buff + exp2);
	getchar();
	if (preci)
	{
		ft_strappend(&fp, ".");
		skip_leading_zeros(&fp);
		tmp = ft_strrdup(*fp_buff + exp2 + 1, *fp_buff + exp2 + preci);
		ft_strappend(&fp, tmp);
		ft_strdel(&tmp);
	}
	ft_strdel(fp_buff);
	*fp_buff = fp;
}
