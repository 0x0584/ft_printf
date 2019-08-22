#include "bigint.h"

/* FIXME: an overflow if index > BIGINT_MAX_SIZE */
t_bigint	bigint_add(t_bigint u, t_bigint v)
{
	t_bigint result;
	t_uint64 sum;
	t_uint64 carry;
	t_uint32 i;
	t_uint32 biggest;

	sum = 0UL;
	carry = 0UL;
	i = 0;
	biggest = MAX(u.size, v.size);
	ft_bzero(&result, sizeof(t_bigint));
	while (i < biggest)
	{
		sum = carry + (t_uint64)u.block[i] + (t_uint64)v.block[i];
		result.block[i++] = (t_uint32)(sum & BLOCK_MASK);
		carry = sum >> BLOCK_SIZE;
	}
	if (carry && i < BLOCK_MAX)
		result.block[i] = (t_uint32)(carry & BLOCK_MASK);
	result.size = biggest + (carry != 0);
	return (result);
}

void		bigint_inadd(t_bigint *u, t_bigint v)
{
	*u = bigint_add(*u, v);
}
