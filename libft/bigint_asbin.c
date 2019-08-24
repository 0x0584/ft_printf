#include "bigint.h"

void		bigint_asbin(t_bigint u)
{
	char		*tmp;
	t_uint16	i;
	t_uint16	rem_bits;
	char		buff[sizeof(t_uint32) * 8 + 1];

	i = u.size;
	while (i--)
	{
		tmp = ft_uitoa_base(u.block[i], BASE_BIN);
		rem_bits = sizeof(t_uint32) * 8 - ft_strlen(tmp);
		buff[rem_bits] = '\0';
		while (rem_bits--)
			buff[rem_bits] = '0';
		ft_putstr(buff);
		ft_putstr(tmp);
		ft_strdel(&tmp);
	}
	ft_putchar('\n');
}
