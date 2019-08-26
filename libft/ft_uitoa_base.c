/* create: 07/30/2019 17:19:46 */

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
			return false;
		i++;
	}
	return (true);
}

static size_t	count_udigits_in_base(uintmax_t nb, size_t radix)
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

static size_t	count_digits_in_base(intmax_t nb, size_t radix)
{
	return count_udigits_in_base(nb < 0 ? -nb : nb, radix);
}

char			*ft_itoa_base(intmax_t nb, const char *base)
{
	char			*buff;
	bool			sign;
	size_t			n_digi;
	size_t			radix;

	sign = (nb < 0);
	if (!isvalid_base(base))
		return (NULL);
	radix = ft_strlen(base);
	n_digi = count_digits_in_base(nb, radix);
	if (!(buff = ft_strnew(n_digi + sign)))
		return (NULL);
	while (n_digi--)
	{
		buff[n_digi + sign] = base[(sign ? -1 : 1) * (nb % radix)];
		nb /= radix;
	}
	if (sign)
		*buff = '-';
	return (buff);
}

char			*ft_utoa_base(uintmax_t nb, const char *base)
{
	char			*buff;
	size_t			n_digi;
	size_t			radix;

	if (!isvalid_base(base))
		return (NULL);
	radix = ft_strlen(base);
	n_digi = count_digits_in_base(nb, radix);
	if (!(buff = ft_strnew(n_digi)))
		return (NULL);
	while (n_digi--)
	{
		buff[n_digi] = base[nb % radix];
		nb /= radix;
	}
	return (buff);
}
