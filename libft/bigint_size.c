#include "bigint.h"

t_uint64	bigint_size(t_bigint u)
{
	t_uint64 size;

	size = 0;
	while (u.block[size])
		size++;
	return (size);
}
