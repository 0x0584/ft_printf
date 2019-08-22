#include "bigint.h"

static t_bigint		bigint_intmul(t_bigint big, t_uint32 num)
{
	t_bigint result;
	t_uint64 muled;
	t_uint64 carry;
	t_uint32 i;

	i = 0;
	if (num == 1)
		return (bigint_dup(big));
	i = 0;
	carry = 0UL;
	while (i < big.size)
	{
		muled = (t_uint64)big.block[i] * (t_uint64)num + carry;
		result.block[i] = (t_uint32)(muled & BLOCK_MASK);
		carry = muled >> BLOCK_SIZE ;
		i++;
	}
	if (carry && i < BLOCK_MAX)
		result.block[i] = (t_uint32)(carry & BLOCK_MASK);
	result.size = bigint_size(result);
	return (result);
}

t_bigint			bigint_mul(t_bigint u, t_bigint v)
{
	t_bigint order[2];
	t_bigint result;
	t_uint32 shift;

	order[0] = bigint_minof(u, v);
	order[1] = bigint_maxof(u, v);
	ft_bzero(&result, sizeof(t_bigint));
	while (shift < order[0].size)
	{
		bigint_inadd(&result,
					 bigint_bls(bigint_intmul(order[1],
											  order[0].block[shift]),
								shift * BLOCK_SIZE));
		shift++;
	}
	return (result);
}

void				bigint_inmul(t_bigint *u, t_bigint v)
{
	*u = bigint_mul(*u, v);
}
