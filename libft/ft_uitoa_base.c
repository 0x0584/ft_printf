/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 17:19:46 by archid-           #+#    #+#             */
/*   Updated: 2019/09/28 17:40:46 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool		isvalid_base(const char *base)
{
	size_t i;

	i = 0;
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+')
			return (false);
		if (ft_strchr(base + i + 1, base[i]))
			return (false);
		i++;
	}
	return (true);
}

static size_t	count_udigits_in_base(t_u128 nb, size_t radix)
{
	size_t count;

	if (nb == 0)
		return (1);
	count = 0;
	while (nb)
	{
		count++;
		nb /= radix;
	}
	return (count);
}

static size_t	count_digits_in_base(t_s128 nb, size_t radix)
{
	t_u128 foo;

	foo = nb < 0 ? -nb : nb;
	return (count_udigits_in_base(foo, radix));
}

char			*ft_itoa_base(t_s128 nb, const char *base)
{
	char	*buff;
	size_t	n_digi;
	size_t	radix;
	t_u128	foo;

	foo = (nb < 0) ? -nb : nb;
	if (!isvalid_base(base))
		return (NULL);
	radix = ft_strlen(base);
	n_digi = count_digits_in_base(foo, radix);
	if (!(buff = ft_strnew(n_digi + (nb < 0))))
		return (NULL);
	while (n_digi--)
	{
		buff[n_digi + (nb < 0)] = base[(foo % radix)];
		foo /= radix;
	}
	if (nb < 0)
		*buff = '-';
	return (buff);
}

char			*ft_utoa_base(t_u128 nb, const char *base)
{
	char			*buff;
	size_t			n_digi;
	size_t			radix;

	if (!isvalid_base(base))
		return (NULL);
	radix = ft_strlen(base);
	n_digi = count_udigits_in_base(nb, radix);
	if (!(buff = ft_strnew(n_digi)))
		return (NULL);
	while (n_digi--)
	{
		buff[n_digi] = base[nb % radix];
		nb /= radix;
	}
	return (buff);
}
