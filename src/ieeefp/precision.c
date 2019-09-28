/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:59:08 by archid-           #+#    #+#             */
/*   Updated: 2019/09/28 19:14:08 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
}

static void		prepare_fp_buff(char **buff, t_ieee_fmt style,
									t_s32 *exp, int prec)
{
	t_s32			npad;
	size_t			buff_size;

	buff_size = ft_strlen(*buff) - 1;
	if (*exp < 0 && style == IEEE_NORMAL)
		ft_strpad(buff, '0', (size_t)-*exp, TOWARD_HEAD);
	if (*exp <= 0)
		npad = MAX(prec - (t_s32)buff_size, 0);
	else
		npad = MAX(*exp - (t_s32)buff_size, 0) + prec
				- (*exp < (t_s32)buff_size ? 0 : ft_strlen(*buff + *exp + 1));
	ft_strpad(buff, '0', (size_t)npad, TOWARD_TAIL);
	round_nearest_even(buff, style, exp, prec);
}

void			dragon4_prec(char **fp_buff, t_s32 *exp, t_ieee_fmt style,
								t_u32 prec)
{
	char	*fp;
	char	*tmp;
	char	*int_part;
	char	*frac_part;
	int		exp2;

	prepare_fp_buff(fp_buff, style, exp, prec);
	int_part = *fp_buff;
	exp2 = MAX(style == IEEE_EXPONENT ? 0 : *exp, 0);
	fp = ft_strrdup(int_part, int_part + exp2);
	frac_part = prec ? int_part + exp2 : NULL;
	if (frac_part)
	{
		ft_strappend(&fp, ".");
		skip_leading_zeros(&fp);
		tmp = ft_strrdup(frac_part + 1, frac_part + prec);
		ft_strappend(&fp, tmp);
		ft_strdel(&tmp);
	}
	ft_strchange(fp_buff, fp);
}
