/* create: 07/30/2019 17:19:46 */

#include "libft.h"

static char *bases = "0123456789abcdef";

char	*ft_itoa_base(t_int128 nb, int base)
{
	char	*buff;
	int		n_digi;
	bool	is_signed;

	n_digi = 1;
	is_signed = 0;
	if (nb < 0)
	{
		is_signed = (base == 10);
		nb *= -1;
	}
	while (ft_power(base, n_digi) - 1 < nb)
		n_digi++;
	UNLESS_RET(buff = ft_strnew(sizeof(buff) * n_digi), NULL);
	buff[n_digi + is_signed] = '\0';
	while (n_digi-- > 0)
	{
		buff[n_digi + is_signed] = bases[nb % base];
		nb /= base;
	}
	if (is_signed)
		buff[0] = '-';
	return (buff);
}
