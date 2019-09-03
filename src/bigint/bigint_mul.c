#include "bigint.h"

t_bigint	bigint_umul(t_bigint big, t_u32 num)
{
	t_bigint result;
	t_u64 muled;
	t_u64 carry;
	t_u32 i;

	i = 0;
	ft_bzero(&result, sizeof(t_bigint));
	if (num == 1)
		return (bigint_dup(big));
	i = 0;
	carry = 0UL;
	while (i < big.size)
	{
		muled = carry + (t_u64)big.block[i] * (t_u64)num;
		result.block[i++] = (t_u32)(muled & BLOCK_MASK);
		carry = muled >> BLOCK_SIZE;
	}
	if (carry && i < BLOCK_MAX)
		result.block[i] = (t_u32)(carry & BLOCK_MASK);
	result.size = bigint_size(result);
	return (result);
}

t_bigint	bigint_mul(t_bigint u, t_bigint v)
{
	t_bigint order[2];
	t_bigint result;
	t_u32 shift;

	shift = 0;
	order[0] = bigint_minof(u, v);
	order[1] = bigint_maxof(u, v);
	ft_bzero(&result, sizeof(t_bigint));
	while (shift < order[0].size)
	{
		bigint_inadd(&result,
						bigint_bls(bigint_umul(order[1],
													order[0].block[shift]),
									shift * BLOCK_SIZE));
		shift++;
	}
	return (result);
}

t_bigint	bigint_inmul(t_bigint *u, t_bigint v)
{
	return (*u = bigint_mul(*u, v));
}
