#include "bigint.h"

t_uint64	bigint_size(t_bigint u)
{
	t_uint64 size;

	size = BLOCK_MAX;
	while (size--)
		if (u.block[size])
			return (size + 1);
	return (0);
}
