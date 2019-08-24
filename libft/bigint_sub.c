#include "bigint.h"

/* always subtract the lowest from the biggest */
/* FIXME: try to handle the sign */

t_bigint	bigint_sub(t_bigint u, t_bigint v)
{
	t_bigint result;
	t_bigint order[2];
	t_uint64 carry;
	t_uint64 tmp;
	t_uint32 i;

	i = 0;
	carry = 0UL;
	order[0] = bigint_maxof(u, v);
	order[1] = bigint_minof(u, v);
	ft_bzero(&result, sizeof(t_bigint));
	while (i < order[0].size)
	{
		tmp = (t_uint64)order[0].block[i] - carry;
		carry = ((order[0].block[i] > 0 || (!order[0].block[i] && !carry))
					&& tmp >= (t_uint64)order[1].block[i]) ? 0UL : 1UL;
		result.block[i] = (t_uint32)((tmp + (carry ? 1UL << 32 : 0UL)
					   - (t_uint64)order[1].block[i]) & BLOCK_MASK);
		i++;
	}
	result.size = bigint_size(result);
	return (result);
}

t_bigint	bigint_insub(t_bigint *u, t_bigint v)
{
	return (*u = bigint_sub(*u, v));
}
