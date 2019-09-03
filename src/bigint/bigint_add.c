#include "bigint.h"

/* FIXME: an overflow if index > BIGINT_MAX_SIZE */
t_bigint	bigint_add(t_bigint u, t_bigint v)
{
	t_bigint result;
	t_u64 sum;
	t_u64 carry;
	t_u32 i;
	t_u32 biggest;

	i = 0;
	sum = 0UL;
	carry = 0UL;
	biggest = MAX(u.size, v.size);
	ft_bzero(&result, sizeof(t_bigint));
	while (i < biggest)
	{
		sum = carry + (t_u64)u.block[i] + (t_u64)v.block[i];
		result.block[i++] = (t_u32)(sum & BLOCK_MASK);
		carry = sum >> BLOCK_SIZE;
	}
	if (carry && i < BLOCK_MAX)
		result.block[i] = (t_u32)(carry & BLOCK_MASK);
	result.size = biggest + (carry != 0);
	return (result);
}

t_bigint	bigint_inadd(t_bigint *u, t_bigint v)
{
	return (*u = bigint_add(*u, v));
}
