#include "bigint.h"

t_bigint	bigint_bls(t_bigint u, t_uint32 shift)
{
	t_bigint result;
	t_uint32 i;

	if (!shift)
		return (bigint_dup(u));
	i = BLOCK_MAX;
	ft_bzero(&result, sizeof(t_bigint));
	if (!(shift % BLOCK_SIZE))
		while (--i >= (shift / BLOCK_SIZE))
			result.block[i] = u.block[i - (shift / BLOCK_SIZE)];
	else
	{
		while (--i >= (shift / BLOCK_SIZE + 1))
			result.block[i] = (u.block[i - (shift / BLOCK_SIZE + 1)]
							   >> (BLOCK_SIZE - (shift % BLOCK_SIZE)))
				| (u.block[i - (shift / BLOCK_SIZE)]
				   << (shift % BLOCK_SIZE));
		result.block[i] = u.block[i - (shift / BLOCK_SIZE)]
			<< (shift % BLOCK_SIZE);
	}
	result.size = bigint_size(result);
	return (result);
}

t_bigint	bigint_inbls(t_bigint *u, t_uint32 shift)
{
	return (*u = bigint_bls(*u, shift));
}
