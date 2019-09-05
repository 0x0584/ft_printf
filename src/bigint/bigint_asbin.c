#include "bigint.h"

void		bigint_asbin(t_bigint u)
{
	char	*tmp;
	t_u16	i;
	t_u16	rem_bits;
	char	buff[sizeof(t_u32) * 8 + 1];

	i = u.size;
	while (i--)
	{
		tmp = ft_utoa_base(u.block[i], BASE_BIN);
		rem_bits = sizeof(t_u32) * 8 - ft_strlen(tmp);
		buff[rem_bits] = '\0';
		while (rem_bits--)
			buff[rem_bits] = '0';
		ft_putstr(buff);
		ft_putstr(tmp);
		ft_strdel(&tmp);
	}
	ft_putchar('\n');
}
