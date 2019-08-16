#include "libft.h"

static bool		isvalid_base(const char *base)
{
	int		i;
	int		size;

	if (!base || !*base)
		return (false);
	size = ft_strchr(base, '\0') - base;
	i = 0;
	while (i < size)
	{
		if (base[i] == '+' || base[i] == '-' || !ft_isprint(base[i]))
			return (false);
		if (ft_strchr(base + i + 1, base[i]))
			return (false);
		i++;
	}
	return (true);
}

static int		ft_udigits_base(uintmax_t n, int base)
{
	int		i;

	if (base < 1)
		return (-1);
	else if (base == 1)
		return (n);
	else if (n == 0)
		return (1);
	i = 0;
	while (n != 0)
	{
		i++;
		n /= base;
	}
	return (i);
}

char	*ft_uitoa_base(unsigned long nb, const char *base)
{
	int		index;
	int		base_size;
	int		ndigi;
	char	*arr;

	if (!base || !isvalid_base(base))
		return (NULL);
	base_size = ft_strchr(base, '\0') - base;
	ndigi = ft_udigits_base(nb, base_size);
	index = ndigi;
	if (!(arr = ft_strnew(index)))
		return (NULL);
	if (nb != 0)
		while (ndigi--)
		{
			arr[--index] = base[nb % base_size];
			nb /= base_size;
		}
	else
		arr[0] = base[0];
	return (arr);
}
