#include "bigint.h"

t_bigint	bigint_init(uintmax_t val)
{
	t_bigint big;
	t_int32 index;

	index = 0;
	ft_bzero(&big, sizeof(t_bigint));
	ft_putstr("#");
	while (val && index < BLOCK_MAX)
	{
		big.block[index++] = (t_uint32)(val & BLOCK_MASK);
		val >>= BLOCK_SIZE;
		ft_putstr(".");
	}
	ft_putstr("#");
	big.size = bigint_size(big);
	return (big);
}
